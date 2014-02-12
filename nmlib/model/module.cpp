#include <nmlib/model/module.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/moduletype.hpp>

#include <algorithm>

namespace nm {

Module::Module(const ModuleType &type, std::string name):
    c_type(type),
    m_name(name),
    m_inputs(),
    m_outputs()
{
    for(auto &moduleInput : c_type.inputs()){
        m_inputs.emplace_back(new InputLink(*this, *moduleInput));
    }
    for(auto &moduleOutput : c_type.outputs()){
        m_outputs.emplace_back(new OutputLink(*this, *moduleOutput));
    }
}

Module::~Module()
{
    //again total badasses to const_casts
    //might eventually solve this by making some methods private, and make moduletype and module friends
    destroying(*this);
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

void Module::setName(std::string name){
    m_name=name;
    nameChanged(*this, m_name);
}

InputLink *Module::getInput(std::string name)
{
    using namespace std;
    auto it = find_if(begin(m_inputs), end(m_inputs),
                      [&](const std::unique_ptr<InputLink> &inputLink){return inputLink->getModuleInput().getName() == name;}
    );
    return it != end(m_inputs) ? it->get() : nullptr;
}

InputLink *Module::getInput(unsigned int i)
{
    if(m_inputs.size()<=i)return nullptr;
    return m_inputs[i].get();
}

unsigned int Module::getInputSize() const
{
    return static_cast<unsigned int>(m_inputs.size());
}

OutputLink *Module::getOutput(std::string name)
{
    using namespace std;
    auto it = find_if(begin(m_outputs), end(m_outputs),
                      [&](const std::unique_ptr<OutputLink> &outputLink){return outputLink->getModuleOutput().getName() == name;}
    );
    return it != end(m_outputs) ? it->get() : nullptr;
}

OutputLink *Module::getOutput(unsigned int i)
{
    if(m_outputs.size()<=i)return nullptr;
    return m_outputs[i].get();
}

unsigned int Module::getOutputSize() const
{
    return static_cast<unsigned int>(m_outputs.size());
}

void Module::onAddedModuleInput(const ModuleInput &moduleInput)
{
    m_inputs.emplace_back(new InputLink(*this, moduleInput));
    addedInputLink(*this, *m_inputs.back());
}

void Module::onAddedModuleOutput(const ModuleOutput &moduleOutput)
{
    m_outputs.emplace_back(new OutputLink(*this, moduleOutput));
    addedOutputLink(*this, *m_outputs.back());
}

std::set<Module *> Module::getRequiredModules(const std::vector<OutputLink *> &outputs, const std::vector<InputLink *> &knownInputs)
{
    //TODO create test for this function
    std::set<InputLink *> knownInputsSet{knownInputs.begin(), knownInputs.end()};
    std::set<Module *> requiredModules;
    for(auto output : outputs){
        requiredModules.insert(&output->getOwner());
    }
    std::vector<Module *> horizon{requiredModules.begin(), requiredModules.end()};
    while(!horizon.empty()){
        Module* module = horizon.back();
        horizon.pop_back();
        for(auto &inputLink : module->m_inputs){
            auto outputLink = inputLink->getOutputLink();
            if(outputLink==nullptr){
                continue; //not connected, skip
            }
            if(knownInputsSet.find(inputLink.get())!=end(knownInputsSet)){
                continue; //skip known inputs
            }
            Module &other_module = outputLink->getOwner();
            //if it's a module we haven't seen before
            if(requiredModules.find(&other_module) == end(requiredModules)){
                //add it to the horizon
                horizon.push_back(&other_module);
            }
        }
        //when we have checked all inputs of a module, it is added to the required set
        requiredModules.insert(module);
    }
    return requiredModules;
}

void Module::topologicallyTraverseDependencies(const std::vector<OutputLink *> &outputs, std::function<void (Module &)> visitor, const std::set<InputLink*> &ignoreInputs)
{
    std::vector<Module *> remainingModules;
    for(auto output : outputs){
        remainingModules.push_back(&output->getOwner());
    }
    std::set<Module *> satisfiedModules;

    //do a dfs-like traversal
    while(!remainingModules.empty()){
        auto current = remainingModules.back();
        bool satisfied = true;
        for(auto &inputLink : current->m_inputs){
            if(find(ignoreInputs.begin(), ignoreInputs.end(), inputLink.get())!=ignoreInputs.end())continue; //skip input
            auto outputLink = inputLink->getOutputLink();
            if(outputLink==nullptr)continue; //skip disconnected inputs
            Module& otherModule = outputLink->getOwner();
            if(satisfiedModules.find(&otherModule)==satisfiedModules.end()){
                //haven't seen this node before
                remainingModules.push_back(&otherModule);
                satisfied = false;
            }
        }
        if(satisfied){
            satisfiedModules.insert(current);
            visitor(*current);
            remainingModules.pop_back();
        }
    }
}

} // namespace nmlib
