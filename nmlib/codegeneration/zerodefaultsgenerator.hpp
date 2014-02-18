#ifndef NM_ZERODEFAULTSGENERATOR_HPP
#define NM_ZERODEFAULTSGENERATOR_HPP

#include <nmlib/codegeneration/defaultsgenerator.hpp>

namespace nm {

class Module;

class ZeroDefaultsGenerator : public DefaultsGenerator{
public:
    ZeroDefaultsGenerator(Module& module):m_module(module){}
    virtual void generateDefaults(InlineGenerator &gen, std::ostream &out);
private:
    Module &m_module;
};

} // namespace nm

#endif // NM_ZERODEFAULTSGENERATOR_HPP
