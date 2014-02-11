#include "inlinegenerator.hpp"

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

namespace nm {

void InlineGenerator::generateModule(const std::vector<InlineGenerator::InputConversion> &inputConversions, const std::vector<InlineGenerator::OutputConversion> &outputConversions, std::ostream &out)
{
    generatePreamble(inputConversions, outputConversions, out);
    generateBody(out);
    generatePostamble(outputConversions, out);
}

void InlineGenerator::generatePreamble(const std::vector<InputConversion> &inputConversions, const std::vector<OutputConversion> &outputConversions, std::ostream& out)
{
    generateOutputDeclarations(outputConversions, out);
    out << "{\n";
    for(auto &conversion : inputConversions){
        out << conversion.inputLink;
    }
}

void InlineGenerator::generateBody(std::ostream &out)
{
    out << "//funtion body here!\n";
}

void InlineGenerator::generatePostamble(std::vector<InlineGenerator::OutputConversion> conversions, std::ostream& out)
{
    generateOutputAssignments(conversions, out);
    out << "}\n";
}

void InlineGenerator::generateOutputDeclarations(const std::vector<InlineGenerator::OutputConversion> &conversions, std::ostream &out)
{
    for(auto &conversion : conversions){
        generateTypeKeyword(conversion.outputLink->getModuleOutput().getSignalType(), out);
        out << " " << conversion.externalSymbol << ";\n";
    }
}

void InlineGenerator::generateInputAssignments(const std::vector<InlineGenerator::InputConversion> &conversions, std::ostream &out)
{
    for(auto conversion : conversions){
        out << conversion.externalSymbol << " = " << conversion.inputLink->getModuleInput().getName() << ";\n";
    }
}

void InlineGenerator::generateOutputAssignments(const std::vector<InlineGenerator::OutputConversion> &conversions, std::ostream &out)
{
    for(auto conversion : conversions){
        out << conversion.externalSymbol << " = " << conversion.outputLink->getModuleOutput().getName() << ";\n";
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
