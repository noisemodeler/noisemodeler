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
    p_inputModule.reset(new Module(m_inputModuleType));
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
                      [&](const std::pair<std::unique_ptr<ModuleOutput>, OutputLink&> &entry){return entry.first->getName()==name;});
    if(it != end(m_outputs)){
        return it->first.get();
    } else {
        return nullptr;
    }
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
    return false;
}

} // namespace nm