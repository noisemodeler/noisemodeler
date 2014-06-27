#ifndef NM_GRAPH_HPP
#define NM_GRAPH_HPP

#include <nmlib/util.hpp>
#include <nmlib/util/signals.hpp>

namespace nm {

class Module;
class ModuleType;

/**
 * @brief A graph of Module%s.
 * @ingroup model
 */
class Graph : public UserDataProvider, NonCopyable //TODO make copyable
{
public:
    Graph():
        m_modules{}
    {}
    ~Graph();
    bool addModule(std::unique_ptr<Module> module);
    Module* createModule(const ModuleType& type, std::string name);
    Module* createModule(const ModuleType& type);
    std::unique_ptr<Module> removeModule(Module& module);
    void clearModules();
    Module* getModule(const std::string &name);
    const Module* getModule(const std::string &name) const;
    Module *getModule(unsigned int index);
    const Module *getModule(unsigned int index) const;
    Module *findModule(std::function<bool(Module&)> predicative);
    const Module *findModule(std::function<bool(const Module&)> predicative) const;
    unsigned int numModules() const { return m_modules.size(); }
    void traverseModulesTopological(std::function<void(const Module&)> callback) const;

    //signals
    signal<void(Graph&)> destroying;
    signal<void(Graph&, Module&, unsigned int)> moduleAdded;
    signal<void(Graph&, Module&, unsigned int)> moduleRemoved;

private:
    std::vector<std::unique_ptr<Module>> m_modules;

};

} // namespace nm

#endif // NM_GRAPH_HPP
