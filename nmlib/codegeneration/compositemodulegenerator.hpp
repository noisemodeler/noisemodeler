#ifndef NM_COMPOSITEMODULEGENERATOR_HPP
#define NM_COMPOSITEMODULEGENERATOR_HPP

#include <nmlib/codegeneration/modulegenerator.hpp>

#include <memory>

namespace nm {

class InlineGenerator;

class CompositeModuleGenerator : public ModuleGenerator
{
public:
    CompositeModuleGenerator(std::unique_ptr<BodyGenerator> bodyGenerator,
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

#endif // NM_COMPOSITEMODULEGENERATOR_HPP
