#include <nmlib/serialization/serializer.hpp>

#include <nmlib/model/typemanager.hpp>
#include <nmlib/model/typemanager.hpp>
#include <nmlib/model/graph.hpp>
#include <nmlib/model/module.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>

//TODO get rapidjson to fix these warnings
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <rapidsjon/prettywriter.h>
#include <rapidsjon/document.h>
#include <rapidsjon/stringbuffer.h>

#include <sstream>
#include <iostream> //TODO remove

namespace {

//implements rapidjson::Stream
template <typename Encoding>
struct GenericStdStringStreamWrapper {
    typedef typename Encoding::Ch Ch;
    GenericStdStringStreamWrapper(){}
//    Ch Peek() const { return *src_; }
//    Ch Take() { return *src_++; }
//    size_t Tell() const { return src_ - head_; }
    Ch* PutBegin() { return 0; }
    void Put(Ch c) { stream << c; }
    size_t PutEnd(Ch*) { return 0; }
    std::stringstream stream;
};
typedef GenericStdStringStreamWrapper<rapidjson::UTF8<> > StdStringStreamWrapper;

}

namespace nm {

void jsonifyModule(const Module& module, rapidjson::Value& moduleValue, rapidjson::Document& document){
    moduleValue.SetObject();
    moduleValue.AddMember("name", module.getName().c_str(), document.GetAllocator());
    moduleValue.AddMember("description", module.getDescription().c_str(), document.GetAllocator());
    moduleValue.AddMember("type", module.getType().getName().c_str(), document.GetAllocator());

    //add inputs
    rapidjson::Value inputsValue;
    inputsValue.SetObject();
    for(unsigned int i=0; i<module.getInputSize(); ++i){
        auto inputLink = module.getInput(i);
        auto outputLink = inputLink->getOutputLink();
        //only add connected links
        if(outputLink){
            std::string sourceString = outputLink->getOwner().getName() + "." + outputLink->getModuleOutput().getName();
            rapidjson::Value source(sourceString.c_str(), document.GetAllocator());
            rapidjson::Value inputName(inputLink->getModuleInput().getName().c_str(), document.GetAllocator());
            inputsValue.AddMember(inputName, source, document.GetAllocator());
        } else {
            //add custom unlinked values
            rapidjson::Value vectorValue;
            vectorValue.SetArray();
            auto unlinkedValue = inputLink->getUnlinkedValue();
            for(int j=0; j<unlinkedValue.getSignalType().dimensionality; ++j){
                vectorValue.PushBack(unlinkedValue[j], document.GetAllocator());
            }
            rapidjson::Value inputName(inputLink->getModuleInput().getName().c_str(), document.GetAllocator());
            inputsValue.AddMember(inputName, vectorValue, document.GetAllocator());
        }
    }
    moduleValue.AddMember("inputs", inputsValue, document.GetAllocator());
}

void jsonifyModuleType(const ModuleType& moduleType, rapidjson::Value& moduleTypeValue, rapidjson::Document& document){
    //TODO assert moduleType.isComposite

    moduleTypeValue.SetObject();
    moduleTypeValue.AddMember("name", moduleType.getName().c_str(), document.GetAllocator());
    moduleTypeValue.AddMember("description", moduleType.getDescription().c_str(), document.GetAllocator());

    //handle inputs
    rapidjson::Value inputs;
    inputs.SetArray();
    for(unsigned int i=0; i<moduleType.numInputs(); ++i){
        const ModuleInput* input = moduleType.getInput(i);
        rapidjson::Value inputValue;
        inputValue.SetObject();

        inputValue.AddMember("name", input->getName().c_str(), document.GetAllocator());

        int dimensionality = input->getSignalType().dimensionality;
        std::stringstream ss;
        ss << dimensionality << "f";
        rapidjson::Value typeValue(ss.str().c_str(), document.GetAllocator());
        inputValue.AddMember("type", typeValue, document.GetAllocator());
        inputs.PushBack(inputValue, document.GetAllocator());
    }
    moduleTypeValue.AddMember("inputs", inputs, document.GetAllocator());

    //handle outputs
    rapidjson::Value outputs;
    outputs.SetArray();
    for(unsigned int i=0; i<moduleType.numOutputs(); ++i){
        const ModuleOutput* output = moduleType.getOutput(i);
        const Module* outputsModule = moduleType.getGraph()->getModule("outputs");
        rapidjson::Value outputValue;
        outputValue.SetObject();
        outputValue.AddMember("name", output->getName().c_str(), document.GetAllocator());
        auto outputLink = outputsModule->getInput(0)->getOutputLink();
        std::string sourceString = outputLink->getOwner().getName() + "." + outputLink->getModuleOutput().getName();
        rapidjson::Value sourceStringValue(sourceString.c_str(),document.GetAllocator());
        outputValue.AddMember("source", sourceStringValue, document.GetAllocator());
        outputs.PushBack(outputValue, document.GetAllocator());
    }
    moduleTypeValue.AddMember("outputs", outputs, document.GetAllocator());

    //handle internal modules
    rapidjson::Value modulesValue;
    modulesValue.SetArray();
    auto graph = moduleType.getGraph();
    graph->traverseModulesTopological([&](const Module& module){
        //skip input/output modules
        if(module.getType().isGraphInput() || module.getType().isGraphOutput())return;
        rapidjson::Value moduleValue;
        jsonifyModule(module, moduleValue, document);
        modulesValue.PushBack(moduleValue, document.GetAllocator());
    });
    moduleTypeValue.AddMember("modules", modulesValue, document.GetAllocator());
}

Serializer::Serializer()
{
}

std::string Serializer::serialize(const TypeManager &typeManager)
{
    rapidjson::Document document;
    {
        rapidjson::Value moduleTypesValue;
        moduleTypesValue.SetArray();
        for(unsigned int i=0; i<typeManager.numUserTypes(); ++i){
            rapidjson::Value moduleTypeValue;
            jsonifyModuleType(*typeManager.getUserType(i), moduleTypeValue, document);
            moduleTypesValue.PushBack(moduleTypeValue, document.GetAllocator());
        }
        document.SetObject();
        document.AddMember("moduleTypes", moduleTypesValue, document.GetAllocator());
    }


    //TODO remove this line when rapidjson have fixed their bug (radix separator is decided by locale, instead of set to .)
    setlocale(LC_NUMERIC, "POSIX");

    //make an std::string from the document
    StdStringStreamWrapper streamWrapper;
    rapidjson::PrettyWriter<StdStringStreamWrapper> writer(streamWrapper);
    document.Accept(writer);

    return streamWrapper.stream.str();
}

} // namespace nm
