#include <nmlib/model/primitivemoduletype.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

#include <algorithm>

namespace nm {

PrimitiveModuleType::PrimitiveModuleType(std::string name, std::string description):
    c_name(name),
    c_description(description),
    m_inputs(),
    m_outputs()
{}

const ModuleInput *PrimitiveModuleType::getInput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const std::unique_ptr<const ModuleInput> &input){return input->getName()==name;});
    return it != end(m_inputs) ? it->get() : nullptr;
}

const ModuleOutput *PrimitiveModuleType::getOutput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const std::unique_ptr<const ModuleOutput> &output){return output->getName()==name;});
    return it != end(m_outputs) ? it->get() : nullptr;
}

std::vector<const ModuleOutput *> PrimitiveModuleType::outputs() const
{
    std::vector<const ModuleOutput*> ret;
    for(auto &it:m_outputs){
        ret.push_back(it.get());
    }
    return ret;
}

std::vector<const ModuleInput *> PrimitiveModuleType::inputs() const
{
    std::vector<const ModuleInput*> ret;
    for(auto &it:m_inputs){
        ret.push_back(it.get());
    }
    return ret;
}

bool PrimitiveModuleType::addInput(std::string name, SignalType signalType)
{
    if(getInput(name) != nullptr)return false;
    m_inputs.emplace_back(new ModuleInput(name, signalType, *this));
    return true;
}

bool PrimitiveModuleType::addOutput(std::string name, SignalType signalType)
{
    if(getOutput(name) != nullptr)return false;
    m_outputs.emplace_back(new ModuleOutput(name, signalType, *this));
    return false;
}

} // namespace nm
