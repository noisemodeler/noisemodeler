#ifndef NM_CONCRETEMODULEGENERATOR_HPP
#define NM_CONCRETEMODULEGENERATOR_HPP

#include <nmlib/codegeneration/modulegenerator.hpp>

#include <memory>

namespace nm {

class InlineGenerator;

/**
 * @brief The ConcreteModuleGenerator class
 * @ingroup codegeneration
 */
class ConcreteModuleGenerator : public ModuleGenerator
{
public:
    ConcreteModuleGenerator(std::unique_ptr<BodyGenerator> bodyGenerator,
                             std::unique_ptr<DefaultsGenerator> defaultsGenerator = {}):
        m_bodyGenerator(std::move(bodyGenerator)),
        m_defaultsGenerator(std::move(defaultsGenerator))
    {
    }

    // BodyGenerator interface
    virtual void generateBody(InlineGenerator &gen, std::ostream &out) override {m_bodyGenerator->generateBody(gen, out);}

    // DefaultsGenerator interface
    virtual void generateDefaults(InlineGenerator &gen, std::ostream &out) override {m_defaultsGenerator->generateDefaults(gen, out);}

private:
    std::unique_ptr<BodyGenerator> m_bodyGenerator;
    std::unique_ptr<DefaultsGenerator> m_defaultsGenerator;
};

} // namespace nm

#endif // NM_CONCRETEMODULEGENERATOR_HPP
