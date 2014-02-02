#include <nmlib/model/builtinmoduletype.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

#include <algorithm>

namespace nm {

BuiltinModuleType::BuiltinModuleType(std::string name, std::string description):
    c_name(name),
    c_description(description),
    m_inputs(),
    m_outputs()
{}

const ModuleInput *BuiltinModuleType::getInput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const std::unique_ptr<const ModuleInput> &input){return input->getName()==name;});
    return it != end(m_inputs) ? it->get() : nullptr;
}

const ModuleOutput *BuiltinModuleType::getOutput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const std::unique_ptr<const ModuleOutput> &output){return output->getName()==name;});
    return it != end(m_outputs) ? it->get() : nullptr;
}

std::vector<const ModuleOutput *> BuiltinModuleType::outputs() const
{
    std::vector<const ModuleOutput*> ret;
    for(auto &it:m_outputs){
        ret.push_back(it.get());
    }
    return ret;
}

std::vector<const ModuleInput *> BuiltinModuleType::inputs() const
{
    std::vector<const ModuleInput*> ret;
    for(auto &it:m_inputs){
        ret.push_back(it.get());
    }
    return ret;
}

bool BuiltinModuleType::addInput(std::string name, SignalType signalType)
{
    if(getInput(name) != nullptr)return false;
    m_inputs.emplace_back(new ModuleInput(name, signalType, *this));
    return true;
}

bool BuiltinModuleType::addOutput(std::string name, SignalType signalType)
{
    if(getOutput(name) != nullptr)return false;
    m_outputs.emplace_back(new ModuleOutput(name, signalType, *this));
    return false;
}

} // namespace nm
