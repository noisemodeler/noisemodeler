#ifndef NM_INPUTLINK_HPP
#define NM_INPUTLINK_HPP

namespace nm {

class Module;
class ModuleInput;
class OutputLink;

class InputLink
{
public:
    InputLink(Module* owner, const ModuleInput* type):p_owner(owner), p_type(type), p_outputLink(nullptr){}
private:
    const ModuleInput* const p_type;
    Module* const p_owner;
    OutputLink* p_outputLink;
};

} // namespace nm

#endif // NM_INPUTLINK_HPP
