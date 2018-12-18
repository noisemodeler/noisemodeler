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
 * @brief Describes one of a ModuleType's inputs (name, SignalType, default value).
 * @ingroup model
 */
class ModuleInput : public UserDataProvider
{
public:
    //TODO this constructor might not be needed
    explicit ModuleInput(std::string name, SignalType signalType, const ModuleType &moduleType) :
        ModuleInput(name, SignalValue(signalType), moduleType) //zero as default value
    {}
    explicit ModuleInput(std::string name, SignalValue defaultValue, const ModuleType &) :
        c_name(name),
        c_signalType(defaultValue.getSignalType()), //TODO redundants?
        c_defaultValue(defaultValue)
    {}
    ~ModuleInput(){destroying(*this);}

    std::string getName() const {return c_name;}
    SignalType getSignalType() const {return c_signalType;}
    SignalValue getDefaultValue() const {return c_defaultValue;}

    signal<void(ModuleInput&)> destroying;
private:
    const std::string c_name;
    const SignalType c_signalType;//TODO this may be inferred from signalvalue?
    const SignalValue c_defaultValue;//TODO consider relaxing the constant requirement on this member
};

} // namespace nm

#endif // NM_MODULEINPUT_HPP
