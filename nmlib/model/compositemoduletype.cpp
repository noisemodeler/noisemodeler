#include <nmlib/model/compositemoduletype.hpp>

#include <nmlib/model/moduletype.hpp>
#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/module.hpp>

#include <algorithm>

namespace nm {

CompositeModuleType::CompositeModuleType(const std::string& name, const std::string& description):
    c_name(name),
    c_description(description),
    m_inputModuleType(*this),
    m_outputs()
{
    //create inputmoduletype and inputmodule
    p_inputModule.reset(new Module(m_inputModuleType, "inputs"));
}

const ModuleInput *CompositeModuleType::getInput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const std::unique_ptr<ModuleInput> &entry){return entry->getName()==name;});
    if(it != end(m_inputs)){
        return it->get();
    } else {
        return nullptr;
    }
}

const ModuleOutput *CompositeModuleType::getOutput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const std::pair<std::unique_ptr<ModuleOutput>, const OutputLink&> &entry){return entry.first->getName()==name;});
    if(it != end(m_outputs)){
        return it->first.get();
    } else {
        return nullptr;
    }
}

std::vector<const ModuleOutput *> CompositeModuleType::outputs() const
{
    std::vector<const ModuleOutput*> ret{};
    ret.reserve(m_inputs.size());
    for(auto &i : m_outputs){
        ret.emplace_back(i.first.get());
    }
    return ret;
}

std::vector<const ModuleInput *> CompositeModuleType::inputs() const
{
    std::vector<const ModuleInput*> ret{};
    ret.reserve(m_inputs.size());
    for(auto &i : m_inputs){
        ret.emplace_back(i.get());
    }
    return ret;
}

bool CompositeModuleType::addInput(std::string name, SignalType signalType)
{
    if(getInput(name) != nullptr){
        return false;
    }
    m_inputs.emplace_back(new ModuleInput{name, signalType, *this});
    m_inputModuleType.addInput(name, signalType);
    return true;
}

bool CompositeModuleType::exportOutput(const OutputLink &outputLink, std::string externalName)
{
    if(getOutput(externalName) != nullptr){
        return false;
    }
    //TODO verify that OutputLink is actually a part of the composite
    m_outputs.emplace_back(
                std::unique_ptr<ModuleOutput>(new ModuleOutput(externalName, outputLink.getModuleOutput().getSignalType(), *this)),
                outputLink);
    return true;
}

bool CompositeModuleType::addModule(std::unique_ptr<Module> module)
{
    m_modules.push_back(std::move(module));
    return true;
}

Module *CompositeModuleType::getModule(const std::string &name)
{
    using namespace std;
    auto it = find_if(begin(m_modules), end(m_modules),
            [&](const std::unique_ptr<Module> &module){return module->getName() == name;});
    return it != end(m_modules) ? it->get() : nullptr;
}

} // namespace nm
