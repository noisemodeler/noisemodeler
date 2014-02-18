#ifndef NM_GLSLGENERATOR_HPP
#define NM_GLSLGENERATOR_HPP

#include <nmlib/model.hpp>
#include <nmlib/codegeneration/inlinegenerator.hpp>

namespace nm {

class GlslGenerator : InlineGenerator
{
public:
    static std::string compileToGlslFunction(InputLink& inputLink, OutputLink &outputLink, std::string name);

private:
    GlslGenerator();

private:
};

} // namespace nm

#endif // NM_GLSLGENERATOR_HPP
