#ifndef NM_MODULETYPE_HPP
#define NM_MODULETYPE_HPP

#include <nmlib/model/signaltype.hpp>

#include <nmlib/util/noncopyable.hpp>
#include <nmlib/util/userdataprovider.hpp>
#include <nmlib/util/signals.hpp>

#include <vector>
#include <string>
#include <memory>

namespace nm {

class Module;
class ModuleOutput;
class ModuleInput;
class Graph;
class OutputLink;
class SignalValue;

/**
 * @brief describes a recipe for a module and its inputs and outputs.
 */
class ModuleType : NonCopyable, public UserDataProvider
{
public:
    /**
     * @brief Module type category
     */
    enum class Category { //couldn't call it moduletypetype, cause that would be silly
        Primitive, /** A low-level module type, without a graph */
        Composite, /** A high-level module type, created as a composition of modules in a graph */
        GraphInput, /** A special module type for inputs of a graph */
        GraphOutput /** A special module type for outputs of a graph */
    };

    /**
     * @brief Simple Constructor for composite module types
     * @param name A unique identifier for the module type
     * @param description A comment or description of what kind of function the module type represents.
     */
    explicit ModuleType(std::string name, std::string description);

    /**
     * @param name A unique identifier for the module type
     * @param category Whether to create a composite, primitive, or special module type
     * @param description A comment or description of what kind of function the module type represents.
     */
    explicit ModuleType(std::string name, Category category = Category::Composite, std::string description = "");
    ~ModuleType();

    /**
     * @brief A unique identifier for the module type
     */
    std::string getName() const { return m_name; }
    void setName(std::string name);

    std::string getDescription() const { return m_description; }
    void setDescription(std::string description);
    /**
     * @brief A built-in module type is part of nmlib, and not created by the user.
     */
    bool isBuiltin() const { return !isComposite(); } //subject to change (some builtins may become composites in the future

    /**
     * @brief A composite module type is built from a graph of modules of other types
     */
    bool isComposite() const { return m_category == Category::Composite; }

    /**
     * @brief A primitive module type, is the opposite of a composite type.
     */
    bool isPrimitive() const { return m_category == Category::Primitive; } //consider if graphinput and graphoutput should be primitive as well?

    /**
     * @brief Some modules, like the ones representing inputs and outputs, 
     * may not be removed from their graphs.
     *
     * @return Whether modules of this type may be removed from their graphs
     */
    bool isRemovable() const { return m_removable; }

    /**
     * @brief A graph input module type represents the inputs of a composite module type.
     */
    bool isGraphInput() const { return m_category == Category::GraphInput; }

    /**
     * @brief A graph output module type represents the outputs of a composite module type.
     */
    bool isGraphOutput() const { return m_category == Category::GraphOutput; }

    /**
     * @brief Change whether modules of this type may be removed from graphs or not
     */
    void setRemovable(bool removable) { m_removable = removable; }

    //inputs
    //getters
    unsigned int numInputs() const { return m_inputs.size(); }
    const ModuleInput *getInput(std::string name) const;
    ModuleInput *getInput(std::string name);
    const ModuleInput *getInput(unsigned int index) const { return m_inputs.at(index).get(); }
    ModuleInput *getInput(unsigned int index) { return m_inputs.at(index).get(); }
    void eachModuleInput(std::function<void(const ModuleInput&)> f) const;
    void eachModuleInput(std::function<void(ModuleInput&)> f);
    //mutable stuff

    /**
     * @brief Add a new input to the module type
     * @param name The name to give the new input
     * @param signalType The type of the new input
     *
     * The default value for this input is set to zero
     */
    ModuleInput *addInput(std::string name, SignalType signalType);

    /**
     * @brief Add a new input to the module type
     * @param name The name to give the new input
     * @param defaultValue The default value for the new input
     *
     * The type of the new input is inferred from the value
     */
    ModuleInput *addInput(std::string name, SignalValue defaultValue);

