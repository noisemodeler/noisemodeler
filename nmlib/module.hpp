#ifndef NM_MODULE_H
#define NM_MODULE_H

#include <nmlib/inputlink.hpp>
#include <nmlib/outputlink.hpp>

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
    Module(const ModuleType* type):p_type(type){}
private:
    const ModuleType* const p_type;
    std::map<const ModuleInput*, InputLink> m_inputs;
    std::map<const ModuleOutput*, OutputLink> m_output;
};

} // namespace nm

#endif // NM_MODULE_H
