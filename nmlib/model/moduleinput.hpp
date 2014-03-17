#ifndef NM_MODULEINPUT_HPP
#define NM_MODULEINPUT_HPP

#include <nmlib/model/signaltype.hpp>
#include <nmlib/model/signalvalue.hpp>
#include <nmlib/util/userdataprovider.hpp>

#include <nmlib/util/signals.hpp>

#include <string>

namespace nm {

class SignalType;
class ModuleType;

/**
 * @brief Describes one of a ModuleType's inputs.
 */
class ModuleInput : public UserDataProvider
{
public:
    explicit ModuleInput(std::string name, SignalType signalType, const ModuleType &moduleType):
        ModuleInput(name, signalType, moduleType, SignalValue(signalType)) //zero as default value
    {}
    explicit ModuleInput(std::string name, SignalType signalType, const ModuleType &moduleType, SignalValue defaultValue):
        c_name(name),
        c_signalType(signalType),
        c_signalValue(defaultValue),
        c_moduleType(moduleType)
    {}
    ~ModuleInput(){destroying(*this);}
//    ModuleInput(ModuleInput&&) = default;
//    ModuleInput(ModuleInput&) = default;

    std::string getName() const {return c_name;}
    const SignalType &getSignalType() const {return c_signalType;}

    signal<void(ModuleInput&)> destroying;
private:
    const std::string c_name;
    const SignalType c_signalType;//TODO this may be inferred from signalvalue?
    const SignalValue c_signalValue;
    const ModuleType &c_moduleType;
};

} // namespace nm

#endif // NM_MODULEINPUT_HPP
