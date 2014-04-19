#include "inlinegenerator.hpp"

#include <nmlib/codegeneration/compositemodulegenerator.hpp>
#include <nmlib/codegeneration/simplebodygenerator.hpp>
#include <nmlib/codegeneration/unlinkedvaluedefaultsgenerator.hpp>
#include <nmlib/codegeneration/functioncallbodygenerator.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>
#include <nmlib/model/signalvalue.hpp>

#include <algorithm>
#include <sstream>

namespace nm {

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
    auto &moduleType = module.getType();
    std::unique_ptr<BodyGenerator> body;
    std::unique_ptr<DefaultsGenerator> defaults;
    body.reset(new SimpleBodyGenerator("//empty body\n"));
    defaults.reset(new UnlinkedValueDefaultsGenerator(module));
    //TODO composite module type
    if(moduleType.isComposite()){
        std::cerr << "TODO: implement composite module handling.\n";

    } else {
        std::cerr << "No policy for module of type: " << moduleType.getName() << "\n";
    }
    return std::unique_ptr<ModuleGenerator>{new CompositeModuleGenerator(std::move(body), std::move(defaults))};
}

void InlineGenerator::genDeclaration(const Declaration &variable, std::ostream &out)
{
    genTypeKeyword(variable.type, out);
    out << " ";
    variable.id->gen(*this, out);
    out << ";\n";
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

void InlineGenerator::genFunctionCall(FunctionCall &functionCall, std::ostream &out)
{
    out << functionCall.functionName;
    out << "(";
    for(auto in : functionCall.inputs) {
        in.gen(*this, out);
        out << ", ";
    }

    for(auto it = functionCall.outputs.begin(); it!=functionCall.outputs.end(); ++it) {
        it->gen(*this, out);
        if(it+1 != functionCall.outputs.end()){
            out << ", ";
        }
    }
    out << ";\n";
}

void InlineGenerator::generateOutputDeclarations(const std::vector<InlineGenerator::OutputRemap> &remaps, std::ostream &out)
{
    out << "\n//generating output declarations\n";
    for(auto &remap : remaps){
        Declaration declaration{
            remap.outputLink->getModuleOutput().getSignalType(),
            remap.externalName
        };
        declaration.gen(*this, out);
    }
}

void InlineGenerator::generateInputDeclarations(Module &module, std::ostream &out)
{
    out << "\n//generating input declarations\n";
    for(auto inputLink : module.getInputs()){
        auto &moduleInput = inputLink->getModuleInput();
        Declaration d{
            moduleInput.getSignalType(),
            moduleInput.getName()
        };
        d.gen(*this, out);
    }
}

void InlineGenerator::generateInputAssignments(const std::vector<InlineGenerator::InputRemap> &remaps, std::ostream &out)
{
    for(auto remap : remaps){
//        out << remap.inputLink->getModuleInput().getName() << " = " << remap.externalName << ";\n";
        Assignment assignment{
            remap.inputLink->getModuleInput().getName(),
            remap.externalName
        };
        assignment.gen(*this, out);
    }
}

void InlineGenerator::generateOutputAssignments(const std::vector<InlineGenerator::OutputRemap> &remaps, std::ostream &out)
{
    out << "\n//generating outputassignments\n";
    for(auto remap : remaps){
        Assignment assignment{
            remap.externalName,
            remap.outputLink->getModuleOutput().getName()
        };
        assignment.gen(*this, out);
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
