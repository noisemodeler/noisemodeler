#ifndef NM_MODULE_H
#define NM_MODULE_H

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>


#include <vector>
#include <string>
#include <memory>

namespace nm {

class ModuleType;
class ModuleInput;
class ModuleOutput;

/**
 * @brief A node in an expression tree.
 */
class Module : public UserDataProvider
{
public:
    ~Module();
    static std::unique_ptr<Module> create(const ModuleType &type, std::string name);
    const ModuleType& getType() const {return c_type;}
    const std::string getName() const {return m_name;}
    void setName(std::string name){m_name=name;}
    InputLink *getInput(std::string getName);
    OutputLink *getOutput(std::string getName);
    void onAddedModuleInput(const ModuleInput &moduleInput);
    void onAddedModuleOutput(const ModuleOutput &moduleOutput);

    //signals

private:
    explicit Module(const ModuleType& getType, std::string getName);
    const ModuleType& c_type;
    std::string m_name;
    std::vector<InputLink> m_inputs;
    std::vector<OutputLink> m_outputs;
};

} // namespace nm

#endif // NM_MODULE_H
