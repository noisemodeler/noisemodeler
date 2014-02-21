#ifndef NM_GRAPH_HPP
#define NM_GRAPH_HPP

#include <nmlib/model/module.hpp>

#include <nmlib/util.hpp>

namespace nm {

class Graph : UserDataProvider, NonCopyable //TODO make copyable
{
public:
    Graph():
        m_modules{}
    {}
    bool addModule(std::unique_ptr<Module> module);
    void clearModules();
    Module* getModule(const std::string &name);
    const Module* getModule(const std::string &name) const;

private:
    std::vector<std::unique_ptr<Module>> m_modules;

};

} // namespace nm

#endif // NM_GRAPH_HPP
