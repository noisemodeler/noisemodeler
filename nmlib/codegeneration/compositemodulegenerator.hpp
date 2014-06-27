#ifndef NM_COMPOSITEMODULEGENERATOR_H
#define NM_COMPOSITEMODULEGENERATOR_H

#include <nmlib/codegeneration/modulegenerator.hpp>
#include <nmlib/codegeneration/unlinkedvaluedefaultsgenerator.hpp>

namespace nm {

/**
 * @brief Generator for modules having composite module types
 * @ingroup codegeneration
 */
class CompositeModuleGenerator : public nm::ModuleGenerator
{
public:
    CompositeModuleGenerator(const Module& module);

    // DefaultsGenerator interface
public:
    void generateDefaults(InlineGenerator &gen, std::ostream &out) override;

    // BodyGenerator interface
public:
    void generateBody(InlineGenerator &gen, std::ostream &out) override;

private:
    const Module& m_module;

};

} // namespace nm

#endif // NM_COMPOSITEMODULEGENERATOR_H
