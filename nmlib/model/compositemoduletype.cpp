#include <nmlib/model/compositemoduletype.hpp>

#include <nmlib/model/moduletype.hpp>
#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>

#include <algorithm>

namespace nm {

CompositeModuleType::CompositeModuleType(const std::string& name, const std::string& description):
    m_name(name),
    m_description(description),
    m_inputs(),
    m_outputs()
{
}

const ModuleInput *CompositeModuleType::getInput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const std::pair<ModuleInput, InputLink&> &entry){return entry.first.getName()==name;});
    if(it != end(m_inputs)){
        return &(it->first);
    } else {
        return nullptr;
    }
}

const ModuleOutput *CompositeModuleType::getOutput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const std::pair<ModuleOutput, OutputLink&> &entry){return entry.first.getName()==name;});
    if(it != end(m_outputs)){
        return &(it->first);
    } else {
        return nullptr;
    }
}

bool CompositeModuleType::exportInput(const InputLink &inputLink, std::string externalName)
{
    if(getInput(externalName) != nullptr){
        return false;
    }
    //TODO
    //create a moduleinput and add it to the vector (m_inputs)
    return true;
}

} // namespace nm
