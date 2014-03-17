#ifndef NM_INPUTLINK_HPP
#define NM_INPUTLINK_HPP

#include <nmlib/util/userdataprovider.hpp>
#include <nmlib/util/signals.hpp>

namespace nm {

class Module;
class ModuleInput;
class OutputLink;
class SignalValue;

/**
 * @brief Describes which output of which node a ModuleInput of a specific Module is connected to.
 */
class InputLink : public UserDataProvider
{
public:
    explicit InputLink(Module &owner, const ModuleInput &type);
    virtual ~InputLink();
    bool link(OutputLink &output);
    void unlink();
    const Module& getOwner() const {return m_owner;}
    Module& getOwner() {return m_owner;}
    const ModuleInput& getModuleInput() const {return c_moduleInput;}
    const OutputLink* getOutputLink() const {return p_outputLink;}
    OutputLink* getOutputLink() {return p_outputLink;}
    SignalValue getUnlinkedValue();

    //signals
    signal<void (InputLink&)> linkChanged;
    signal<void (InputLink&)> destroying;

private:
    Module& m_owner;
    const ModuleInput& c_moduleInput;
    OutputLink* p_outputLink;
};

} // namespace nm

#endif // NM_INPUTLINK_HPP
