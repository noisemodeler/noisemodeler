#include <nmlib/model/module.hpp>

#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/moduletype.hpp>

#include <nmlib/util.hpp>

#include <algorithm>

namespace nm {

Module::Module(const ModuleType &type, std::string name):
    m_type(type),
    m_name(name),
    m_inputs(),
    m_outputs()
{
    m_type.eachModuleInput([&](const ModuleInput& moduleInput){
        createInputLink(moduleInput);
    });
    m_type.eachModuleOutput([&](const ModuleOutput& moduleOutput){
        createOutputLink(moduleOutput);
    });

    //hook up to events from moduletype
    //we're gonna be total badasses and cast away the constness
    auto &mutableType = const_cast<ModuleType&>(type);
    m_moduleInputAddedCon = mutableType.inputAdded.connect([&](ModuleInput &moduleInput){
        createInputLink(moduleInput);
    });
    m_moduleOutputAddedCon = mutableType.outputAdded.connect([&](ModuleOutput &moduleOutput){
        createOutputLink(moduleOutput);
    });

    //TODO connect to removed events as well
}

Module::~Module()
{
    destroying(*this);
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

std::vector<InputLink *> Module::getInputs()
{
    std::vector<InputLink *> inputs;
    inputs.reserve(m_inputs.size());
    for(auto &input : m_inputs){
        inputs.push_back(input.get());
    }
    return inputs;
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

std::vector<OutputLink *> Module::getOutputs()
{
    std::vector<OutputLink *> outputs;
    outputs.reserve(m_outputs.size());
    for(auto &output : m_outputs){
        outputs.push_back(output.get());
    }
    return outputs;
}

void Module::traverseDescendants(std::function<void (Module &)> callback)
{
    //simple recursive dfs traversal, but keep track of visited ancestors and skip them
    std::set<Module *> visited;
    std::function<void(Module&)> helper = [&](Module& module) {
        auto inserted = visited.insert(&module).second;
        if(inserted){
            module.traverseChildren(helper);
            //postfix traversal
            callback(module);
        }
    };
//    traverseChildren(helper);
    helper(*this);
}

void Module::traverseChildren(std::function<void (Module &)> callback)
{
    std::set<Module *> visited{this};
    for(auto &outputLink : m_outputs){
        for(unsigned int i=0; i<outputLink->numLinks(); ++i){
            auto inputLink = outputLink->getLink(i);
            if(inputLink!=nullptr){
                auto &module = inputLink->getOwner();
                auto inserted = visited.insert(&module).second;
                if(inserted){
                    callback(module);
                }
            }
        }
    }
}

void nm::Module::traverseParents(std::function<void (nm::Module &)> callback)
{
    for(auto &inputLink : m_inputs){
        auto outputLink = inputLink->getOutputLink();
        callback(outputLink->getOwner());
    }
}

void nm::Module::traverseAncestors(std::function<void (nm::Module &)> callback)
{
    //simple recursive dfs traversal, but keep track of visited ancestors and skip them
    std::set<Module *> visited{this};
    std::function<void(Module&)> helper = [&](Module& module) {
        auto inserted = visited.insert(&module).second;
        if(inserted){
            module.traverseParents(helper);
            //postfix traversal
            callback(module);
        }
    };
    traverseParents(helper);
}

void Module::onAddedModuleInput(const ModuleInput &moduleInput)
{
    createInputLink(moduleInput);
}

void Module::onAddedModuleOutput(const ModuleOutput &moduleOutput)
{
    createOutputLink(moduleOutput);
}

std::vector<Module *> Module::getDependenciesSorted(const std::vector<OutputLink *> &outputs, const std::set<InputLink *> &ignoreInputs)
{
    std::vector<Module *> modules;
    topologicallyTraverseDependencies(outputs, [&](Module& module){
        modules.push_back(&module);
    }, ignoreInputs);
    return modules;
}
//template?
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
            bool inserted = satisfiedModules.insert(current).second;
            if(inserted){
                visitor(*current);
            }
            remainingModules.pop_back();
        }
    }
}

void Module::createInputLink(const nm::ModuleInput &moduleInput)
{
    m_inputs.emplace_back(new InputLink(*this, moduleInput));
    addedInputLink(*this, *m_inputs.back());
}

void Module::createOutputLink(const ModuleOutput &moduleOutput)
{
    m_outputs.emplace_back(new OutputLink(*this, moduleOutput));
    addedOutputLink(*this, *m_outputs.back());
}

} // namespace nmlib
