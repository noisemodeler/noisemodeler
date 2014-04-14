#include "typemanagerq.hpp"

#include "moduletypeq.hpp"

#include <nmlib/model/typemanager.hpp>

namespace nmgui {

TypeManagerQ::TypeManagerQ(nm::TypeManager* typeManager, QObject *parent) :
    QObject(parent),
    m_typeManager(typeManager)
{
    Q_ASSERT(m_typeManager!=nullptr);
    Q_ASSERT(m_typeManager->getUserData()==nullptr);
    m_typeManager->setUserData(this);

    typeManagerDestroyedConnection = m_typeManager->destroying.connect([&](nm::TypeManager &){
        deleteLater();
        m_typeManager->setUserData(nullptr);
        m_typeManager = nullptr;
    });
    userTypesChangedConnection = m_typeManager->userTypesChanged.connect([&](nm::TypeManager &){
        userTypesChanged();
    });
}

TypeManagerQ *TypeManagerQ::fromTypeManager(nm::TypeManager &typeManager)
{
    //TODO switch to some Qt smart pointer instead of rawpointer?
    auto userData = static_cast<TypeManagerQ*>(typeManager.getUserData());
    return userData != nullptr ? userData : new TypeManagerQ(&typeManager);
}

QQmlListProperty<ModuleTypeQ> TypeManagerQ::builtinTypes()
{
    return QQmlListProperty<ModuleTypeQ>(this, 0, nullptr, &TypeManagerQ::builtinModulesCount, &TypeManagerQ::builtinModuleAt, nullptr);
}

QQmlListProperty<ModuleTypeQ> TypeManagerQ::userTypes()
{
    return QQmlListProperty<ModuleTypeQ>(this, 0, nullptr, &TypeManagerQ::userModulesCount, &TypeManagerQ::userModuleAt, nullptr);
}

ModuleTypeQ *TypeManagerQ::builtinModuleAt(QQmlListProperty<ModuleTypeQ> *list, int index)
{
    TypeManagerQ *typeManager = qobject_cast<TypeManagerQ *>(list->object);
    if(typeManager){
        return ModuleTypeQ::fromModuleType(*typeManager->m_typeManager->getBuiltinType(index));
    } else {
        return nullptr;
    }
}

int TypeManagerQ::builtinModulesCount(QQmlListProperty<ModuleTypeQ> *list)
{
    TypeManagerQ *typeManager = qobject_cast<TypeManagerQ *>(list->object);
    if(typeManager){
        return typeManager->m_typeManager->numBuiltinTypes();
    } else {
        return 0;
    }
}

ModuleTypeQ *TypeManagerQ::userModuleAt(QQmlListProperty<ModuleTypeQ> *list, int index)
{
    TypeManagerQ *typeManager = qobject_cast<TypeManagerQ *>(list->object);
    if(typeManager){
        return ModuleTypeQ::fromModuleType(*typeManager->m_typeManager->getUserType(index));
    } else {
        return nullptr;
    }
}

int TypeManagerQ::userModulesCount(QQmlListProperty<ModuleTypeQ> *list)
{
    TypeManagerQ *typeManager = qobject_cast<TypeManagerQ *>(list->object);
    if(typeManager){
        return typeManager->m_typeManager->numUserTypes();
    } else {
        return 0;
    }
}

} // namespace nmgui
