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
 * @ingroup model
 * @brief An instantiated ModuleType. A node in a function graph.
 *
 * A module is a part of a node in a Graph.
 * It has a corresponding ModuleType, which describes some sort
 * of mathematical function or algorithm.
 * A module may be thought of a configuration for a function
 * call.
 *
 * A Module has a number of InputLink%s and OutputLink%s that may be
 * connected to other Module%s InputLink%s and OutputLink%s.
 * 
 * Connections can be changed by using the getters for these InputLink%s
 * and OutputLink%s. One InputLink exists for each ModuleInput in the
 * ModuleType of the Module. The same applies for outputs.
 *
 * Usually create by Graph::createModule
 */
class Module : public UserDataProvider
{
public:
    /** @brief Constructor.
     *
     * Consider using Graph::createModule() instead if your goal is to add the module to a graph.
     */
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
    const InputLink *getInput(std::string name) const;
    InputLink *getInput(unsigned int i);
    const InputLink *getInput(unsigned int i) const;
    unsigned int getInputSize() const;
    std::vector<InputLink*> getInputs();

    //outputs
    OutputLink *getOutput(std::string name);
    const OutputLink *getOutput(std::string name) const;
    OutputLink *getOutput(unsigned int i);
    const OutputLink *getOutput(unsigned int i) const;
    unsigned int getOutputSize() const;
    std::vector<OutputLink*> getOutputs();

    /**
     * @brief disconnects module by unlinking all InputLink%s and OutputLink%s of this module.
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
    /** @brief This signal is emitted when the name of the Module is changed */
    signal<void (Module&, const std::string&)> nameChanged;
    /** @brief This signal is emitted when the description of the Module is changed */
    signal<void (Module&, const std::string&)> descriptionChanged;
    /** @brief This signal is emitted before the Module is destroyed */
    signal<void (Module&)> destroying;
    /** @brief This signal is emitted after an input has been added */
    signal<void (Module&, InputLink&)> addedInputLink;
    /** @brief This signal is emitted after an input has been removed */
    signal<void (Module&, const ModuleInput&)> removedInputLink;
    /** @brief This signal is emitted after an output has been added */
    signal<void (Module&, OutputLink&)> addedOutputLink;
    /** @brief This signal is emitted after an output has been removed */
    signal<void (Module&, const ModuleOutput&)> removedOutputLink;
    /** @brief This signal is emitted if changes have been made to the graph that may influence this Module%'s output signals */
    signal<void (Module&)> dependenciesChanged;

    //static methods
    static std::vector<Module *> getDependenciesSorted(const std::vector<OutputLink *> &outputs,
                                                    const std::set<InputLink *> &ignoreInputs = decltype(ignoreInputs){});
    static std::vector<const Module *> getDependenciesSorted(const std::vector<const OutputLink *> &outputs,
                                                    const std::set<const InputLink *> &ignoreInputs = decltype(ignoreInputs){});
    static void topologicallyTraverseDependencies(const std::vector<OutputLink*> &outputs, std::function<void(Module&)> visitor,
                                                  const std::set<InputLink*> &ignoreInputs = decltype(ignoreInputs){});
    static void topologicallyTraverseDependencies(const std::vector<const OutputLink*> &outputs, std::function<void(const Module&)> visitor,
                                                  const std::set<const InputLink*> &ignoreInputs = decltype(ignoreInputs){});

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
