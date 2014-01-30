#ifndef NM_MODULE_H
#define NM_MODULE_H

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>

#include <vector>
#include <string>

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
    explicit Module(const ModuleType& type, std::string name);
    const ModuleType& type(){return c_type;}
    const std::string name(){return c_name;}
    InputLink *getInput(std::string name);
    OutputLink *getOutput(std::string name);

private:
    const ModuleType& c_type;
    const std::string c_name;
    std::vector<InputLink> m_inputs;
    std::vector<OutputLink> m_outputs;
};

} // namespace nm

#endif // NM_MODULE_H
