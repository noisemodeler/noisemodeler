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
                      [&](const std::unique_ptr<ModuleInput> &input){return input->getName()==name;});
    return it != end(m_inputs) ? it->get() : nullptr;
}

const ModuleOutput *PrimitiveModuleType::getOutput(std::string name) const
{
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const std::unique_ptr<ModuleOutput> &output){return output->getName()==name;});
    return it != end(m_outputs) ? it->get() : nullptr;
}

std::vector<ModuleOutput *> PrimitiveModuleType::outputs()
{
    std::vector<ModuleOutput*> ret;
    for(auto &it:m_outputs){
        ret.push_back(it.get());
    }
    return ret;
}

std::vector<ModuleInput *> PrimitiveModuleType::inputs()
{
    std::vector<ModuleInput*> ret;
    for(auto &it:m_inputs){
        ret.push_back(it.get());
    }
    return ret;
}

} // namespace nm
