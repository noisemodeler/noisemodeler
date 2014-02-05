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
    explicit InputLink(const Module &owner, const ModuleInput &type):
        c_owner(owner),
        c_moduleInput(type),
        p_outputLink(nullptr)
    {}
    bool link(OutputLink &output);
    void unlink();
    const Module& getOwner() const {return c_owner;}
    const ModuleInput& getModuleInput() const {return c_moduleInput;}
    const OutputLink* getOutputLink() const {return p_outputLink;}

private:
    const Module& c_owner;
    const ModuleInput& c_moduleInput;
    OutputLink* p_outputLink;
};

} // namespace nm

#endif // NM_INPUTLINK_HPP
