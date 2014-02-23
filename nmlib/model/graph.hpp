#ifndef NM_GRAPH_HPP
#define NM_GRAPH_HPP

#include <nmlib/model/module.hpp>

#include <nmlib/util.hpp>
#include <nmlib/util/signals.hpp>

namespace nm {

class Graph : public UserDataProvider, NonCopyable //TODO make copyable
{
public:
    Graph():
        m_modules{}
    {}
    ~Graph();
    bool addModule(std::unique_ptr<Module> module);
    //TODO supply a version without name
    Module* createModule(const ModuleType& type, std::string name);
    void clearModules();
    Module* getModule(const std::string &name);
    const Module* getModule(const std::string &name) const;
    Module *getModule(unsigned int index);
    const Module *getModule(unsigned int index) const;
    unsigned int numModules() const { return m_modules.size(); }

    //signals
    signal<void(Graph&)> destroying;
    signal<void(Graph&, Module&)> moduleAdded;
    signal<void(Graph&, Module&)> moduleRemoved;

private:
    std::vector<std::unique_ptr<Module>> m_modules;

};

} // namespace nm

#endif // NM_GRAPH_HPP
