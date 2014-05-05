#ifndef NM_SIMPLEBODYGENERATOR_HPP
#define NM_SIMPLEBODYGENERATOR_HPP

#include <nmlib/codegeneration/bodygenerator.hpp>

namespace nm {

/**
 * @brief The SimpleBodyGenerator class
 * @ingroup codegeneration
 */
class SimpleBodyGenerator : public BodyGenerator
{
public:
    SimpleBodyGenerator(std::string body):
        m_body(body){
    }

    // BodyGenerator interface
    virtual void generateBody(InlineGenerator &/*gen*/, std::ostream &out){out << m_body;}

private:
    std::string m_body;
};

} // namespace nm

#endif // NM_SIMPLEBODYGENERATOR_HPP
