#include <nmlib/codegeneration/glsl/glslgenerator.hpp>
#include <nmlib/codegeneration/zerodefaultsgenerator.hpp>
#include <nmlib/codegeneration/simplebodygenerator.hpp>
#include <nmlib/codegeneration/compositemodulegenerator.hpp>

#include <nmlib/codegeneration/glsl/glslsourcenoise2d.hpp>

#include <sstream>

namespace nm {
namespace glsl {

std::string GlslGenerator::compileToGlslFunction(InputLink &inputLink, OutputLink &outputLink, std::string name)
{
    std::stringstream sl;
    GlslGenerator generator;

    sl << source_noise2d;

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
    auto moduleTypeName = module.getType().getName();
    std::unique_ptr<BodyGenerator> body;
    std::unique_ptr<DefaultsGenerator> defaults;
    body.reset(new SimpleBodyGenerator("//empty body\n"));
    defaults.reset(new ZeroDefaultsGenerator(module));

    //mah giant if

    //1D modules
    if (moduleTypeName == "add1") {
        body.reset(new SimpleBodyGenerator(
            "float result = lhs + rhs;\n"
        ));
    } else if (moduleTypeName == "sub1") {
        body.reset(new SimpleBodyGenerator(
            "float result = lhs - rhs;\n"
        ));
    } else if (moduleTypeName == "mul1") {
        body.reset(new SimpleBodyGenerator(
            "float result = lhs * rhs;\n"
        ));
    } else if (moduleTypeName == "mod") {
        body.reset(new SimpleBodyGenerator(
            "float result = mod(dividend, divisor);\n"
        ));

    //2D modules
    } else if (moduleTypeName == "add2") {
        body.reset(new SimpleBodyGenerator(
            "vec2 result = lhs + rhs;\n"
        ));
    } else if (moduleTypeName == "sub2") {
        body.reset(new SimpleBodyGenerator(
            "vec2 result = lhs - rhs;\n"
        ));
    } else if (moduleTypeName == "mul2") {
        body.reset(new SimpleBodyGenerator(
            "vec2 result = lhs * rhs;\n"
        ));
    } else if (moduleTypeName == "demux2") {
        body.reset(new SimpleBodyGenerator(
            "float x = m.x;\n"
            "float y = m.y;\n"
        ));
    } else if (moduleTypeName == "mux2") {
        body.reset(new SimpleBodyGenerator(
            "vec2 m = vec2(x, y);\n"
        ));
    } else if (moduleTypeName == "noise2") {
        body.reset(new SimpleBodyGenerator(
            "float result = snoise(pos);\n"
        ));

    //3D modules
    } else if (moduleTypeName == "add3") {
        body.reset(new SimpleBodyGenerator(
            "vec3 result = lhs + rhs;\n"
        ));
    } else if (moduleTypeName == "sub3") {
        body.reset(new SimpleBodyGenerator(
            "vec3 result = lhs - rhs;\n"
        ));
    } else if (moduleTypeName == "mul3") {
        body.reset(new SimpleBodyGenerator(
            "vec3 result = lhs * rhs;\n"
        ));
    } else if (moduleTypeName == "demux3") {
        body.reset(new SimpleBodyGenerator(
            "float x = m.x;\n"
            "float y = m.y;\n"
            "float z = m.z;\n"
        ));
    } else if (moduleTypeName == "mux3") {
        body.reset(new SimpleBodyGenerator(
            "vec3 m = vec3(x, y, z);\n"
        ));

    //lets ask superclass if it knows something useful
    } else {
        return InlineGenerator::getModuleGenerator(module);
    }
    return std::unique_ptr<ModuleGenerator>{new CompositeModuleGenerator(std::move(body), std::move(defaults))};
}

GlslGenerator::GlslGenerator():
    InlineGenerator()
{
}

} // namespace glsl
} // namespace nm
