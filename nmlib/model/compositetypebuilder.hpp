#ifndef NM_COMPOSITETYPEBUILDER_HPP
#define NM_COMPOSITETYPEBUILDER_HPP

#include <nmlib/model/moduletype.hpp>

#include <nmlib/util.hpp>

namespace nm {

class CompositeTypeBuilder
{
public:
    template<typename T>
    CompositeTypeBuilder(T&& t):
        m_moduleType(std::forward<T>(t))
    {}
    ModuleType &getModuleType() { return *m_moduleType; }
    const ModuleType &getModuleType() const { return *m_moduleType; }
    std::unique_ptr<ModuleType> releaseModuleType() { return std::unique_ptr<ModuleType>{m_moduleType.release()}; }

    bool addInput(std::string name, SignalType signalType);
    bool exportOutput(const OutputLink &outputLink, std::string externalName);

    //implementation
private:
    std::unique_ptr<ModuleType> m_moduleType;
};

} // namespace nm

#endif // NM_COMPOSITETYPEBUILDER_HPP
