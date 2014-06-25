#include <nmlib/model/module.hpp>

#include <nmlib/model/moduletype.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>

#include <nmlib/util.hpp>

#include <algorithm>

namespace nm {

Module::Module(const ModuleType &type, std::string name, std::string description):
    m_type(type),
    m_name(name),
    m_description(description),
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
    m_moduleInputRemovedCon = mutableType.removingInput.connect([&](ModuleInput &moduleInput){
        removeInput(moduleInput);
    });
    m_moduleOutputRemovedCon = mutableType.removingOutput.connect([&](ModuleOutput &moduleOutput){
        removeOutput(moduleOutput);
    });

    //TODO connect to removed events as well
}

Module::~Module()
{
    //unlink if still connected
    for(auto output : getOutputs()){
        output->unlinkAll();
    }
    for(auto input : getInputs()){
        input->unlink();
    }
    destroying(*this);
}

void Module::setName(std::string name){
    m_name=name;
    nameChanged(*this, m_name);
}

void Module::setDescription(std::string description)
{
    m_description=description;
    descriptionChanged(*this, m_description);
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

const InputLink *Module::getInput(unsigned int i) const
{
    if(m_inputs.size()<=i)return nullptr;
    return m_inputs[i].get();
}

unsigned int Module::getInputSize() const
{
    return m_inputs.size();
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

bool Module::removeInput(const ModuleInput &moduleInput)
{
    auto it = std::find_if(m_inputs.begin(), m_inputs.end(), [&](const std::unique_ptr<InputLink> &inputLink){
        return &inputLink->getModuleInput() == &moduleInput;
    });
    if(it==m_inputs.end())return false;
    m_inputs.erase(it);
    removedInputLink(*this, moduleInput);
    return true;
}

bool Module::removeOutput(const ModuleOutput &moduleOutput)
{
    auto it = std::find_if(m_outputs.begin(), m_outputs.end(), [&](const std::unique_ptr<OutputLink> &outputLink){
        return &outputLink->getModuleOutput() == &moduleOutput;
    });
    if(it==m_outputs.end())return false;
    m_outputs.erase(it);
    removedOutputLink(*this, moduleOutput);
    return true;
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

const OutputLink *Module::getOutput(unsigned int i) const
{
    if(m_outputs.size()<=i)return nullptr;
    return m_outputs[i].get();
}

unsigned int Module::getOutputSize() const
{
    return m_outputs.size();
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

void Module::disconnect()
{
    for(auto &inputLink : m_inputs){
        inputLink->unlink();
    }
    for(auto &outputLink : m_outputs){
        outputLink->unlinkAll();
    }
}

void Module::traverseDescendants(std::function<void (Module &)> callback)
{
    const_cast<const Module&>(*this).traverseDescendants([&](const Module& module){
        callback(const_cast<Module&>(module));
    });
}

void Module::traverseDescendants(std::function<void(const Module &)> callback) const
{
    //simple recursive dfs traversal, but keep track of visited ancestors and skip them
    std::set<const Module *> visited;
    std::function<void(const Module&)> helper = [&](const Module& module) {
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

void Module::traverseChildren(std::function<void(const Module &)> callback) const
{
    std::set<const Module *> visited{this};
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

void nm::Module::traverseParents(std::function<void(const Module &)> callback) const
{
    for(auto &inputLink : m_inputs){
        auto outputLink = inputLink->getOutputLink();
        if(outputLink!=nullptr){
            callback(outputLink->getOwner());
        }
    }
}

void nm::Module::traverseAncestors(std::function<void(const Module &)> callback) const
{
    //simple recursive dfs traversal, but keep track of visited ancestors and skip them
    std::set<const Module *> visited{this};
    std::function<void(const Module&)> helper = [&](const Module& module) {
        auto inserted = visited.insert(&module).second;
        if(inserted){
            module.traverseParents(helper);
            //postfix traversal
            callback(module);
        }
    };
    traverseParents(helper);
}

int Module::getDepth() const
{
    int maxParentDepth = -1;
    traverseParents([&](const Module &parentModule){
        int parentDepth = parentModule.getDepth();
        maxParentDepth = parentDepth>maxParentDepth ? parentDepth : maxParentDepth;
    });
    return maxParentDepth+1;
}

int Module::getHeight() const
{
    int maxChildHeight = -1;
    traverseChildren([&](const Module &childModule){
        int childHeight = childModule.getHeight();
        maxChildHeight = childHeight>maxChildHeight ? childHeight : maxChildHeight;
    });
    return maxChildHeight+1;
}

std::vector<Module *> Module::getDependenciesSorted(const std::vector<OutputLink *> &outputs, const std::set<InputLink *> &ignoreInputs)
{
    std::vector<Module *> modules;
    topologicallyTraverseDependencies(outputs, [&](Module& module){
        modules.push_back(&module);
    }, ignoreInputs);
    return modules;
}

std::vector<const Module *> Module::getDependenciesSorted(const std::vector<const OutputLink *> &outputs, const std::set<const InputLink *> &ignoreInputs)
{
    std::vector<const Module *> modules;
    topologicallyTraverseDependencies(outputs, [&](const Module& module){
        modules.push_back(&module);
    }, ignoreInputs);
    return modules;
}
//template?
void Module::topologicallyTraverseDependencies(const std::vector<OutputLink *> &outputs, std::function<void (Module &)> visitor, const std::set<InputLink*> &ignoreInputs)
{
    std::vector<Module *> remainingModules;
    for(auto output : outputs){
        //TODO: something about this looks wrong, what happens if there are several inputs?
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

void Module::topologicallyTraverseDependencies(const std::vector<const OutputLink *> &outputs, std::function<void (const Module &)> visitor, const std::set<const InputLink *> &ignoreInputs)
{
    //almost copy-pasted from mutable version because I don't know how to cast away constness from vectors
    //maybe it would be better to let the mutable version depend on this version

    std::vector<const Module *> remainingModules;
    for(auto output : outputs){
        //TODO: something about this looks wrong, what happens if there are several inputs?
        remainingModules.push_back(&output->getOwner());
    }
    std::set<const Module *> satisfiedModules;

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
