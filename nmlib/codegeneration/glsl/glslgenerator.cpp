#include <nmlib/codegeneration/glsl/glslgenerator.hpp>
#include <nmlib/codegeneration/zerodefaultsgenerator.hpp>
#include <nmlib/codegeneration/simplebodygenerator.hpp>
#include <nmlib/codegeneration/compositemodulegenerator.hpp>

#include <sstream>

namespace nm {
namespace glsl {

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

std::unique_ptr<ModuleGenerator> GlslGenerator::getModuleGenerator(Module &module)
{
//    auto moduleTypeName = module.getType().getName();
//    std::unique_ptr<BodyGenerator> body;
//    std::unique_ptr<DefaultsGenerator> defaults;
//    body.reset(new SimpleBodyGenerator("//empty body\n"));
//    defaults.reset(new ZeroDefaultsGenerator(module));
//    //TODO implement other modules
//    if(moduleTypeName == "add"){
//        body.reset(new SimpleBodyGenerator("float result = lhs + rhs;\n"));
//    } else if (moduleTypeName == "demux2") {
//        body.reset(new SimpleBodyGenerator(
//            "float x = m.x;\n"
//            "float y = m.y;\n"
//        ));
//    } else if (moduleTypeName == "mul1") {
//        body.reset(new SimpleBodyGenerator(
//            "float result = lhs * rhs;\n"
//        ));
//    } else {
        return InlineGenerator::getModuleGenerator(module);
//    }
//    return std::unique_ptr<ModuleGenerator>{new CompositeModuleGenerator(std::move(body), std::move(defaults))};
}

GlslGenerator::GlslGenerator():
    InlineGenerator()
{
}

} // namespace glsl
} // namespace nm
