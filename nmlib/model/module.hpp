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
    explicit Module(const ModuleType& getType, std::string getName);
    const ModuleType& getType() const {return c_type;}
    const std::string getName() const {return c_name;}
    InputLink *getInput(std::string getName);
    OutputLink *getOutput(std::string getName);

private:
    const ModuleType& c_type;
    const std::string c_name;
    std::vector<InputLink> m_inputs;
    std::vector<OutputLink> m_outputs;
};

} // namespace nm

#endif // NM_MODULE_H
