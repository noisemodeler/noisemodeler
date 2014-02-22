#include <nmlib/model/moduletype.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/graph.hpp> //unique_ptr needs this

namespace nm {

ModuleType::ModuleType(std::string name, std::string description):
    ModuleType(name, ModuleType::Category::Composite, description)
{}

ModuleType::ModuleType(std::string name, ModuleType::Category category, std::string description):
    m_name(name),
    m_description(description),
    m_removable(category==Category::GraphInput || category == Category::GraphOutput),
    m_category(category),
    m_inputs(),
    m_outputs(),
    //composite only attribute intitialization
    m_graph(category==Category::Composite ? make_unique<Graph>() : std::unique_ptr<Graph>{}),
    m_inputModuleType(category==Category::Composite ? make_unique<ModuleType>("inputs", Category::GraphInput) : std::unique_ptr<ModuleType>{}),
    m_outputModuleType(category==Category::Composite ? make_unique<ModuleType>("outputs", Category::GraphInput) : std::unique_ptr<ModuleType>{})
{
    if(isComposite()){
        m_graph->addModule(make_unique<Module>(*m_inputModuleType, "inputs"));
        m_graph->addModule(make_unique<Module>(*m_outputModuleType, "outputs"));
    }
}

const ModuleInput *ModuleType::getInput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const std::unique_ptr<ModuleInput> &input){return input->getName()==name;});
    return it != end(m_inputs) ? it->get() : nullptr;
}

ModuleInput *ModuleType::getInput(std::string name)
{
    //reuse const implementation
    return const_cast<ModuleInput*>(static_cast<const ModuleType&>(*this).getInput(name));
}

void ModuleType::eachModuleInput(std::function<void (const ModuleInput &)> f) const
{
    for(auto &input : m_inputs){
        f(*input);
    }
}

void ModuleType::eachModuleInput(std::function<void (ModuleInput &)> f)
{
    for(auto &input : m_inputs){
        f(*input);
    }
}

ModuleInput *ModuleType::addInput(std::string name, SignalType signalType)
{
    if(getInput(name) != nullptr)return nullptr;
    m_inputs.emplace_back(new ModuleInput(name, signalType, *this));
    if(isComposite()){
        m_inputModuleType->addOutput(name, signalType);
        m_inputModuleType->addInput(name, signalType);
    }
    inputAdded(*m_inputs.back());
    return m_inputs.back().get();
}



const ModuleOutput *ModuleType::getOutput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const std::unique_ptr<ModuleOutput> &output){return output->getName()==name;});
    return it != end(m_outputs) ? it->get() : nullptr;
}

ModuleOutput *ModuleType::getOutput(std::string name)
{
    //reuse const implementation
    return const_cast<ModuleOutput*>(static_cast<const ModuleType&>(*this).getOutput(name));
}

void ModuleType::eachModuleOutput(std::function<void (const ModuleOutput &)> f) const
{
    for(auto &output : m_outputs){
        f(*output);
    }
}

void ModuleType::eachModuleOutput(std::function<void (ModuleOutput &)> f)
{
    for(auto &output : m_outputs){
        f(*output);
    }
}

ModuleOutput *ModuleType::addOutput(std::string name, SignalType signalType)
{
    if(getOutput(name) != nullptr)return nullptr;
    m_outputs.emplace_back(new ModuleOutput(name, signalType, *this));
    if(isComposite()){
        m_outputModuleType->addOutput(name, signalType);
        m_outputModuleType->addInput(name, signalType);
    }
    outputAdded(*m_outputs.back());
    return m_outputs.back().get();
}

ModuleOutput *ModuleType::exportInternalOutput(OutputLink &outputLink, std::string externalName)
{
    assert(isComposite());
    //TODO verify that the inpulink belongs to a module in the composites graph
    auto moduleOutput = addOutput(externalName, outputLink.getModuleOutput().getSignalType());
    if(moduleOutput == nullptr)return nullptr;
    //we assume calling addoutput updated the outputmoduletype, so we can now connect the output
    m_graph->getModule("outputs")->getInput(externalName)->link(outputLink);
    return moduleOutput;
}

} // namespace nm
