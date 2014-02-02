#include <nmlib/model/module.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/moduletype.hpp>

#include <algorithm>

namespace nm {

Module::Module(const ModuleType &type, std::string name):
    c_type(type),
    c_name(name),
    m_inputs(),
    m_outputs()
{
    for(auto &moduleInput : c_type.inputs()){
        m_inputs.push_back(InputLink(*this, *moduleInput));
    }
    for(auto &moduleOutput : c_type.outputs()){
        m_outputs.push_back(OutputLink(*this, *moduleOutput));
    }
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
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const OutputLink &outputLink){return outputLink.getModuleOutput().getName() == name;}
    );
    return it != end(m_outputs) ? &(*it) : nullptr;
}

} // namespace nmlib
