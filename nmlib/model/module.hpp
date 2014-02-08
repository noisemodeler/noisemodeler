#ifndef NM_MODULE_H
#define NM_MODULE_H

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/util/signals.hpp>

#include <vector>
#include <string>
#include <memory>

#include <nmlib/util/signals.hpp>

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
    void setName(std::string name);

    //inputs
    InputLink *getInput(std::string getName);
    InputLink *getInput(unsigned int i);
    unsigned int getInputSize() const;

    //outputs
    OutputLink *getOutput(std::string getName);
    OutputLink *getOutput(unsigned int i);
    unsigned int getOutputSize() const;

    void onAddedModuleInput(const ModuleInput &moduleInput);
    void onAddedModuleOutput(const ModuleOutput &moduleOutput);

    //signals
    signal<void (Module&, const std::string&)> nameChanged;
    signal<void (Module&)> destroying;
    signal<void (Module&, InputLink&)> addedInputLink;
    signal<void (Module&, OutputLink&)> addedOutputLink;


private:
    explicit Module(const ModuleType& getType, std::string getName);
    const ModuleType& c_type;
    std::string m_name;
    std::vector<std::unique_ptr<InputLink>> m_inputs;
    std::vector<std::unique_ptr<OutputLink>> m_outputs;
};

} // namespace nm

#endif // NM_MODULE_H
