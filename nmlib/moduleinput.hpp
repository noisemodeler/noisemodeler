#ifndef NM_MODULEINPUT_HPP
#define NM_MODULEINPUT_HPP

#include <string>

namespace nm {

class SignalType;

class ModuleInput
{
public:
    const std::string m_name;
    const SignalType * const p_type;
    ModuleInput(std::string name, SignalType *type): m_name(name), p_type(type){}
};

} // namespace nm

#endif // NM_MODULEINPUT_HPP
