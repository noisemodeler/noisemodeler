#ifndef NM_TYPEMANAGER_HPP
#define NM_TYPEMANAGER_HPP

#include <nmlib/model/moduletype.hpp>
#include <nmlib/model/compositemoduletype.hpp>

#include <map>
#include <memory>
#include <vector>

namespace nm {

class TypeManager
{
public:
    TypeManager();
    bool addUserType(std::unique_ptr<CompositeModuleType> type);
    ModuleType *getType(std::string name) const;
    CompositeModuleType *getUserType(std::string name) const;
    void initBuiltinTypes();
private:
    std::map<std::string, std::unique_ptr<CompositeModuleType>> m_userTypes;
};

} // namespace nm

#endif // NM_TYPEMANAGER_HPP
