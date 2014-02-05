#include <nmlib/model/inputmoduletype.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>

#include <algorithm>

#include <cassert>

namespace nm {

InputModuleType::InputModuleType(const ModuleType &parentType):
    c_parentType(parentType),
    m_inputs(),
    p_inputModule(nullptr)
{}

std::string InputModuleType::getName() const
{
    return {"input"};
}

std::string InputModuleType::getDescription() const
{
    return {"Inputs for ModuleType: "+c_parentType.getName()};
}

const ModuleInput *InputModuleType::getInput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const pair<ModuleInput, ModuleOutput> &entry){return entry.first.getName()==name;});
    if(it == end(m_inputs)){
        return nullptr;
    } else {
        return &(it->first);
    }
}

const ModuleOutput *InputModuleType::getOutput(std::string /*name*/) const
{
    return nullptr;

//    using namespace std;
//    auto it = find_if(begin(m_inputs), end(m_inputs),
//                      [&](const pair<ModuleInput, ModuleOutput> &entry){return entry.second.getName()==name;});
//    if(it == end(m_inputs)){
//        return nullptr;
//    } else {
//        return &(it->second);
    //    }
}

std::vector<const ModuleOutput *> InputModuleType::outputs() const
{
    std::vector<const ModuleOutput*> ret;
    ret.reserve(m_inputs.size());
    for(auto &p : m_inputs){
        ret.push_back(&(p.second));
    }
    return ret;
}

std::vector<const ModuleInput *> InputModuleType::inputs() const
{
    return std::vector<const ModuleInput*>();
}

void InputModuleType::onCreatedModule(Module &module)
{
    assert(p_inputModule==nullptr);
    p_inputModule = &module;
}

bool InputModuleType::addInput(std::string name, SignalType signalType)
{
    if(getInput(name) != nullptr){
        return false;
    }
    ModuleInput input(name, signalType, *this);
    ModuleOutput output(name, signalType, *this);
    //TODO this doesn't really move! why?
    m_inputs.emplace_back(std::move(input), std::move(output));
    if(p_inputModule!=nullptr){
        p_inputModule->onAddedModuleOutput(m_inputs.back().second);
    }
    return true;
}

} // namespace nm
