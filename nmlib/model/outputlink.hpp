#ifndef NM_OUTPUTLINK_HPP
#define NM_OUTPUTLINK_HPP

#include <nmlib/util/userdataprovider.hpp>
#include <nmlib/util/signals.hpp>

#include <set>

namespace nm {

class Module;
class ModuleOutput;
class InputLink;

/**
 * @brief an output of a Module
 * @ingroup model
 *
 * OutputLink%s are created by the library itself when instantiation a new Module
 */
class OutputLink : public UserDataProvider
{
public:
    /**
     * @brief OutputLink
     * @param owner which module this is an output of
     * @param type which ModuleOutput this is an outputLink for
     */
    explicit OutputLink(Module &owner, const ModuleOutput &type):
        m_owner(owner),
        c_moduleOutput(type),
        m_inputLinks()
    {}
    virtual ~OutputLink();

    /**
     * @brief Add a connection from this OutputLink to the specified InputLink
     * @param input
     * @return Whether a new link was added.
     */
    bool addLink(InputLink &input);

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

    unsigned int numLinks(){
        return m_inputLinks.size();
    }
    InputLink* getLink(unsigned int index);

    const Module &getOwner() const {return m_owner;}
    Module &getOwner() {return m_owner;}
    const ModuleOutput &getModuleOutput() const {return c_moduleOutput;}

    //signals
    signal<void (OutputLink&)> linksChanged;
    signal<void (OutputLink&)> destroying;

private:
    Module &m_owner;
    const ModuleOutput &c_moduleOutput;
    std::vector<InputLink *> m_inputLinks;
};

} // namespace nm

#endif // NM_OUTPUTLINK_HPP
