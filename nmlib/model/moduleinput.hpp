#ifndef NM_MODULEINPUT_HPP
#define NM_MODULEINPUT_HPP

#include <string>

namespace nm {

class SignalType;

/**
 * @brief Describes one of a ModuleType's inputs.
 */
class ModuleInput
{
public:
    const std::string m_name;
    const SignalType * const p_type;
    explicit ModuleInput(std::string name, SignalType *type): m_name(name), p_type(type){}
private:
};

} // namespace nm

#endif // NM_MODULEINPUT_HPP
