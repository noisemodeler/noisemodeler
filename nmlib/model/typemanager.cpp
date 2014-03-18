#include <nmlib/model/typemanager.hpp>

#include <nmlib/model/primitivemoduletype.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>
#include <nmlib/model/graph.hpp>

#include <nmlib/util.hpp>

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
//1D versions

std::unique_ptr<const ModuleType> createAdd1(){
    auto moduleType = make_unique<ModuleType>("add1", ModuleType::Category::Primitive, "result = lhs + rhs");
    moduleType->addInput("lhs", SignalType{1});
    moduleType->addInput("rhs", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createSub1(){
    auto moduleType = make_unique<ModuleType>("sub1", ModuleType::Category::Primitive, "result = lhs - rhs");
    moduleType->addInput("lhs", SignalType{1});
    moduleType->addInput("rhs", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createMul1(){
    auto moduleType = make_unique<ModuleType>("mul1", ModuleType::Category::Primitive, "result = lhs * rhs");
    moduleType->addInput("lhs", SignalValue{1.f});
    moduleType->addInput("rhs", SignalValue{1.f});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createMod(){
    auto moduleType = make_unique<ModuleType>("mod", ModuleType::Category::Primitive, "modulo operator. result = dividend mod divisor");
    moduleType->addInput("dividend", SignalType{1});
    moduleType->addInput("divisor", SignalValue{1.f});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createAbs(){
    auto moduleType = make_unique<ModuleType>("abs", ModuleType::Category::Primitive, "absolute value");
    moduleType->addInput("source", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

//2D modules

std::unique_ptr<const ModuleType> createAdd2(){
    auto moduleType = make_unique<ModuleType>("add2", ModuleType::Category::Primitive, "result = lhs + rhs");
    moduleType->addInput("lhs", SignalType{2});
    moduleType->addInput("rhs", SignalType{2});
    moduleType->addOutput("result", SignalType{2});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createSub2(){
    auto moduleType = make_unique<ModuleType>("sub2", ModuleType::Category::Primitive, "result = lhs - rhs");
    moduleType->addInput("lhs", SignalType{2});
    moduleType->addInput("rhs", SignalType{2});
    moduleType->addOutput("result", SignalType{2});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createMul2(){
    auto moduleType = make_unique<ModuleType>("mul2", ModuleType::Category::Primitive, "result = lhs * rhs");
    moduleType->addInput("lhs", SignalType{2});
    moduleType->addInput("rhs", SignalType{2});
    moduleType->addOutput("result", SignalType{2});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDemux2(){
    auto moduleType = make_unique<ModuleType>("demux2", ModuleType::Category::Primitive, "demultiplexes a 2D vector to two 1D vectors");
    moduleType->addInput("m", SignalType{2});
    moduleType->addOutput("x", SignalType{1});
    moduleType->addOutput("y", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createMux2(){
    auto moduleType = make_unique<ModuleType>("mux2", ModuleType::Category::Primitive, "multiplexes two 1D vectors into a 2D vector");
    moduleType->addInput("x", SignalType{1});
    moduleType->addInput("y", SignalType{1});
    moduleType->addOutput("m", SignalType{2});
    return std::move(moduleType);
}


std::unique_ptr<const ModuleType> createNoise2(){
    auto moduleType = make_unique<ModuleType>("noise2", ModuleType::Category::Primitive, "2D noise (implementation defined)");
    moduleType->addInput("pos", SignalType{2});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createFbm2D(){
    auto moduleType = make_unique<ModuleType>("fbm2", ModuleType::Category::Primitive, "fractional brownian motion");
    moduleType->addInput("pos", SignalType{2});
    moduleType->addInput("octaves", SignalValue{10});
    moduleType->addInput("lacunarity", SignalValue{2.f});
    moduleType->addInput("gain", SignalValue{0.5f});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

//3D modules

std::unique_ptr<const ModuleType> createDemux3(){
    auto moduleType = make_unique<ModuleType>("demux3", ModuleType::Category::Primitive, "demultiplexes a 3D vector to three 1D vectors");
    moduleType->addInput("m", SignalType{3});
    moduleType->addOutput("x", SignalType{1});
    moduleType->addOutput("y", SignalType{1});
    moduleType->addOutput("z", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createMux3(){
    auto moduleType = make_unique<ModuleType>("mux3", ModuleType::Category::Primitive, "multiplexes three 1D vectors into a 3D vector");
    moduleType->addInput("x", SignalType{1});
    moduleType->addInput("y", SignalType{1});
    moduleType->addInput("z", SignalType{1});
    moduleType->addOutput("m", SignalType{3});
    return std::move(moduleType);
}


//Debug modules

std::unique_ptr<const ModuleType> createDebugInput(){
    auto moduleType = make_unique<ModuleType>("debug_input", ModuleType::Category::Primitive, "preview pixel coordinates");
    moduleType->addOutput("pos", SignalType{2});
    moduleType->addInput("pos", SignalType{2});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDebugOutput(){
    auto moduleType = make_unique<ModuleType>("debug_output", ModuleType::Category::Primitive, "height value for the preview");
    moduleType->addInput("height", SignalType{1});
    moduleType->addOutput("height", SignalType{1});
    return std::move(moduleType);
}

}

void TypeManager::initBuiltinTypes()
{
    //1D modules
    addBuiltinType(createAdd1());
    addBuiltinType(createSub1());
    addBuiltinType(createMul1());
    addBuiltinType(createMod());
    addBuiltinType(createAbs());

    //2D modules
    addBuiltinType(createAdd2());
    addBuiltinType(createSub2());
    addBuiltinType(createMul2());
    addBuiltinType(createDemux2());
    addBuiltinType(createMux2());
    addBuiltinType(createNoise2());
    addBuiltinType(createFbm2D());

    //3D modules
    addBuiltinType(createDemux3());
    addBuiltinType(createMux3());

    //debug modules
    addBuiltinType(createDebugInput());
    addBuiltinType(createDebugOutput());
}

void TypeManager::addBuiltinType(std::unique_ptr<const ModuleType> moduleType)
{
    m_builtinTypes.push_back(std::move(moduleType));
}

} // namespace nm