    /**
     * @brief Removes an input from this module type
     * @param moduleInput A pointer to one of this ModuleType%'s inputs
     * @return true if an input was removed
     *
     * Instantiated Modules of this type are notified of this, and their
     * corresponding InputLink%s are automatically removed.
     */
    bool removeInput(ModuleInput *moduleInput);

    //outputs
    //getters
    unsigned int numOutputs() const { return m_outputs.size(); }
    const ModuleOutput *getOutput(std::string name) const;
    ModuleOutput *getOutput(std::string name);
    const ModuleOutput *getOutput(unsigned int index) const { return m_outputs.at(index).get(); }
    ModuleOutput *getOutput(unsigned int index) { return m_outputs.at(index).get(); }
    void eachModuleOutput(std::function<void(const ModuleOutput&)> f) const;
    void eachModuleOutput(std::function<void(ModuleOutput&)> f);
    //mutable stuff
    ModuleOutput *addOutput(std::string name, SignalType signalType);
    /**
     * @brief Removes an output from this module type
     * @param moduleOutput A pointer to one of this ModuleType%'s outputs
     * @return true if an output was removed
     *
     * Instantiated Modules of this type are notified of this, and their
     * corresponding OutputLink%s are automatically removed.
     */
    bool removeOutput(ModuleOutput *moduleOutput);

    /**
     * @brief Accessor for the graph of a composite module type
     * @return Returns a pointer to the Graph corresponding to this module type,
     * or nullptr if this is not a composite module type
     */
    Graph* getGraph() { return m_graph.get(); }

    /** 
     * @brief Immutable version of getGraph
     */
    const Graph* getGraph() const { return m_graph.get(); }
    /**
     * @brief Convenience method for exposing a part of the module graph as a new external output.
     *
     * This method only works for composite module types.
     */
    ModuleOutput *exportInternalOutput(OutputLink &outputLink, std::string externalName);

    //TODO enum and/or constant params

    //signals
    /** @brief This signal is emitted when the name of the moduleType changes */
    signal<void(ModuleType&, const std::string&)> nameChanged;
    /** @brief This signal is emitted when the description of the moduleType changes */
    signal<void(ModuleType&, const std::string&)> descriptionChanged;
    /** @brief This signal is emitted after an input has been added */
    signal<void(ModuleInput&)> inputAdded; 
    /** @brief This signal is emitted before an input is removed */
    signal<void(ModuleInput&)> removingInput; 
    /** @brief This signal is emitted after an input has been removed */
    signal<void(ModuleType&)> inputRemoved;
    /** @brief This signal is emitted after an output has been added */
    signal<void(ModuleOutput&)> outputAdded;
    /** @brief This signal is emitted before an output is removed */
    signal<void(ModuleOutput&)> removingOutput;
    /** @brief This signal is emitted after an output has been removed */
    signal<void(ModuleType&)> outputRemoved;
    /** @brief This signal is emitted before the type is destroyed */
    signal<void(ModuleType&)> destroying;
    //TODO more signals
//    signal<void(ModuleType&)> nameChanged;


    //implementation
private:
    std::string m_name, m_description;
    bool m_removable;
    const Category m_category; // these are special types of nodes that there can only be one of in each graph
                         // they also can't be copied

    std::vector<std::unique_ptr<ModuleInput>> m_inputs;
    std::vector<std::unique_ptr<ModuleOutput>> m_outputs;

    std::unique_ptr<Graph> m_graph; //if this is a composite module, it will have a graph of internal nodes, this is it.
    std::unique_ptr<ModuleType> m_inputModuleType; //if this is a composite module, it will have a special module type for inputs this is were its type will be stored
    std::unique_ptr<ModuleType> m_outputModuleType; //if this is a composite module, it will have a special module type for outputs
};

} // namespace nm

#endif // NM_MODULETYPE_HPP
