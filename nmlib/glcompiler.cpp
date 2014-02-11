#include "glcompiler.hpp"

#include <sstream>

namespace nm {

class InlineCompiler {
public:
    struct InputConversion {
        std::string externalSymbol;
        InputLink* inputLink;
    };
    struct OutputConversion {
        std::string externalSymbol;
        OutputLink* outputLink;
    };
    explicit InlineCompiler(const BuiltinModuleType& module);
    void compileInline(const std::vector<InputConversion> &inputConversions, const std::vector<OutputConversion> &outputConversions, std::ostream &out);
private:
    void preamble(const std::vector<InputConversion> &inputConversions, const std::vector<OutputConversion> &outputConversions, std::ostream &out);
    void body(std::ostream &out);
    void postamble(std::vector<OutputConversion> conversions, std::ostream &out);

    void declareOutputs(const std::vector<OutputConversion> &conversions, std::ostream& out);
    void inputAssignments(const std::vector<InputConversion> &conversions, std::ostream& out);
    void outputAssignments(const std::vector<OutputConversion> &conversions, std::ostream& out);
    void typeKeyword(const SignalType &signalType, std::ostream& out);
    BuiltinModuleType& m_moduleType;
};



std::string GLCompiler::compileToGlslFunction(InputLink &/*inputLink*/, OutputLink &/*outputLink*/, std::string name)
{
    std::stringstream sl;

    //function start
    sl << "void " << name << "(";

    //inputs
    sl << "in vec2 pos";
    sl << ", ";

    //outputs
    sl << "out float height";

    //function body start
    sl << "){\n";


    //function body
    sl << "    height=pos.x;\n";
    InlineCompiler inlineCompiler;

    inlineCompiler.compileInline(sl);


    //function end
    sl << "}\n";
    return sl.str();
}

void InlineCompiler::compileInline(const std::vector<InlineCompiler::InputConversion> &inputConversions, const std::vector<InlineCompiler::OutputConversion> &outputConversions, std::ostream &out)
{
    preamble(inputConversions, outputConversions, out);
    body(out);
    postamble(outputConversions, out);
}

void InlineCompiler::preamble(const std::vector<InputConversion> &inputConversions, const std::vector<OutputConversion> &outputConversions, std::ostream& out)
{
    declareOutputs(outputConversions, out);
    out << "{\n";
    for(auto &conversion : inputConversions){
        out << conversion.inputLink;
    }
}

void InlineCompiler::body(std::ostream &out)
{
    out << "//funtion body here!\n";
}

void InlineCompiler::postamble(std::vector<InlineCompiler::OutputConversion> conversions, std::ostream& out)
{
    outputAssignments(conversions, out);
    out << "}\n";
}

void InlineCompiler::declareOutputs(const std::vector<InlineCompiler::OutputConversion> &conversions, std::ostream &out)
{
    for(auto &conversion : conversions){
        typeKeyword(conversion.outputLink->getModuleOutput().getSignalType(), out);
        out << " " << conversion.externalSymbol << ";\n";
    }
}

void InlineCompiler::inputAssignments(const std::vector<InlineCompiler::InputConversion> &conversions, std::ostream &out)
{
    for(auto conversion : conversions){
        out << conversion.externalSymbol << " = " << conversion.inputLink->getModuleInput().getName() << ";\n";
    }
}

void InlineCompiler::outputAssignments(const std::vector<InlineCompiler::OutputConversion> &conversions, std::ostream &out)
{
    for(auto conversion : conversions){
        out << conversion.externalSymbol << " = " << conversion.outputLink->getModuleOutput().getName() << ";\n";
    }
}

void InlineCompiler::typeKeyword(const SignalType &signalType, std::ostream &out)
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
