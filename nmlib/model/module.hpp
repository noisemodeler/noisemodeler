#ifndef NM_MODULE_H
#define NM_MODULE_H

#include <nmlib/util/signals.hpp>
#include <nmlib/util/userdataprovider.hpp>

#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <set>

namespace nm {

class InputLink;
class OutputLink;
class ModuleType;
class ModuleInput;
class ModuleOutput;

/**
 * @brief An instantiated ModuleType.
 * @ingroup model
 *
 * A function node in a Graph.
 *
 * Usually create by Graph::createModule
 */
class Module : public UserDataProvider
{
public:
    explicit Module(const ModuleType &type, std::string name, std::string description = "");
    virtual ~Module();
    const ModuleType& getType() const {return m_type;}
    const ModuleType& getType() {return m_type;}
    const std::string getName() const {return m_name;}
    void setName(std::string name);
    const std::string getDescription() const {return m_description;}
    void setDescription(std::string description);


    //inputs
    InputLink *getInput(std::string name);
    InputLink *getInput(unsigned int i);
    const InputLink *getInput(unsigned int i) const;
    unsigned int getInputSize() const;
    std::vector<InputLink*> getInputs();

    //outputs
    OutputLink *getOutput(std::string name);
    OutputLink *getOutput(unsigned int i);
    unsigned int getOutputSize() const;
    std::vector<OutputLink*> getOutputs();

    /**
     * @brief disconnects module by unlinking all inputlinks outputlinks
     */
    void disconnect();

    //module graph convenience functions
    void traverseChildren(std::function<void (const Module &)> callback) const;
    void traverseParents(std::function<void(const Module&)> callback) const;
    //for now, these two includes this node as well
    void traverseDescendants(std::function<void(const Module&)> callback) const;
    void traverseDescendants(std::function<void(Module&)> callback);
    void traverseAncestors(std::function<void(const Module&)> callback) const;

    /**
     * @return the number of modules above this one
     */
    int getDepth() const;
    /**
     * @return the number of modules below this one
     */
    int getHeight() const;

    //signals
    signal<void (Module&, const std::string&)> nameChanged;
    signal<void (Module&, const std::string&)> descriptionChanged;
    signal<void (Module&)> destroying;
    signal<void (Module&, InputLink&)> addedInputLink;
    signal<void (Module&, const ModuleInput&)> removedInputLink; //TODO hook up
    signal<void (Module&, OutputLink&)> addedOutputLink;
    signal<void (Module&, const ModuleOutput&)> removedOutputLink; //TODO hook up
    signal<void (Module&)> dependenciesChanged;

    //static methods
    static std::vector<Module *> getDependenciesSorted(const std::vector<OutputLink*> &outputs,
                                                    const std::set<InputLink *> &ignoreInputs = {});
    static void topologicallyTraverseDependencies(const std::vector<OutputLink*> &outputs, std::function<void(Module&)> visitor,
                                                  const std::set<InputLink*> &ignoreInputs = {});

private:
    bool removeInput(const ModuleInput& moduleInput);
    bool removeOutput(const ModuleOutput& moduleOutput);
    void createInputLink(const ModuleInput& moduleInput);
    void createOutputLink(const ModuleOutput& moduleInput);
    const ModuleType& m_type;
    std::string m_name, m_description;
    std::vector<std::unique_ptr<InputLink>> m_inputs;
    std::vector<std::unique_ptr<OutputLink>> m_outputs;

    //we need some connections to the moduletype to make sure links are added and removed as needed
    boost::signals2::scoped_connection m_moduleInputAddedCon, m_moduleInputRemovedCon;
    boost::signals2::scoped_connection m_moduleOutputAddedCon, m_moduleOutputRemovedCon;
};

} // namespace nm

#endif // NM_MODULE_H
