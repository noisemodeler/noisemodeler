#include "glslgenerator.hpp"

#include <sstream>

namespace nm {

std::string GlslGenerator::compileToGlslFunction(InputLink &inputLink, OutputLink &outputLink, std::string name)
{
    std::stringstream sl;
    GlslGenerator generator;
    auto posId = "pos_"+generator.getUniqueId();
    auto heightId = "height_"+generator.getUniqueId();

    //function start
    sl << "void " << name << "(";

    //inputs
    sl << "in vec2 " << posId;
    sl << ", ";

    //outputs
    sl << "out float height";

    //function body start
    sl << "){\n";


    //function body
//    sl << "    height=pos.y;\n";
    InlineGenerator::InputRemap inputRemap{posId, &inputLink};
    InlineGenerator::OutputRemap outputRemap{heightId, &outputLink};
    std::vector<InputRemap> inputRemaps{inputRemap};
    std::vector<OutputRemap> outputRemaps{outputRemap};
    generator.generateFromLinks(inputRemaps, outputRemaps, sl);
//    InlineGenerator::compileInline(sl);


    //function end
    //write to outputs
    sl << "height" << " = " << heightId << ";\n";
    sl << "}\n";
    return sl.str();
}

void GlslGenerator::genTypeKeyword(const SignalType &signalType, std::ostream &out)
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

GlslGenerator::GlslGenerator():
    InlineGenerator()
{
}

} // namespace nm
