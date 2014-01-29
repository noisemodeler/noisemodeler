#ifndef NM_MODULETYPE_HPP
#define NM_MODULETYPE_HPP

#include <vector>
#include <string>

namespace nm {

class ModuleOutput;
class ModuleInput;

/**
 * @brief Interface for describing a module and its inputs and outputs.
 */
class ModuleType
{
public:
    virtual ~ModuleType(){}
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual const ModuleInput *getInput(std::string name) const = 0;
    virtual const ModuleOutput *getOutput(std::string name) const = 0;
//    virtual std::vector<ModuleOutput*> outputs() const;
//    virtual std::vector<ModuleInput*> inputs() const;
};

} // namespace nm

#endif // NM_MODULETYPE_HPP
