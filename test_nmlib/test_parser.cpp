#include "nmlib/parser.hpp"

#include <gtest/gtest.h>

#include <fstream>

namespace {

nm::optional<std::string> readFile(std::string path)
{
    std::ifstream t(path);
    if(!t || !t.good()){
        return {};
    }
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

} // namespace

TEST(ParserTest, Constructor) {
    nm::Parser* parser = new nm::Parser();
    delete parser;
    SUCCEED();
}


TEST(ParserTest, GracefulFailure){
    nm::Parser parser;
    auto modules = parser.parseDocument("Malformed");
    EXPECT_FALSE(modules);
}

TEST(ParserTest, BlankDocument){
    nm::Parser parser;
    auto modules = parser.parseDocument(R"( {"moduleTypes":[]} )");
    if(!modules){
        FAIL();
    }
    //TODO assert user modules == 0
}

TEST(ParserTest, OneModuleType){
    nm::Parser parser;
    auto input = readFile("./data/onemoduletype.json");
    if(!input){
        FAIL() << "Couldn't read file";
    }

    auto maybeTypeManager = parser.parseDocument(*input);
    if(!maybeTypeManager){
        FAIL() << "Parser didn't return a type manager";
    }
    nm::TypeManager &typeManager = *(*maybeTypeManager);
    //TODO assert user modules == 1

    nm::CompositeModuleType* terrainModuleType = typeManager.getUserType("terrainHeight");
    ASSERT_NE(terrainModuleType, nullptr) << "Couldn't find ModuleType terrainHeight";

    EXPECT_EQ("terrainHeight", terrainModuleType->getName());
    EXPECT_EQ("determines elevation based on position", terrainModuleType->getDescription());

    //verify input
    {
        auto *inputPosition = terrainModuleType->getInput("pos");
        ASSERT_NE(nullptr, inputPosition) << "Couldn't find a ModuleInput named \"pos\"";
        EXPECT_EQ("pos", inputPosition->getName());
        auto &posType = inputPosition->getSignalType();
        EXPECT_EQ(2, posType.dimensionality);
    }

    //check that the submodule is there
    {
        auto fbmmodule = terrainModuleType->getModule("fbm1");
        ASSERT_NE(nullptr, fbmmodule);
        EXPECT_EQ("fbm", fbmmodule->getType().getName());

        //check that it's connected to the input
        auto posInputLink = fbmmodule->getInput("pos");
        ASSERT_NE(nullptr, posInputLink);
        //TODO uncomment this part of the test
        //check that fbm.pos is connected to input
//        auto outputLink = posInputLink->getOutputLink();
//        ASSERT_NE(nullptr, outputLink);
//        EXPECT_EQ(terrainModuleType->getModule("input"), &(outputLink->getOwner()));
    }

    //verify output
    {
        auto *height = terrainModuleType->getOutput("height");
        ASSERT_NE(nullptr, height) << "Couldn't find a ModuleOutput named \"height\"";
        EXPECT_EQ("height", height->getName());
        auto &heightSignalType = height->getSignalType();
        EXPECT_EQ(1, heightSignalType.dimensionality);
    }
}
