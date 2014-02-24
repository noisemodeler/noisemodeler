#include <nmlib/model/typemanager.hpp>

#include <nmlib/model/primitivemoduletype.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>
#include <nmlib/model/graph.hpp>

#include <iostream>
#include <algorithm>

namespace nm {

TypeManager::TypeManager():
    m_userTypes(),
    m_builtinTypes()
{
}

TypeManager::~TypeManager()
{
    destroying(*this);
    //TODO empty all graphs
//    for(auto &graphs : m_userTypes){
//    }
}

bool TypeManager::addUserType(std::unique_ptr<ModuleType> moduleType)
{
    if(getType(moduleType->getName()) != nullptr){
        std::cerr << "Type already exists\n";
        return false;
    }
    m_userTypes.push_back(std::move(moduleType));
    return true;
}

const ModuleType *TypeManager::getType(std::string name) const
{
    //try to find builtin first
    auto builtin = getBuiltinType(name);
    if(builtin != nullptr)return builtin;

    //then search the user types
    return getUserType(name);
}

const ModuleType *TypeManager::getBuiltinType(std::string name) const
{
    auto it = std::find_if(m_builtinTypes.begin(), m_builtinTypes.end(), [&](const std::unique_ptr<const ModuleType> &moduleType){
        return moduleType->getName()==name;
    });
    return it != m_builtinTypes.end() ? it->get() : nullptr;
}

const ModuleType *TypeManager::getUserType(std::string name) const
{
    auto it = std::find_if(m_userTypes.begin(), m_userTypes.end(), [&](const std::unique_ptr<ModuleType> &moduleType){
        return moduleType->getName()==name;
    });
    return it != m_userTypes.end() ? it->get() : nullptr;
}

ModuleType *TypeManager::getUserType(std::string name)
{
    return const_cast<ModuleType*>(const_cast<const TypeManager&>(*this).getUserType(name));
}

namespace {

std::unique_ptr<const ModuleType> createFBM(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"fbm", ModuleType::Category::Primitive, "fractional brownian motion"}};
    moduleType->addInput("pos", SignalType{2});
    moduleType->addInput("gain", SignalType{1});
    moduleType->addInput("lacunarity", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createAdd(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"add", ModuleType::Category::Primitive, "result = lhs + rhs"}};
    moduleType->addInput("lhs", SignalType{1});
    moduleType->addInput("rhs", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDebugInput(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"debug_input", ModuleType::Category::Primitive, "preview pixel coordinates"}};
    moduleType->addOutput("pos", SignalType{2});
    moduleType->addInput("pos", SignalType{2});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDebugOutput(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"debug_output", ModuleType::Category::Primitive, "height value for the preview"}};
    moduleType->addInput("height", SignalType{1});
    moduleType->addOutput("height", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDemux2(){
    std::unique_ptr<ModuleType> moduleType{new ModuleType{"demux2", ModuleType::Category::Primitive, "demultiplexes a 2D vector to two 1D vectors"}};
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
    m_builtinTypes.push_back(std::move(moduleType));
}

} // namespace nm
