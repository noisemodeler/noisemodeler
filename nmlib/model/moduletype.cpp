#include <nmlib/model/moduletype.hpp>

#include <nmlib/model/module.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/graph.hpp> //unique_ptr needs this

namespace nm {

ModuleType::ModuleType(std::string name, std::string description):
    ModuleType(name, ModuleType::Category::Composite, description)
{}

ModuleType::ModuleType(std::string name, ModuleType::Category category, std::string description):
    m_name(name),
    m_description(description),
    m_removable(category!=Category::GraphInput && category != Category::GraphOutput),
    m_category(category),
    m_inputs(),
    m_outputs(),
    //composite only attribute intitialization
    m_graph(category==Category::Composite ? make_unique<Graph>() : std::unique_ptr<Graph>{}),
    m_inputModuleType(category==Category::Composite ? make_unique<ModuleType>("inputs", Category::GraphInput) : std::unique_ptr<ModuleType>{}),
    m_outputModuleType(category==Category::Composite ? make_unique<ModuleType>("outputs", Category::GraphOutput) : std::unique_ptr<ModuleType>{})
{
    if(isComposite()){
        m_graph->addModule(make_unique<Module>(*m_inputModuleType, "inputs"));
        m_graph->addModule(make_unique<Module>(*m_outputModuleType, "outputs"));
    }
}

ModuleType::~ModuleType(){destroying(*this);}

void ModuleType::setName(std::string name)
{
    if(name==m_name)return;
    m_name = std::move(name);
    nameChanged(*this, m_name);
}

void ModuleType::setDescription(std::string description)
{
    if(description==m_description)return;
    m_description = std::move(description);
    descriptionChanged(*this, m_description);
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
    return addInput(name, SignalValue(signalType));
}

ModuleInput *ModuleType::addInput(std::string name, SignalValue defaultValue)
{
    if(getInput(name) != nullptr)return nullptr;
    m_inputs.emplace_back(new ModuleInput(name, defaultValue, *this));
    if(isComposite()){
        m_inputModuleType->addOutput(name, defaultValue.getSignalType());
        m_inputModuleType->addInput(name, defaultValue);
    }
    inputAdded(*m_inputs.back());
    return m_inputs.back().get();
}

bool ModuleType::removeInput(ModuleInput *moduleInput)
{
    auto it = std::find_if(m_inputs.begin(), m_inputs.end(), [&](const std::unique_ptr<ModuleInput>& input){
        return input.get() == moduleInput;
    });
    if(it==m_inputs.end())return false;
    removingInput(**it);
    if(isComposite()){
        m_inputModuleType->removeOutput(m_inputModuleType->getOutput(moduleInput->getName()));
        m_inputModuleType->removeInput(m_inputModuleType->getInput(moduleInput->getName()));
    }
    m_inputs.erase(it);
    inputRemoved(*this);
    return true;
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

bool ModuleType::removeOutput(ModuleOutput *moduleOutput)
{
    auto it = std::find_if(m_outputs.begin(), m_outputs.end(), [&](const std::unique_ptr<ModuleOutput>& output){
        return output.get() == moduleOutput;
    });
    if(it==m_outputs.end())return false;
    removingOutput(**it);
    if(isComposite()){
        m_outputModuleType->removeOutput(m_outputModuleType->getOutput(moduleOutput->getName()));
        m_outputModuleType->removeInput(m_outputModuleType->getInput(moduleOutput->getName()));
    }
    m_outputs.erase(it);
    outputRemoved(*this);
    return true;
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
