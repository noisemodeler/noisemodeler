#include <nmlib/model/graph.hpp>

namespace nm {

bool Graph::addModule(std::unique_ptr<Module> /*module*/)
{
    //TODO check for name conflicts
    m_modules.push_back(std::move(module));
    return true;
}

void Graph::clearModules()
{
    m_modules.clear();
}

const Module *Graph::getModule(const std::string &name) const
{
    auto it = std::find_if(m_modules.begin(), m_modules.end(), [&](const std::unique_ptr<Module> &module){
        return name == module->getName();
    });
    return it != m_modules.end() ? it->get() : nullptr;
}

} // namespace nm
