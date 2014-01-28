#include <nmlib/model/moduletype.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

#include <algorithm>

namespace nm {

nm::ModuleType::ModuleType(const std::string &name, const std::string &description):
    m_name(name),
    m_description(description),
    m_inputs(),
    m_outputs()
{}

const ModuleInput *ModuleType::getInput(std::string name) const
{
     using namespace std;
     auto it = find_if(begin(m_inputs), end(m_inputs),
                       [&](const ModuleInput& input){return input.m_name==name;});
     if(it != end(m_inputs)){
         return &(*it);
     } else {
         return nullptr;
     }
}

const ModuleOutput *ModuleType::getOutput(std::string name) const
{

}

} // namespace nm
