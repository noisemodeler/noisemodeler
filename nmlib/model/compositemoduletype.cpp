#include "compositemoduletype.hpp"

#include <nmlib/model/moduletype.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

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
                      [&](const ModuleInput& input){return input.getName()==name;});
    if(it != end(m_inputs)){
        return &(*it);
    } else {
        return nullptr;
    }
}

const ModuleOutput *CompositeModuleType::getOutput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const ModuleOutput& output){return output.getName()==name;});
    if(it != end(m_outputs)){
        return &(*it);
    } else {
        return nullptr;
    }
}

bool CompositeModuleType::addInput(const ModuleInput &input)
{
    if(getInput(input.getName()) != nullptr){
        return false;
    }
    m_inputs.push_back(input);
    return true;
}

} // namespace nm
