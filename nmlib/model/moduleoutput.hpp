#ifndef NM_MODULEOUTPUT_HPP
#define NM_MODULEOUTPUT_HPP

#include <string>

namespace nm {

class SignalType;

/**
 * @brief Describes one of a ModuleType's outputs
 */
class ModuleOutput
{
public:
    explicit ModuleOutput(std::string name, const SignalType &type): c_name(name), c_type(type){}

    std::string getName() const {return c_name;}
    const SignalType &getSignalType() const {return c_type;}
private:
    const std::string c_name;
    const SignalType &c_type;
};

} // namespace nm

#endif // NM_MODULEOUTPUT_HPP
