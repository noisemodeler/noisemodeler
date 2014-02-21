#include <nmlib/model/typemanager.hpp>

#include <nmlib/model/primitivemoduletype.hpp>
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
    //TODO empty all graphs
//    for(auto &graphs : m_userTypes){
//    }
}

//TODO graphTypeController as well
bool TypeManager::addUserType(std::unique_ptr<ModuleType> type)
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

ModuleType *TypeManager::getUserType(std::string name)
{
    auto it = m_userTypes.find(name);
    return it != end(m_userTypes) ? it->second.get() : nullptr;
}

namespace {

std::unique_ptr<const ModuleType> createFBM(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"fbm", "fractional brownian motion"}};
    moduleType->addInput("pos", SignalType{2});
    moduleType->addInput("gain", SignalType{1});
    moduleType->addInput("lacunarity", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createAdd(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"add", "result = lhs + rhs"}};
    moduleType->addInput("lhs", SignalType{1});
    moduleType->addInput("rhs", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDebugInput(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"debug_input", "preview pixel coordinates"}};
    moduleType->addOutput("pos", SignalType{2});
    moduleType->addInput("pos", SignalType{2});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDebugOutput(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"debug_output", "height value for the preview"}};
    moduleType->addInput("height", SignalType{1});
    moduleType->addOutput("height", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDemux2(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"demux2", "demultiplexes a 2D vector to two 1D vectors"}};
    moduleType->addInput("m", SignalType{2});
    moduleType->addOutput("x", SignalType{1});
    moduleType->addOutput("y", SignalType{1});
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

void TypeManager::addBuiltinType(std::unique_ptr<const ModuleType> moduleType)
{
    m_primitiveBuiltinTypes[moduleType->getName()] = std::move(moduleType);
}

} // namespace nm
