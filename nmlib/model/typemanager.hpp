#ifndef NM_TYPEMANAGER_HPP
#define NM_TYPEMANAGER_HPP

#include <nmlib/model/moduletype.hpp>
#include <nmlib/model/compositemoduletype.hpp>

#include <map>
#include <memory>
#include <vector>

namespace nm {

class BuiltinModuleType;

class TypeManager
{
public:
    TypeManager();
    bool addUserType(std::unique_ptr<CompositeModuleType> type);
    const ModuleType *getType(std::string name) const;
    CompositeModuleType *getUserType(std::string name);
    void initBuiltinTypes();
private:
    void addBuiltinType(std::unique_ptr<const BuiltinModuleType> moduleType);
    std::map<std::string, std::unique_ptr<CompositeModuleType>> m_userTypes;
    std::map<std::string, std::unique_ptr<const BuiltinModuleType>> m_primitiveBuiltinTypes;
//    std::map<std::string, std::unique_ptr<CompositeModuleType>> m_compositeBuiltinTypes;
};

} // namespace nm

#endif // NM_TYPEMANAGER_HPP
