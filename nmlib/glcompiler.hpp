#ifndef NM_GLCOMPILER_HPP
#define NM_GLCOMPILER_HPP

#include <nmlib/model.hpp>

namespace nm {

class GLCompiler
{
public:
    static std::string compileToGlslFunction(InputLink& inputLink, OutputLink &outputLink, std::string name);
protected:
    GLCompiler();
};

} // namespace nm

#endif // NM_GLCOMPILER_HPP
