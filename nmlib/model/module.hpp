#ifndef NM_MODULE_H
#define NM_MODULE_H

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>

#include <map>

namespace nm {

class ModuleType;
class ModuleInput;
class ModuleOutput;

/**
 * @brief A node in an expression tree.
 */
class Module
{
public:
    explicit Module(const ModuleType& type):m_type(type){}
    const ModuleType& type(){return m_type;}
private:
    const ModuleType& m_type;
    std::map<const ModuleInput*, InputLink> m_inputs;
    std::map<const ModuleOutput*, OutputLink> m_outputs;
};

} // namespace nm

#endif // NM_MODULE_H
