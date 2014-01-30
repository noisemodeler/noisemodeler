#include <nmlib/model/module.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

#include <algorithm>

namespace nm {

Module::Module(const ModuleType &type, std::string name):
    c_type(type),
    c_name(name)
{
    //loop through moduleinputs and add inputlinks
    //and outputs
}

InputLink *Module::getInput(std::string name)
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const InputLink &inputLink){return inputLink.getModuleInput().getName() == name;}
    );
    return it != end(m_inputs) ? &(*it) : nullptr;
}

OutputLink *Module::getOutput(std::string name)
{

}

} // namespace nmlib
