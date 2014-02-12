#include "inlinegenerator.hpp"

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>

namespace nm {

InlineGenerator::InlineGenerator()
{

}

void InlineGenerator::generateFromLinks(const std::vector<InlineGenerator::InputRemap> &inputRemaps, const std::vector<InlineGenerator::OutputRemap> &outputRemaps, std::ostream &out)
{
    //sort topologically
    std::vector<OutputLink*> outputs;
    outputs.reserve(outputRemaps.size());
    for(auto outputRemap : outputRemaps){
        outputs.push_back(outputRemap.outputLink);
    }

    std::vector<InputLink*> inputs;
    inputs.reserve(inputRemaps.size());
    for(auto inputRemap : inputRemaps){
        inputs.push_back(inputRemap.inputLink);
    }
    Module::getRequiredModules(outputs, inputs);

    generatePreamble(inputRemaps, outputRemaps, out);
    generateBody(out);
    generatePostamble(outputRemaps, out);
}

void InlineGenerator::generateModule(const std::vector<InlineGenerator::InputRemap> &inputRemaps, const std::vector<InlineGenerator::OutputRemap> &outputRemaps, std::ostream &out)
{
    generatePreamble(inputRemaps, outputRemaps, out);
    generateBody(out);
    generatePostamble(outputRemaps, out);
}

std::string InlineGenerator::getUniqueId()
{
    return m_idGenerator.getUniqueId();
}

void InlineGenerator::generatePreamble(const std::vector<InputRemap> &inputRemaps, const std::vector<OutputRemap> &outputRemaps, std::ostream& out)
{
    generateOutputDeclarations(outputRemaps, out);
    out << "{\n";
    generateInputDeclarations(inputRemaps, out);
    //TODO defaults here!
    generateInputAssignments(inputRemaps, out);
}

void InlineGenerator::generateBody(std::ostream &out)
{
    out << "\n//funtion body here!\n";
    out << "float result = pos.x * pos.y;\n";
    out << "\n";
}

void InlineGenerator::generatePostamble(std::vector<InlineGenerator::OutputRemap> remaps, std::ostream& out)
{
    generateOutputAssignments(remaps, out);
    out << "}\n";
}

void InlineGenerator::generateOutputDeclarations(const std::vector<InlineGenerator::OutputRemap> &remaps, std::ostream &out)
{
    for(auto &remap : remaps){
        generateTypeKeyword(remap.outputLink->getModuleOutput().getSignalType(), out);
        out << " " << remap.externalName << ";\n";
    }
}

void InlineGenerator::generateInputDeclarations(const std::vector<InputRemap> &inputRemaps, std::ostream &out)
{
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
