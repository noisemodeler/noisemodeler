#include <nmlib/model/typemanager.hpp>

#include <nmlib/model/builtinmoduletype.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>

#include <iostream>
#include <algorithm>

namespace nm {

TypeManager::TypeManager():
    m_userTypes(),
    m_primitiveBuiltinTypes()
{
}

TypeManager::~TypeManager()
{
    for(auto &compositeType : m_userTypes){
        compositeType.second->clearModules();
    }
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

const ModuleType *TypeManager::getType(std::string name) const
{
    auto it1 = m_primitiveBuiltinTypes.find(name);
    if(it1 != end(m_primitiveBuiltinTypes)){
        return it1->second.get();
    }
    auto it = m_userTypes.find(name);
    return it != end(m_userTypes) ? it->second.get() : nullptr;
}

CompositeModuleType *TypeManager::getUserType(std::string name)
{
    auto it = m_userTypes.find(name);
    return it != end(m_userTypes) ? it->second.get() : nullptr;
}

namespace {

std::unique_ptr<const BuiltinModuleType> createFBM(){
    std::unique_ptr<BuiltinModuleType> moduleType{new BuiltinModuleType{"fbm", "fractional brownian motion"}};
    moduleType->addInput("pos", SignalType{2});
    moduleType->addOutput("out", SignalType{1});
    return std::move(moduleType);
}

}

void TypeManager::initBuiltinTypes()
{
    addBuiltinType(createFBM());
    //TODO
}

void TypeManager::addBuiltinType(std::unique_ptr<const BuiltinModuleType> moduleType)
{
    m_primitiveBuiltinTypes[moduleType->getName()] = std::move(moduleType);
}

} // namespace nm
