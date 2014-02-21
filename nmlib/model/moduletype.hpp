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

/**
 * @brief describes a recipe for a module and its inputs and outputs.
 */
class ModuleType : NonCopyable, public UserDataProvider
{
public:
    explicit ModuleType(std::string name, std::string description = "");

    std::string getName() const { return m_name; }
    std::string getDescription() const { return m_description; }
    bool isBuiltin() const { return !isComposite(); } //subject to change (some builtins may become composites in the future
    bool isComposite() const { return m_composite; }
    bool isRemovable() const { return m_removable; }
    bool isGraphInput() const { return m_graphInput; }
    bool isGraphOutput() const { return m_graphOutput; }

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
    void setGraph(std::unique_ptr<Graph> graph);

    //TODO enum params

    //signals
    signal<void(ModuleInput&)> inputAdded;
    signal<void(ModuleInput&)> inputRemoved;
    signal<void(ModuleOutput&)> outputAdded;
    signal<void(ModuleOutput&)> outputRemoved;
    //TODO more signals


    //implementation
private:
    std::string m_name, m_description;
    bool m_composite, m_removable; //TODO could be put in a bit field to save space
    bool m_graphInput, m_graphOutput; // these are special types of nodes that there can only be one of in each graph
                                      // they also can't be copied

    std::vector<std::unique_ptr<ModuleInput>> m_inputs;
    std::vector<std::unique_ptr<ModuleOutput>> m_outputs;

    std::unique_ptr<Graph> m_graph; //if this is a composite module, it will have a graph of internal nodes, this is it.
};

} // namespace nm

#endif // NM_MODULETYPE_HPP
