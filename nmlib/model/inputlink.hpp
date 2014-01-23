#ifndef NM_INPUTLINK_HPP
#define NM_INPUTLINK_HPP

namespace nm {

class Module;
class ModuleInput;
class OutputLink;

/**
 * @brief Describes which output of which node a ModuleInput of a specific Module is connected to.
 */
class InputLink
{
public:
    explicit InputLink(Module *owner, const ModuleInput *type):p_owner(owner), p_type(type), p_outputLink(nullptr){}
    bool link(OutputLink *output);
    void unlink();

    Module* const p_owner;
    const ModuleInput* const p_type;
private:
    OutputLink* p_outputLink;
};

} // namespace nm

#endif // NM_INPUTLINK_HPP
