#include "parser.hpp"

//TODO get rapidjson to fix these warnings
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <rapidsjon/document.h>

#include <iostream>
#include <cstdio>

namespace nm {

namespace {

optional<std::pair<std::string, std::string> > parseDotPair(const std::string &sourceString){
    //TODO error checking
    auto dotPos = sourceString.find(".");
    auto sourceModuleString = sourceString.substr(0, dotPos);
    auto outputLinkString = sourceString.substr(dotPos+1);
    return {{sourceModuleString, outputLinkString}};
}

//std::vector<std::string> split(const std::string& input, const std::string& regex) {
//    // passing -1 as the submatch index parameter performs splitting
//    std::sregex_token_iterator
//        first{input.begin(), input.end(), regex, -1},
//        last;
//    return {first, last};
//}
optional<SignalType> parseSignalType(const rapidjson::Value &signalTypeValue)
{
    if(!signalTypeValue.IsString()){
        return{};
    }
    int dimensionality{-1};
    if(sscanf(signalTypeValue.GetString(), "%df", &dimensionality) == EOF){
        std::cerr << "Couldn't parse signal type";
        return {};
    }
    return {SignalType{dimensionality}};
}

optional<std::unique_ptr<Module> > parseModule(const rapidjson::Value &moduleValue, const nm::TypeManager &typeManager, Graph &graph)
{
    if(!moduleValue["name"].IsString()){
        return false;
    }
    if(!moduleValue["type"].IsString()){
        return false;
    }
    std::string typeString = moduleValue["type"].GetString();
    std::string nameString = moduleValue["name"].GetString();
    auto type = typeManager.getType(typeString);
    if(type == nullptr){
        std::cerr << "Unknown type: " <<  typeString << std::endl;
        return false;
    }
    auto module = make_unique<Module>(*type, nameString);
    //TODO parse inputs
    auto &inputsValue = moduleValue["inputs"];
    if(!inputsValue.IsNull()){
        if(!inputsValue.IsObject()){
            std::cerr << "Invalid input\n";
            return false;
        }
        for(auto it = inputsValue.MemberBegin(); it != inputsValue.MemberEnd(); ++it){
            if(!it->name.IsString() || !it->value.IsString()){
                std::cerr << "Invalid member in inputs\n";
                return false;
            }

            //find out which input to connect
            auto inputName = it->name.GetString();
            auto inputLink = module->getInput(inputName);
            if(inputLink==nullptr){
                std::cerr << "ModuleType \"" << module->getName() << "\" has no input named \"" << inputName << "\"\n";
                return false;
            }

            //find out which outputlink to connect to
            auto sourceString = it->value.GetString();
            auto sourcePair = parseDotPair(sourceString);
            if(!sourcePair){
                std::cerr << "Couldn't parse input string\n";
                return false;
            }
            auto sourceModule = graph.getModule(sourcePair->first);
            if(sourceModule==nullptr){
                std::cerr << "No module named \"" << sourcePair->first << "\" in graph\n"; // \"" << owner.getName() << "\"\n";
                return false;
            }

            auto sourceOutputLink = sourceModule->getOutput(sourcePair->second);
            if(sourceOutputLink==nullptr){
                std::cerr << "No output named \"" << sourcePair->second << "\" in module \"" << sourceModule->getName() << "\"\n";
                return false;
            }
            inputLink->link(*sourceOutputLink);
        }

    }
    graph.addModule(std::move(module));
    return true;
}

optional<std::unique_ptr<CompositeTypeBuilder> > parseModuleType(const rapidjson::Value &type, const TypeManager& typeManager)
{
    auto &nameValue = type["name"];
    if(!nameValue.IsString()){
        std::cerr << "Module missing required field \"name\"\n";
        return {};
    }
    std::string moduleTypeName = nameValue.GetString();
    std::string description;
    auto &descriptionValue = type["description"];
    if(descriptionValue.IsString()){
        description = descriptionValue.GetString();
    }

    auto compositeBuilder = make_unique<CompositeTypeBuilder>(make_unique<ModuleType>(moduleTypeName, description));

    //parse inputs
    auto &inputsValue = type["inputs"];
    if(!inputsValue.IsNull()){
        if(!inputsValue.IsArray()){
            std::cerr << "inputs is not an array\n";
            return {};
        }
        for(rapidjson::SizeType i = 0; i < inputsValue.Size(); i++){
            auto &inputValue = inputsValue[i];
            std::string name = inputValue["name"].GetString();
            auto maybeSignalType = parseSignalType(inputValue["type"]);
            if(!maybeSignalType){
                return {};
            }
            compositeBuilder->addInput(name, *maybeSignalType);
        }
    }

    //parse submodules
    auto &modulesValue = type["modules"];
    if(!modulesValue.IsNull()){
        if(!modulesValue.IsArray()){
            std::cerr << "modules is not an array\n";
            return {};
        }
        for(rapidjson::SizeType i = 0; i<modulesValue.Size(); i++){
            auto success = parseModule(modulesValue[i], typeManager, *compositeBuilder->getGraph());
            //TODO consider continuing without this module?
            if(!success){
                std::cerr << "Couldn't parse Module\n";
                return {};
            }
        }
    }

    //parse outputs
    auto &outputsValue = type["outputs"];
    if(!outputsValue.IsNull()){
        if(!outputsValue.IsArray()){
            std::cerr << "outputs is not an array\n";
            return {};
        }
        for(rapidjson::SizeType i = 0; i < outputsValue.Size(); i++){
            auto &outputValue = outputsValue[i];
            if(!outputValue["name"].IsString() || !outputValue["source"].IsString()){
                std::cerr << "Missing required field name or string";
                return {};
            }
            std::string externalName = outputValue["name"].GetString();
            std::string sourceString = outputValue["source"].GetString();
            //dotpos stufff
            auto sourcePair = parseDotPair(sourceString);
            if(!sourcePair){
                std::cerr << "Couldn't parse source string: " << sourceString << "\n";
                return {};
            }
            Module* module = moduleType->getModule(sourcePair->first);
            if(module==nullptr){
                std::cerr << "Couldn't find the output node for: " << sourceString << "\n";
                return {};
            }
            OutputLink* outputLink = module->getOutput(sourcePair->second);
            if(outputLink==nullptr){
                std::cerr << "Couldn't find an output named: " << sourcePair->second << "\n";
                return{};
            }
            moduleType->exportOutput(*outputLink, externalName);
        }
    }

    return {std::move(moduleType)};
}

bool parseModuleTypeArray(const rapidjson::Value &array, TypeManager &typeManager)
{
    if(!array.IsArray()){
        std::cerr << "Tried to parse an array that wasn't an array";
        return {};
    }
    std::map <std::string, std::unique_ptr<ModuleType>> moduleTypes{};
    for(rapidjson::SizeType i = 0; i < array.Size(); i++){
        auto maybeModuleType = parseModuleType(array[i], typeManager);
        if(!maybeModuleType){
            return false;
        }
        std::unique_ptr<ModuleType> &moduleTypePtr = *maybeModuleType;
        if(!typeManager.addUserType(std::move(moduleTypePtr))){
            std::cerr << "Couldn't add type to typeManager.\n";
            return false;
        }
    }
    return true;
}

} // namespace

Parser::Parser()
{
}

optional<std::unique_ptr<TypeManager> > Parser::parseDocument(std::string input)
{
    rapidjson::Document document;
    document.Parse<0>(input.c_str());

    if(document.HasParseError()){
        std::cerr << "Couldn't parse json document\n";
        return {};
    }

    auto &moduleTypes = document["moduleTypes"];

    if(moduleTypes.IsNull()){
        std::cerr << "moduleTypes not present in root of document\n";
        return {};
    }

    std::unique_ptr<TypeManager> typeManager{new TypeManager{}};
    typeManager->initBuiltinTypes();
    if(!parseModuleTypeArray(moduleTypes, *(typeManager.get()))){
        return {};
    }
    return {std::move(typeManager)};
}

} // namespace nm
