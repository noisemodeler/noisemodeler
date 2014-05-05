#ifndef NM_GLSLGENERATOR_HPP
#define NM_GLSLGENERATOR_HPP

#include <nmlib/model.hpp>
#include <nmlib/codegeneration/inlinegenerator.hpp>

namespace nm {
namespace glsl {

/**
 * @brief Generates glsl code to evaluate function graphs using OpenGL 3.0 shaders
 * @ingroup codegeneration
 */
class GlslGenerator : InlineGenerator
{
public:
    static std::string compileToGlslFunction(InputLink& inputLink, OutputLink &outputLink, std::string name);

private:
    GlslGenerator();

protected:
    virtual void genTypeKeyword(const SignalType &signalType, std::ostream &out) override;
    virtual std::unique_ptr<nm::ModuleGenerator> getModuleGenerator(Module &module) override;
};

} // namespace glsl
} // namespace nm

#endif // NM_GLSLGENERATOR_HPP
