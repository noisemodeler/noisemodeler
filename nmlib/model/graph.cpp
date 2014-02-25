#include <nmlib/model/graph.hpp>
#include <nmlib/model/moduletype.hpp>

#include <sstream>

namespace nm {

Graph::~Graph()
{
    destroying(*this);
}

bool Graph::addModule(std::unique_ptr<Module> module)
{
    //TODO check for name conflicts
    m_modules.push_back(std::move(module));
    moduleAdded(*this, *m_modules.back(), m_modules.size()-1);
    return true;
}

Module *Graph::createModule(const ModuleType &type, std::string name)
{
    auto module = make_unique<Module>(type, name);
    auto modulePtr =  module.get();
    if(!addModule(std::move(module))){
        return nullptr;
    }
    return modulePtr;
}

Module *Graph::createModule(const ModuleType &type)
{
    std::string name = type.getName() + "_1";
    for(unsigned int i = 2; getModule(name) != nullptr; ++i){
        std::stringstream ss;
        ss << type.getName() << "_" << i;
        name = ss.str();
    }
    return createModule(type, name);
}

std::unique_ptr<Module> Graph::removeModule(Module &module)
{
    auto it = std::find_if(m_modules.begin(), m_modules.end(), [&](const std::unique_ptr<Module> &m){
        return m.get() == &module;
    });
    if(it==m_modules.end())return {};
    (*it)->disconnect(); //we don't want to leave dangling connections to this node
    auto modulePtr = std::move(*it);
    m_modules.erase(it);
    moduleRemoved(*this, *modulePtr, it - m_modules.begin());
    return std::move(modulePtr);
}

void Graph::clearModules()
{
    //TODO some nodes can't be removed!
    m_modules.clear();
}

Module *Graph::getModule(const std::string &name)
{
    return const_cast<Module*>(static_cast<const Graph&>(*this).getModule(name));
}

const Module *Graph::getModule(const std::string &name) const
{
    auto it = std::find_if(m_modules.begin(), m_modules.end(), [&](const std::unique_ptr<Module> &module){
        return name == module->getName();
    });
    return it != m_modules.end() ? it->get() : nullptr;
}

Module *Graph::getModule(unsigned int index)
{
    //TODO bounds checking
    return m_modules.at(index).get();
}

const Module *Graph::getModule(unsigned int index) const
{
    //TODO bounds checking
    return m_modules.at(index).get();
}

} // namespace nm
