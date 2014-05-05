#ifndef NM_COMPOSITEMODULEGENERATOR_H
#define NM_COMPOSITEMODULEGENERATOR_H

#include <nmlib/codegeneration/modulegenerator.hpp>

namespace nm {

/**
 * @brief The CompositeModuleGenerator class
 * @ingroup codegeneration
 */
class CompositeModuleGenerator : public nm::ModuleGenerator
{
public:
    CompositeModuleGenerator();

    // DefaultsGenerator interface
public:
    void generateDefaults(InlineGenerator &gen, std::ostream &out) override;

    // BodyGenerator interface
public:
    void generateBody(InlineGenerator &gen, std::ostream &out) override;
};

} // namespace nm

#endif // NM_COMPOSITEMODULEGENERATOR_H
