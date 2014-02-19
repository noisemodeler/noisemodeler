#include "inlinegenerator.hpp"

#include <nmlib/codegeneration/compositemodulegenerator.hpp>
#include <nmlib/codegeneration/simplebodygenerator.hpp>
#include <nmlib/codegeneration/zerodefaultsgenerator.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>
#include <nmlib/model/signalvalue.hpp>

#include <nmlib/util.hpp>

#include <nmlib/util.hpp>

#include <algorithm>
#include <sstream>

namespace nm {

InlineGenerator::InlineGenerator()
{

}

void InlineGenerator::generateFromLinks(const std::vector<InlineGenerator::InputRemap> &inputRemaps, const std::vector<InlineGenerator::OutputRemap> &outputRemaps, std::ostream &out)
{
    std::vector<OutputLink*> outputs;
    outputs.reserve(outputRemaps.size());
    for(auto outputRemap : outputRemaps){
        outputs.push_back(outputRemap.outputLink);
    }

    std::set<InputLink*> inputs;
    for(auto inputRemap : inputRemaps){
        inputs.insert(inputRemap.inputLink);
    }

    std::vector<OutputRemap> internalOutputRemaps = outputRemaps;

    auto dependencies = Module::getDependenciesSorted(outputs, inputs);

//    std::remove_if(begin(dependencies), end(dependencies), [&](Module &module){
//        return end(inputRemaps) != find_if(begin(inputRemaps), end(inputRemaps), [&](InputRemap& inputRemap){
//            return &module == &inputRemap.inputLink->getOwner();
//        });
//    });

    //generate code for all dependencies
    for(auto module : dependencies){

        out << "//////////////////////////////////////////\n";
        out << "//Generating code for " <<  module->getName() << "\n";
        out << "//////////////////////////////////////////\n";


        //get existing remaps for inputs of this module
        std::vector<InputRemap> moduleInputRemaps;
        auto moduleInputLinks = module->getInputs();
        for(auto inputLink : moduleInputLinks){
            //is this the input we are going to export?
            auto myMatch = std::find_if(inputRemaps.begin(), inputRemaps.end(), [&](const InputRemap& remap){
                return remap.inputLink == inputLink;
            });
            if(myMatch!=inputRemaps.end()){
                moduleInputRemaps.push_back(*myMatch);
                continue;
            }

            auto outputLink = inputLink->getOutputLink();
            if(outputLink==nullptr)continue;

            auto match = std::find_if(internalOutputRemaps.begin(), internalOutputRemaps.end(), [=](OutputRemap& remap){
                return remap.outputLink == outputLink;
            });
            if(match!=outputRemaps.end()){
                //found matching outputlink in remaps
                OutputRemap &remap = *match;
                moduleInputRemaps.emplace_back(InputRemap{remap.externalName, inputLink}); //make the names match
            }
        }
        //create uniqueid outputs of this module
        std::vector<OutputRemap> moduleOutputRemaps;
        auto moduleOutputLinks = module->getOutputs();
        for(auto outputLink : moduleOutputLinks){
            auto match = std::find_if(internalOutputRemaps.begin(), internalOutputRemaps.end(), [=](OutputRemap& remap){
                return remap.outputLink == outputLink;
            });
            if(match!=internalOutputRemaps.end()){
                OutputRemap &remap = *match;
                moduleOutputRemaps.push_back(remap);
            } else {
                OutputRemap remap{getUniqueId(), outputLink};
                internalOutputRemaps.push_back(remap);
                moduleOutputRemaps.push_back(std::move(remap));
            }
        }
        generateModule(*module, moduleInputRemaps, moduleOutputRemaps, out);
    }
}

void InlineGenerator::generateModule(Module &module, const std::vector<InlineGenerator::InputRemap> &inputRemaps, const std::vector<InlineGenerator::OutputRemap> &outputRemaps, std::ostream &out)
{
    //module handler object
    std::unique_ptr<ModuleGenerator> moduleGenerator = getModuleGenerator(module);

    //declare outputs of scope
    generateOutputDeclarations(outputRemaps, out);

    //start module call scope
    out << "{\n";

    //declare all inputs
    generateInputDeclarations(module, out);

    //generate default values for inputs
    moduleGenerator->generateDefaults(*this, out);

    //overwrite defaults with supplied remaps
    out << "\n//generating input reassignments\n";
    for(auto remap : inputRemaps){
        auto &moduleInput = remap.inputLink->getModuleInput();
        out << " " << moduleInput.getName() << ";\n";
    }

    //assign custom inputs from inputremaps
    generateInputAssignments(inputRemaps, out);

    out << "\n//funtion body for module \"" << module.getName() << "\" of type \"" << module.getType().getName() << "\"\n";
    moduleGenerator->generateBody(*this, out);
    out << "//end function body\n\n";

    out << "\n//generating postamble\n";
    //assign outputs to remapped values
    generateOutputAssignments(outputRemaps, out);
    out << "}\n";
}

std::string InlineGenerator::getUniqueId()
{
    return m_idGenerator.getUniqueId();
}

std::unique_ptr<ModuleGenerator> InlineGenerator::getModuleGenerator(Module &module)
{
    auto moduleTypeName = module.getType().getName();
    std::unique_ptr<BodyGenerator> body;
    std::unique_ptr<DefaultsGenerator> defaults;
    body.reset(new SimpleBodyGenerator("//empty body\n"));
    defaults.reset(new ZeroDefaultsGenerator(module));
    if(moduleTypeName == "add"){
        body.reset(new SimpleBodyGenerator("float result = lhs + rhs;\n"));
    } else if (moduleTypeName == "demux2") {
        body.reset(new SimpleBodyGenerator(
            "float x = m.x;\n"
            "float y = m.y;\n"
        ));
    } else if (moduleTypeName == "mul1") {
        body.reset(new SimpleBodyGenerator(
            "float result = lhs * rhs;\n"
        ));
    } else {
        std::cerr << "No policy for module of type: " << moduleTypeName << "\n";
    }
    return std::unique_ptr<ModuleGenerator>{new CompositeModuleGenerator(std::move(body), std::move(defaults))};
}

void InlineGenerator::genValue(const SignalValue &value, std::ostream &out)
{
    if(value.getSignalType().dimensionality==1){
        out << value[0];
    } else {
        genTypeKeyword(value.getSignalType(), out);
        out << "(";
        for(unsigned int i=0; i<static_cast<unsigned int>(value.getSignalType().dimensionality-1); ++i){
            out << value[i] << ", ";
        }
        out << value[static_cast<unsigned int>(value.getSignalType().dimensionality-1)] << ")";
    }
}

void InlineGenerator::generateOutputDeclarations(const std::vector<InlineGenerator::OutputRemap> &remaps, std::ostream &out)
{
    out << "\n//generating output declarations\n";
    for(auto &remap : remaps){
        genTypeKeyword(remap.outputLink->getModuleOutput().getSignalType(), out);
        out << " " << remap.externalName << ";\n";
    }
}

void InlineGenerator::generateInputDeclarations(Module &module, std::ostream &out)
{
    out << "\n//generating input declarations\n";
    for(auto inputLink : module.getInputs()){
        auto &moduleInput =inputLink->getModuleInput();
        genTypeKeyword(moduleInput.getSignalType(), out);
        out << " " << moduleInput.getName() << ";\n";
    }
}

void InlineGenerator::generateInputAssignments(const std::vector<InlineGenerator::InputRemap> &remaps, std::ostream &out)
{
    for(auto remap : remaps){
//        out << remap.inputLink->getModuleInput().getName() << " = " << remap.externalName << ";\n";
        auto assignment = make_unique<Assignment>(
            make_unique<Variable>(remap.inputLink->getModuleInput().getName()),
            make_unique<Variable>(remap.externalName)
        );
        assignment->gen(*this, out);
    }
}

void InlineGenerator::generateOutputAssignments(const std::vector<InlineGenerator::OutputRemap> &remaps, std::ostream &out)
{
    out << "\n//generating outputassignments\n";
    for(auto remap : remaps){
        auto assignment = make_unique<Assignment>(
            make_unique<Variable>(remap.externalName),
            make_unique<Variable>(remap.outputLink->getModuleOutput().getName())
        );
        assignment->gen(*this, out);
    }
}

void InlineGenerator::genTypeKeyword(const SignalType &signalType, std::ostream &out)
{
    switch(signalType.dimensionality){
    case 1:
        out << "float";
        break;
    case 2:
    case 3:
    case 4:
        out << "vec" << signalType.dimensionality;
        break;
    default:
        out << "UNKNOWN_TYPE";
    }
}

void InlineGenerator::genAssignment(const Assignment &assignment, std::ostream &out)
{
    assignment.lhs->gen(*this, out);
    out << " = ";
    assignment.rhs->gen(*this, out);
    out << ";\n";
}

void InlineGenerator::genVariable(const Variable &variable, std::ostream &out)
{
    out << variable.m_id;
}

} // namespace nm
