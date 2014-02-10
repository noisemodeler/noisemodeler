#include "glcompiler.hpp"

#include <sstream>

namespace nm {

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

    //function end
    sl << "}\n";
    return sl.str();
}

} // namespace nm
