#include <nmlib/model/graph.hpp>

namespace nm {

Graph::~Graph()
{
    destroying(*this);
}

bool Graph::addModule(std::unique_ptr<Module> module)
{
    //TODO check for name conflicts
    m_modules.push_back(std::move(module));
    moduleAdded(*this, *module);
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

void Graph::clearModules()
{
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
