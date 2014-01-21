#ifndef NM_OUTPUTLINK_HPP
#define NM_OUTPUTLINK_HPP

#include <set>

namespace nm {

class Module;
class ModuleOutput;
class InputLink;

class OutputLink
{
public:
    OutputLink(Module *owner, const ModuleOutput *type):p_owner(owner), p_type(type){}
    bool addLink(InputLink *input);
    bool unlink(InputLink *input);
    void unlinkAll();

    const ModuleOutput * const p_type;
    Module * const p_owner;
private:
    std::set<InputLink *> m_inputLinks;
};

} // namespace nm

#endif // NM_OUTPUTLINK_HPP
