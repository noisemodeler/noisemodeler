#include <nmlib/model/typemanager.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

#include <iostream>

namespace nm {

TypeManager::TypeManager()
{
}

bool TypeManager::addType(std::unique_ptr<ModuleType> type)
{
    if(getType(type->getName()) != nullptr){
        std::cerr << "Type already exists\n";
        return false;
    }
    m_userTypes[type->getName()]=std::move(type);
    return true;
}

ModuleType *TypeManager::getType(std::string name)
{
    auto it = m_userTypes.find(name);
    if(it == end(m_userTypes)){
        return nullptr;
    } else {
        ModuleType* type = it->second.get();
        return type;
    }
}

} // namespace nm
