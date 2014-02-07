#ifndef NM_MODULETYPE_HPP
#define NM_MODULETYPE_HPP

#include <vector>
#include <string>

#include <nmlib/model/noncopyable.hpp>
#include <nmlib/model/userdataprovider.hpp>

namespace nm {

class Module;
class ModuleOutput;
class ModuleInput;

/**
 * @brief Interface for describing a module and its inputs and outputs.
 */
class ModuleType : NonCopyable, public UserDataProvider
{
public:
    virtual ~ModuleType(){}
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual const ModuleInput *getInput(std::string name) const = 0;
    virtual const ModuleOutput *getOutput(std::string name) const = 0;
    virtual std::vector<const ModuleOutput*> outputs() const = 0;
    virtual std::vector<const ModuleInput*> inputs() const = 0;
    virtual void onCreatedModule(Module &module) = 0;
    virtual void onDestroyingModule(Module *module) = 0;
};

} // namespace nm

#endif // NM_MODULETYPE_HPP
