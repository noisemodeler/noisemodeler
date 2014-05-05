#ifndef NM_FUNCTIONCALLBODYGENERATOR_HPP
#define NM_FUNCTIONCALLBODYGENERATOR_HPP

#include <nmlib/codegeneration/inlinegenerator.hpp>
#include <nmlib/codegeneration/bodygenerator.hpp>

namespace nm {

/**
 * @brief The FunctionCallBodyGenerator class
 * @ingroup codegeneration
 */
class FunctionCallBodyGenerator : public BodyGenerator
{
public:
    template<typename T>
    FunctionCallBodyGenerator(T** t):
        m_fcall(std::forward(t)){}
    virtual void generateBody(InlineGenerator &gen, std::ostream &out) override;
private:
    FunctionCall m_fcall;
};

} // namespace nm

#endif // NM_FUNCTIONCALLBODYGENERATOR_HPP
