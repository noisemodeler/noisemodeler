#ifndef NM_TYPEMANAGER_HPP
#define NM_TYPEMANAGER_HPP

#include <nmlib/model/moduletype.hpp>
#include <nmlib/model/compositemoduletype.hpp>

#include <map>
#include <memory>
#include <vector>

namespace nm {

class PrimitiveModuleType;

class TypeManager : public UserDataProvider
{
public:
    TypeManager();
    ~TypeManager();
    bool addUserType(std::unique_ptr<CompositeModuleType> type);
    const ModuleType *getType(std::string name) const;
    CompositeModuleType *getUserType(std::string name);
    void initBuiltinTypes();
private:
    void addBuiltinType(std::unique_ptr<const PrimitiveModuleType> moduleType);
    std::map<std::string, std::unique_ptr<CompositeModuleType>> m_userTypes;
    std::map<std::string, std::unique_ptr<const PrimitiveModuleType>> m_primitiveBuiltinTypes;
//    std::map<std::string, std::unique_ptr<CompositeModuleType>> m_compositeBuiltinTypes;
    static const PrimitiveModuleType
    //1D only types
    mod,step,smoothStep,
    //1D modules
    add1,sub1,mul1,perlin1,fbm1,
    //2D modules
    add2,sub2,mul2,perlin2,fbm2,scale2;
};

} // namespace nm

#endif // NM_TYPEMANAGER_HPP
