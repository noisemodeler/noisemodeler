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

/**
 * @brief describes a recipe for a module and its inputs and outputs.
 */
class ModuleType : NonCopyable, public UserDataProvider
{
public:
    enum class Category { //couldn't call it moduletypetype, cause that would be silly
        Primitive,
        Composite,
        GraphInput,
        GraphOutput
    };
    explicit ModuleType(std::string name, std::string description);
    explicit ModuleType(std::string name, Category category = Category::Composite, std::string description = "");
    ~ModuleType();

    std::string getName() const { return m_name; }
    void setName(std::string name);
    std::string getDescription() const { return m_description; }
    void setDescription(std::string description);
    bool isBuiltin() const { return !isComposite(); } //subject to change (some builtins may become composites in the future
    bool isComposite() const { return m_category == Category::Composite; }
    bool isPrimitive() const { return m_category == Category::Primitive; } //consider if graphinput and graphoutput should be primitive as well?
    bool isRemovable() const { return m_removable; }
    bool isGraphInput() const { return m_category == Category::GraphInput; }
    bool isGraphOutput() const { return m_category == Category::GraphOutput; }
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
    ModuleInput *addInput(std::string name, SignalType signalType);
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
    bool removeOutput(ModuleOutput *moduleOutput);

    Graph* getGraph() { return m_graph.get(); }
    ModuleOutput *exportInternalOutput(OutputLink &outputLink, std::string externalName);

    //TODO enum and/or constant params

    //signals
    signal<void(ModuleType&, const std::string&)> nameChanged;
    signal<void(ModuleType&, const std::string&)> descriptionChanged;
    signal<void(ModuleInput&)> inputAdded; //fired after an input has been added
    signal<void(ModuleInput&)> removingInput; //fired before input is removed
    signal<void(ModuleType&)> inputRemoved; //fired after input is removed
    signal<void(ModuleOutput&)> outputAdded;
    signal<void(ModuleOutput&)> removingOutput;
    signal<void(ModuleType&)> outputRemoved;
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
