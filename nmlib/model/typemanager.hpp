#ifndef NM_TYPEMANAGER_HPP
#define NM_TYPEMANAGER_HPP

#include <nmlib/model/moduletype.hpp>

#include <map>
#include <memory>
#include <vector>

namespace nm {

/**
 * @ingroup model
 * @brief The top-level entity of a noise model. Encapsulates several
 * user types as well as built-in types.
 *
 * A type manager is the top-level entity in the model hierarchy.
 *
 * Two lists of ModuleType%s are maintained in a TypeManager, the user types,
 * and the built-in types.
 *
 * A user type may be constructed explicitly, or may be returned from a Parser
 * in the form of a unique_ptr.
 *
 * New user types can conveniently be added to the type manager, using the method
 * createUserType().
 * 
 * A TypeManager owns the ModuleType%s it manages.
 *
 */
class TypeManager : public UserDataProvider
{
public:
    /**
     * @brief Creates a new TypeManager
     *
     * Note that initBuiltinTypes method has to be called explicitly to
     * populate the list of buil-in types.
     */
    TypeManager();
    ~TypeManager();
    /**
     * @brief Add an existing user type to the TypeManager.
     * @return true if there was not a naming conflict and the type was added.
     *
     * To create a new user type, consider using createUserType instead.
     */
    bool addUserType(std::unique_ptr<ModuleType> moduleType);
    /** 
     * @brief try to create a new usertype with the given name
     * @return If a ModuleType was created, a pointer to it is returned.
     * Note that the ModuleType is still owned by the TypeManager.
     *
     * If the name is unavailable a different name may be chosen.
     */
    ModuleType* createUserType(std::string desiredName);
    /**
     * @brief Search for a module type with the given name
     * @return A pointer to a user type or built-in type, or nullptr
     * if it was not found.
     */
    const ModuleType *getType(std::string name) const;
    /** @brief Search for a built-in type with the given name */
    const ModuleType *getBuiltinType(std::string name) const;
    /** @brief Search for a user type with the given name */
    const ModuleType *getUserType(std::string name) const;
    /** @brief Search for a user type with the given name */
    ModuleType *getUserType(std::string name);
    /** @brief Populate the list of built-in module types */
    void initBuiltinTypes();

    //index accessors
    unsigned int numBuiltinTypes() const { return m_builtinTypes.size(); }
    const ModuleType *getBuiltinType(unsigned int index) const { return m_builtinTypes.at(index).get(); }
    unsigned int numUserTypes() const { return m_userTypes.size(); }
    const ModuleType *getUserType(unsigned int index) const { return m_userTypes.at(index).get(); }

    //signals
    /** @brief This signal is emitted before the TypeManager is destroyed */
    signal<void(TypeManager&)> destroying;
    /** @brief This signal is emitted when the list of user type changes */
    signal<void(TypeManager&)> userTypesChanged;

private:
    void addBuiltinType(std::unique_ptr<const ModuleType> moduleType);
    std::vector<std::unique_ptr<ModuleType>> m_userTypes;
    std::vector<std::unique_ptr<const ModuleType>> m_builtinTypes;
};

} // namespace nm

#endif // NM_TYPEMANAGER_HPP
