#ifndef NM_MODULEOUTPUT_HPP
#define NM_MODULEOUTPUT_HPP

#include <string>

namespace nm {

class SignalType;
class ModuleType;

/**
 * @brief Describes one of a ModuleType's outputs
 */
class ModuleOutput
{
public:
    explicit ModuleOutput(std::string name, const SignalType &signalType, const ModuleType& moduleType):
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

#endif // NM_MODULEOUTPUT_HPP
