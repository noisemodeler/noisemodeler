#ifndef NM_TYPEMANAGER_HPP
#define NM_TYPEMANAGER_HPP

#include <nmlib/model/moduletype.hpp>

#include <map>
#include <memory>

namespace nm {

class TypeManager
{
public:
    TypeManager();
    bool addType(std::unique_ptr<ModuleType> type);
    ModuleType *getType(std::string name);
    void initBuiltinTypes();
private:
    std::map<std::string, std::unique_ptr<ModuleType>> m_userTypes;
};

} // namespace nm

#endif // NM_TYPEMANAGER_HPP
