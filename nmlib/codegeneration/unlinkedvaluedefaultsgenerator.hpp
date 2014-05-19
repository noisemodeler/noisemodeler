#ifndef NM_UNLINKEDVALUEDEFAULTSGENERATOR_HPP
#define NM_UNLINKEDVALUEDEFAULTSGENERATOR_HPP

#include <nmlib/codegeneration/defaultsgenerator.hpp>

namespace nm {

class Module;

class UnlinkedValueDefaultsGenerator : public DefaultsGenerator
{
public:
    UnlinkedValueDefaultsGenerator(const Module& module):
        m_module(module)
    {}

    // DefaultsGenerator interface
    virtual void generateDefaults(InlineGenerator &gen, std::ostream &out) override;

private:
    const Module& m_module;
};

} // namespace nm

#endif // NM_UNLINKEDVALUEDEFAULTSGENERATOR_HPP
