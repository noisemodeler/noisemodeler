#include <nmlib/model/moduletype.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/graph.hpp> //unique_ptr needs this

namespace nm {

ModuleType::ModuleType(std::string name, std::string description):
    m_name(name),
    m_description(description),
    m_composite(false),
    m_removable(true),
    m_graphInput(false),
    m_graphOutput(false),
    m_inputs(),
    m_outputs(),
    m_graph()
{}

const ModuleInput *ModuleType::getInput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const std::unique_ptr<ModuleInput> &input){return input->getName()==name;});
    return it != end(m_inputs) ? it->get() : nullptr;
}

ModuleInput *ModuleType::getInput(std::string name)
{
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
    return m_outputs.back().get();
}

void ModuleType::setGraph(std::unique_ptr<Graph> graph) { m_graph = std::move(graph); }

} // namespace nm
