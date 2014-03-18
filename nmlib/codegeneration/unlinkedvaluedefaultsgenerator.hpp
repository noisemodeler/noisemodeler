#ifndef NM_UNLINKEDVALUEDEFAULTSGENERATOR_HPP
#define NM_UNLINKEDVALUEDEFAULTSGENERATOR_HPP

#include <nmlib/codegeneration/defaultsgenerator.hpp>

namespace nm {

class Module;

class UnlinkedValueDefaultsGenerator : public DefaultsGenerator
{
public:
    UnlinkedValueDefaultsGenerator(Module& module):
        m_module(module)
    {}

    // DefaultsGenerator interface
    virtual void generateDefaults(InlineGenerator &gen, std::ostream &out) override;

private:
    Module& m_module; //TODO should be const
};

} // namespace nm

#endif // NM_UNLINKEDVALUEDEFAULTSGENERATOR_HPP
