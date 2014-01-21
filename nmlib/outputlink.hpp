#ifndef NM_OUTPUTLINK_HPP
#define NM_OUTPUTLINK_HPP

namespace nm {

class Module;
class ModuleOutput;
class InputLink;

class OutputLink
{
public:
    OutputLink(Module* owner, const ModuleOutput* type):p_owner(owner), p_type(type){}
    const ModuleInput* const p_type;
    Module* const p_owner;
private:
    set<InputLink*> m_inputLinks;
};

} // namespace nm

#endif // NM_OUTPUTLINK_HPP
