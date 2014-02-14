#include "inlinegenerator.hpp"

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>

#include <algorithm>

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
        generateModule(moduleInputRemaps, moduleOutputRemaps, out);
    }
}

void InlineGenerator::generateModule(const std::vector<InlineGenerator::InputRemap> &inputRemaps, const std::vector<InlineGenerator::OutputRemap> &outputRemaps, std::ostream &out)
{
    generatePreamble(inputRemaps, outputRemaps, out);
    Module &module = outputRemaps[0].outputLink->getOwner();
    out << "\n//funtion body for module \"" << module.getName() << "\" of type \"" << module.getType().getName() << "\"\n";
    generateBody(module, out);
    out << "//end function body\n\n";
    generatePostamble(outputRemaps, out);
}

std::string InlineGenerator::getUniqueId()
{
    return m_idGenerator.getUniqueId();
}

void InlineGenerator::generatePreamble(const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream& out)
{
    out << "\n//generating preamble\n";
    generateOutputDeclarations(outputRemaps, out);
    out << "{\n";
    generateInputDeclarations(inputRemaps, out);
    //TODO defaults here!
    generateModuleDefaultValues(outputRemaps[0].outputLink->getOwner(), out);
    generateInputAssignments(inputRemaps, out);
}

void InlineGenerator::generateModuleDefaultValues(Module &module, std::ostream &/*out*/)
{
    //TODO move to subclass
    auto moduleName = module.getType().getName();
    if(moduleName == "add"){
//        out << "lhs = 0; rhs = 0;";
    }

}

void InlineGenerator::generateBody(Module& /*module*/, std::ostream &out)
{
    out << "Override me!;\n";
}

void InlineGenerator::generatePostamble(std::vector<InlineGenerator::OutputRemap> remaps, std::ostream& out)
{
    out << "\n//generating postamble\n";
    generateOutputAssignments(remaps, out);
    out << "}\n";
}

void InlineGenerator::generateOutputDeclarations(const std::vector<InlineGenerator::OutputRemap> &remaps, std::ostream &out)
{
    out << "\n//generating output declarations\n";
    for(auto &remap : remaps){
        generateTypeKeyword(remap.outputLink->getModuleOutput().getSignalType(), out);
        out << " " << remap.externalName << ";\n";
    }
}

void InlineGenerator::generateInputDeclarations(const std::vector<InputRemap> &inputRemaps, std::ostream &out)
{
    out << "\n//generating input declarations\n";
    for(auto remap : inputRemaps){
        auto &moduleInput = remap.inputLink->getModuleInput();
        generateTypeKeyword(moduleInput.getSignalType(), out);
        out << " " << moduleInput.getName() << ";\n";
    }
}

void InlineGenerator::generateInputAssignments(const std::vector<InlineGenerator::InputRemap> &remaps, std::ostream &out)
{
    for(auto remap : remaps){
        out << remap.inputLink->getModuleInput().getName() << " = " << remap.externalName << ";\n";
    }
}

void InlineGenerator::generateOutputAssignments(const std::vector<InlineGenerator::OutputRemap> &remaps, std::ostream &out)
{
    out << "\n//generating outputassignments\n";
    for(auto remap : remaps){
        out << remap.externalName << " = " << remap.outputLink->getModuleOutput().getName() << ";\n";
    }
}

void InlineGenerator::generateTypeKeyword(const SignalType &signalType, std::ostream &out)
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

} // namespace nm
