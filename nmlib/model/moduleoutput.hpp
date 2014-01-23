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
    const std::string m_name;
    const SignalType * const p_type;
    explicit ModuleOutput(std::string name, SignalType *type): m_name(name), p_type(type){}
};

} // namespace nm

#endif // NM_MODULEOUTPUT_HPP
