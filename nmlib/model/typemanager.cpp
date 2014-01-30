#include <nmlib/model/typemanager.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>

#include <iostream>
#include <algorithm>

namespace nm {

TypeManager::TypeManager()
{
}

bool TypeManager::addUserType(std::unique_ptr<CompositeModuleType> type)
{
    if(getType(type->getName()) != nullptr){
        std::cerr << "Type already exists\n";
        return false;
    }
    m_userTypes[type->getName()]=std::move(type);
    return true;
}

ModuleType *TypeManager::getType(std::string name) const
{
    auto it = m_userTypes.find(name);
    return it != end(m_userTypes) ? it->second.get() : nullptr;
}

CompositeModuleType *TypeManager::getUserType(std::string name) const
{
    auto it = m_userTypes.find(name);
    return it != end(m_userTypes) ? it->second.get() : nullptr;
}

void TypeManager::initBuiltinTypes()
{
    //TODO
}

} // namespace nm
