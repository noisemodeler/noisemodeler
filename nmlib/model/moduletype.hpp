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
    explicit ModuleType();
    const ModuleInput* getInput(std::string name) const;
    const ModuleOutput* getOutput(std::string name) const;
//    std::vector<ModuleOutput*> outputs() const;
//    std::vector<ModuleInput*> inputs() const;
private:

};

} // namespace nm

#endif // NM_MODULETYPE_HPP