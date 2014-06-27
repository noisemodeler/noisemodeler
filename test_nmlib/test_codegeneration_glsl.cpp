#include <nmlib/codegeneration/glsl/glslgenerator.hpp>
#include <nmlib/serialization/parser.hpp>

#include "readfile.hpp"

#include <gtest/gtest.h>

namespace {

TEST(GLSLCodeGenerationTest, compileWithoutErrors){
    //create a simple fbm terrain
    nm::TypeManager typeManager;
    typeManager.initBuiltinTypes();
    nm::ModuleType* terrainType = typeManager.createUserType("terrain");
    terrainType->addInput("pos", nm::SignalType{2});
    terrainType->addOutput("height", nm::SignalType{1});
    const nm::ModuleType *fbmType = typeManager.getType("fbm2");
    ASSERT_NE(nullptr, fbmType);
    nm::Module* fbmModule = terrainType->getGraph()->createModule(*fbmType);
    fbmModule->getInput("pos")->link(*terrainType->getInputModule()->getOutput("pos"));
    fbmModule->getOutput("result")->addLink(*terrainType->getOutputModule()->getInput("height"));

    //TODO, create a simpler function
    std::string glslSource = nm::glsl::GlslGenerator::compileToGlslFunction(
                *terrainType->getInputModule()->getInput("pos"),
                *terrainType->getOutputModule()->getOutput("height"),
                "terrainFunction");

    EXPECT_NE("", glslSource);
    //TODO more tests for generated source code
}

TEST(GLSLCodeGenerationTest, compileNestedWithoutErrors){
    //load terrain with multiple user types
    auto input = readFile("./data/multipletypes.nm.json");
    if(!input){
        FAIL() << "Couldn't read file";
    }
    nm::Parser parser;
    auto maybeTypeManager = parser.parseDocument(*input);
    if(!maybeTypeManager){
        FAIL() << "Parser didn't return a type manager";
    }

    nm::TypeManager &typeManager = *(*maybeTypeManager);
    nm::ModuleType* terrainType = typeManager.getUserType("terrain");

    //TODO, create a simpler function
    std::string glslSource = nm::glsl::GlslGenerator::compileToGlslFunction(
                *terrainType->getInputModule()->getInput("pos"),
                *terrainType->getOutputModule()->getOutput("height"),
                "terrainFunction");

    EXPECT_NE("", glslSource);
//    std::cout << glslSource;
    //TODO more tests for generated source code
}

}
