#include "inlinegenerator.hpp"

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

namespace nm {

void InlineGenerator::generateModule(const std::vector<InlineGenerator::InputRemap> &inputRemaps, const std::vector<InlineGenerator::OutputRemap> &outputRemaps, std::ostream &out)
{
    generatePreamble(inputRemaps, outputRemaps, out);
    generateBody(out);
    generatePostamble(outputRemaps, out);
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
    out << "//funtion body here!\n";
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
        out << remap.externalName << " = " << remap.inputLink->getModuleInput().getName() << ";\n";
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
