#ifndef NM_MODULEINPUT_HPP
#define NM_MODULEINPUT_HPP

#include <string>

namespace nm {

class SignalType;
class ModuleType;

/**
 * @brief Describes one of a ModuleType's inputs.
 */
class ModuleInput
{
public:
    explicit ModuleInput(std::string name, const SignalType &signalType, const ModuleType &moduleType):
        c_name(name),
        c_signalType(signalType),
        c_moduleType(moduleType)
    {}

    std::string getName() const {return c_name;}
    const SignalType &getSignalType() const {return c_signalType;}
private:
    const std::string c_name;
    const SignalType &c_signalType;
    const ModuleType &c_moduleType;
};

} // namespace nm

#endif // NM_MODULEINPUT_HPP
