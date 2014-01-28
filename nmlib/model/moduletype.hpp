#ifndef NM_MODULETYPE_HPP
#define NM_MODULETYPE_HPP

#include <vector>
#include <string>

namespace nm {

class ModuleOutput;
class ModuleInput;

/**
 * @brief Describes a module and its inputs and outputs.
 */
class ModuleType
{
public:
    explicit ModuleType(const std::string &name, const std::string &description);
    std::string getName() const {return m_name;}
    std::string getDescription() const {return m_description;}
    const ModuleInput *getInput(std::string name) const;
    const ModuleOutput *getOutput(std::string name) const;
    std::vector<ModuleOutput*> outputs() const;
    std::vector<ModuleInput*> inputs() const;
private:
    const std::string m_name;
    const std::string m_description;
    std::vector<ModuleInput> m_inputs;
    std::vector<ModuleOutput> m_outputs;
};

} // namespace nm

#endif // NM_MODULETYPE_HPP
