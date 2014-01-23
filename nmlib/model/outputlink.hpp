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
    explicit OutputLink(Module *owner, const ModuleOutput *type):p_owner(owner), p_type(type){}

    /**
     * @brief Add a connection from this OutputLink to the specified InputLink
     * @param input
     * @return Whether a new link was added.
     */
    bool addLink(InputLink *input);

    /**
     * @brief Remove the link an InputLink if it exists
     * @param input
     * @return Whether a link was removed
     */
    bool unlink(InputLink *input);

    /**
     * @brief Remove links to all inputs.
     *
     * This also removes the links from the inputs to the output
     */
    void unlinkAll();

    const ModuleOutput * const p_type;
    Module * const p_owner;
private:
    std::set<InputLink *> m_inputLinks;
};

} // namespace nm

#endif // NM_OUTPUTLINK_HPP
