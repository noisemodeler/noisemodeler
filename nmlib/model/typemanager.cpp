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
    moduleType->addInput("gain", SignalType{1});
    moduleType->addInput("lacunarity", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const BuiltinModuleType> createAdd(){
    std::unique_ptr<BuiltinModuleType> moduleType{new BuiltinModuleType{"add", "result = lhs + rhs"}};
    moduleType->addInput("lhs", SignalType{1});
    moduleType->addInput("rhs", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const BuiltinModuleType> createDebugInput(){
    std::unique_ptr<BuiltinModuleType> moduleType{new BuiltinModuleType{"debug_input", "preview pixel coordinates"}};
    moduleType->addOutput("pos", SignalType{2});
    return std::move(moduleType);
}

std::unique_ptr<const BuiltinModuleType> createDebugOutput(){
    std::unique_ptr<BuiltinModuleType> moduleType{new BuiltinModuleType{"debug_output", "height value for the preview"}};
    moduleType->addInput("height", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const BuiltinModuleType> createDemux2(){
    std::unique_ptr<BuiltinModuleType> moduleType{new BuiltinModuleType{"demux2", "demultiplexes a 2D vector to two 1D vectors"}};
    moduleType->addInput("m", SignalType{2});
    moduleType->addOutput("d1", SignalType{1});
    moduleType->addOutput("d2", SignalType{1});
    return std::move(moduleType);
}

}

void TypeManager::initBuiltinTypes()
{
    addBuiltinType(createFBM());
    addBuiltinType(createAdd());
    addBuiltinType(createDebugInput());
    addBuiltinType(createDebugOutput());
    addBuiltinType(createDemux2());
    //TODO
}

void TypeManager::addBuiltinType(std::unique_ptr<const BuiltinModuleType> moduleType)
{
    m_primitiveBuiltinTypes[moduleType->getName()] = std::move(moduleType);
}

} // namespace nm
