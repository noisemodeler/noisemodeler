#ifndef NM_TYPEMANAGER_HPP
#define NM_TYPEMANAGER_HPP

#include <nmlib/model/moduletype.hpp>

#include <map>
#include <memory>
#include <vector>

namespace nm {

class PrimitiveModuleType;
class CompositeTypeBuilder;

/**
 * @brief The top-level entity of a noise model. Encapsulates several user types as well as built-in types.
 * @ingroup model
 */
class TypeManager : public UserDataProvider
{
public:
    TypeManager();
    ~TypeManager();
    bool addUserType(std::unique_ptr<ModuleType> moduleType);
    ModuleType* createUserType(std::string desiredName);
    const ModuleType *getType(std::string name) const;
    const ModuleType *getBuiltinType(std::string name) const;
    const ModuleType *getUserType(std::string name) const;
    ModuleType *getUserType(std::string name); //this is used to be able to edit usertypes
    void initBuiltinTypes();

    //index accessors
    unsigned int numBuiltinTypes() const { return m_builtinTypes.size(); }
    const ModuleType *getBuiltinType(unsigned int index) const { return m_builtinTypes.at(index).get(); }
    unsigned int numUserTypes() const { return m_userTypes.size(); }
    const ModuleType *getUserType(unsigned int index) const { return m_userTypes.at(index).get(); }

    //signals
    signal<void(TypeManager&)> destroying;
    signal<void(TypeManager&)> userTypesChanged;

private:
    void addBuiltinType(std::unique_ptr<const ModuleType> moduleType);
    std::vector<std::unique_ptr<ModuleType>> m_userTypes;
    std::vector<std::unique_ptr<const ModuleType>> m_builtinTypes;
};

} // namespace nm

#endif // NM_TYPEMANAGER_HPP
