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

} // namespace nmgui
