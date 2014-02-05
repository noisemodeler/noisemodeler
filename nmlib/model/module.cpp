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

Module::~Module()
{
    //again total badasses to const_casts
    //might eventually solve this by making some methods private, and make moduletype and module friends
    auto &mutableType = const_cast<ModuleType &>(c_type);
    mutableType.onDestroyingModule(this);
}

std::unique_ptr<Module> Module::create(const ModuleType &type, std::string name)
{
    //We're gonna be total badasses and cast away the constness of the type
    auto &mutableType = const_cast<ModuleType &>(type);
    std::unique_ptr<Module> module{new Module{type, name}};
    mutableType.onCreatedModule(*module);
    return std::move(module);
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

void Module::onAddedModuleInput(const ModuleInput &moduleInput)
{
    m_inputs.push_back(InputLink(*this, moduleInput));
}

void Module::onAddedModuleOutput(const ModuleOutput &moduleOutput)
{
    m_outputs.push_back(OutputLink(*this, moduleOutput));
}
} // namespace nmlib
