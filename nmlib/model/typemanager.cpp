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
    userTypesChanged(*this);
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

std::unique_ptr<const ModuleType> createConstant1(){
    auto moduleType = make_unique<ModuleType>("constant1", ModuleType::Category::Primitive, "a constant value");
    moduleType->addInput("value", SignalType{1});
    moduleType->addOutput("value", SignalType{1});
    return std::move(moduleType);
}

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

std::unique_ptr<const ModuleType> createMin(){
    auto moduleType = make_unique<ModuleType>("min", ModuleType::Category::Primitive, "minimum of two values");
    moduleType->addInput("a", SignalType{1});
    moduleType->addInput("b", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createMax(){
    auto moduleType = make_unique<ModuleType>("max", ModuleType::Category::Primitive, "maximum of two values");
    moduleType->addInput("a", SignalType{1});
    moduleType->addInput("b", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createClamp(){
    auto moduleType = make_unique<ModuleType>("clamp", ModuleType::Category::Primitive, "clamp a value between two extremes");
    moduleType->addInput("x", SignalType{1});
    moduleType->addInput("min", SignalValue{0.f});
    moduleType->addInput("max", SignalValue{1.f});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createStep(){
    auto moduleType = make_unique<ModuleType>("step", ModuleType::Category::Primitive, "result = 0 for x < edge, otherwise result = 1");
    moduleType->addInput("value", SignalType{1});
    moduleType->addInput("edge", SignalType{1});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createSmoothStep(){
    auto moduleType = make_unique<ModuleType>("smoothstep", ModuleType::Category::Primitive, "Hermite interpolation between 0 and 1 when value is between minedge and maxedge");
    moduleType->addInput("value", SignalType{1});
    moduleType->addInput("minedge", SignalValue{0.0f});
    moduleType->addInput("maxedge", SignalValue{1.0f});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

//2D modules

std::unique_ptr<const ModuleType> createConstant2(){
    auto moduleType = make_unique<ModuleType>("constant2", ModuleType::Category::Primitive, "a constant 2d vector value");
    moduleType->addInput("value", SignalType{2});
    moduleType->addOutput("value", SignalType{2});
    return std::move(moduleType);
}

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

std::unique_ptr<const ModuleType> createScale2(){
    auto moduleType = make_unique<ModuleType>("scale2", ModuleType::Category::Primitive, "multiplies a 2D vector by a scalar. result = scalar * v");
    moduleType->addInput("v", SignalType{2});
    moduleType->addInput("scalar", SignalValue{1.f});
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

std::unique_ptr<const ModuleType> createRidgedMultifractal(){
    auto moduleType = make_unique<ModuleType>("ridgedmultifractal", ModuleType::Category::Primitive, "Specialized version of fBm to create a ridge-like landscape");
    moduleType->addInput("pos", SignalType{2});
    moduleType->addInput("octaves", SignalValue{10});
    moduleType->addInput("lacunarity", SignalValue{2.f});
    moduleType->addInput("h", SignalValue{0.25f});
    moduleType->addInput("offset", SignalValue{1.0f});
    moduleType->addInput("gain", SignalValue{2.0f});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createHybridMultifractal(){
    auto moduleType = make_unique<ModuleType>("hybridmultifractal", ModuleType::Category::Primitive, "Specialized version of fBm to create a create a terrain with rough mountains and smooth valleys");
    moduleType->addInput("pos", SignalType{2});
    moduleType->addInput("octaves", SignalValue{10});
    moduleType->addInput("lacunarity", SignalValue{2.f});
    moduleType->addInput("h", SignalValue{0.25f});
    moduleType->addInput("offset", SignalValue{0.7f});
    moduleType->addOutput("result", SignalType{1});
    return std::move(moduleType);
}

//3D modules

std::unique_ptr<const ModuleType> createConstant3(){
    auto moduleType = make_unique<ModuleType>("constant3", ModuleType::Category::Primitive, "a constant 3d vector value");
    moduleType->addInput("value", SignalType{3});
    moduleType->addOutput("value", SignalType{3});
    return std::move(moduleType);
}

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

std::unique_ptr<const ModuleType> createScale3(){
    auto moduleType = make_unique<ModuleType>("scale3", ModuleType::Category::Primitive, "multiplies a 3D vector by a scalar. result = scalar * v");
    moduleType->addInput("v", SignalType{3});
    moduleType->addInput("scalar", SignalValue{1.f});
    moduleType->addOutput("result", SignalType{3});
    return std::move(moduleType);
}


// 4D modules

std::unique_ptr<const ModuleType> createConstant4(){
    auto moduleType = make_unique<ModuleType>("constant4", ModuleType::Category::Primitive, "a constant 4d vector value");
    moduleType->addInput("value", SignalType{4});
    moduleType->addOutput("value", SignalType{4});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createDemux4(){
    auto moduleType = make_unique<ModuleType>("demux4", ModuleType::Category::Primitive, "demultiplexes a 4D vector to four 1D vectors");
    moduleType->addInput("m", SignalType{3});
    moduleType->addOutput("x", SignalType{1});
    moduleType->addOutput("y", SignalType{1});
    moduleType->addOutput("z", SignalType{1});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createMux4(){
    auto moduleType = make_unique<ModuleType>("mux4", ModuleType::Category::Primitive, "multiplexes four 1D vectors into a 4D vector");
    moduleType->addInput("x", SignalType{1});
    moduleType->addInput("y", SignalType{1});
    moduleType->addInput("z", SignalType{1});
    moduleType->addInput("w", SignalType{1});
    moduleType->addOutput("m", SignalType{4});
    return std::move(moduleType);
}

std::unique_ptr<const ModuleType> createScale4(){
    auto moduleType = make_unique<ModuleType>("scale4", ModuleType::Category::Primitive, "multiplies a 4D vector by a scalar. result = scalar * v");
    moduleType->addInput("v", SignalType{4});
    moduleType->addInput("scalar", SignalValue{1.f});
    moduleType->addOutput("result", SignalType{4});
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
    addBuiltinType(createConstant1());
    addBuiltinType(createAdd1());
    addBuiltinType(createSub1());
    addBuiltinType(createMul1());
    addBuiltinType(createMod());
    addBuiltinType(createAbs());
    addBuiltinType(createMin());
    addBuiltinType(createMax());
    addBuiltinType(createClamp());
    addBuiltinType(createStep());
    addBuiltinType(createSmoothStep());

    //2D modules
    addBuiltinType(createConstant2());
    addBuiltinType(createAdd2());
    addBuiltinType(createSub2());
    addBuiltinType(createMul2());
    addBuiltinType(createScale2());
    addBuiltinType(createDemux2());
    addBuiltinType(createMux2());
    addBuiltinType(createNoise2());
    addBuiltinType(createFbm2D());
    addBuiltinType(createRidgedMultifractal());
    addBuiltinType(createHybridMultifractal());

    //3D modules
    addBuiltinType(createConstant3());
    addBuiltinType(createDemux3());
    addBuiltinType(createMux3());
    addBuiltinType(createScale3());

    //4D modules
    addBuiltinType(createConstant4());
    addBuiltinType(createDemux4());
    addBuiltinType(createMux4());
    addBuiltinType(createScale4());

    //debug modules
    addBuiltinType(createDebugInput());
    addBuiltinType(createDebugOutput());
}

void TypeManager::addBuiltinType(std::unique_ptr<const ModuleType> moduleType)
{
    m_builtinTypes.push_back(std::move(moduleType));
}

} // namespace nm
