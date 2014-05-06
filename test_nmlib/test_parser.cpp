#include <nmlib/serialization/parser.hpp>
#include <nmlib/model/typemanager.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/graph.hpp>
#include <nmlib/model/module.hpp>

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
    auto typeManager = parser.parseDocument(R"( {"moduleTypes":[]} )");
    if(!typeManager){
        FAIL();
    }
    EXPECT_EQ(0, (*typeManager)->numUserTypes());
}

TEST(ParserTest, OneModuleType){
    nm::Parser parser;
    auto input = readFile("./data/onemoduletype.nm.json");
    if(!input){
        FAIL() << "Couldn't read file";
    }

    auto maybeTypeManager = parser.parseDocument(*input);
    if(!maybeTypeManager){
        FAIL() << "Parser didn't return a type manager";
    }
    nm::TypeManager &typeManager = *(*maybeTypeManager);
    //TODO assert user modules == 1

    nm::ModuleType* terrainModuleType = typeManager.getUserType("terrainHeight");
    ASSERT_NE(terrainModuleType, nullptr) << "Couldn't find ModuleType terrainHeight";

    EXPECT_EQ("terrainHeight", terrainModuleType->getName());
    EXPECT_EQ("determines elevation based on position", terrainModuleType->getDescription());

    //verify input
    {
        auto *inputPosition = terrainModuleType->getInput("pos");
        ASSERT_NE(nullptr, inputPosition) << "Couldn't find a ModuleInput named \"pos\"";
        EXPECT_EQ("pos", inputPosition->getName());
        auto posType = inputPosition->getSignalType();
        EXPECT_EQ(2, posType.dimensionality);
    }

    //check that the submodule is there
    {
        auto graph = terrainModuleType->getGraph();
        ASSERT_NE(nullptr, graph);

        auto fbmmodule = graph->getModule("fbm1");
        ASSERT_NE(nullptr, fbmmodule);
        EXPECT_EQ("fbm2", fbmmodule->getType().getName());

        //check that it's connected to the input
        auto posInputLink = fbmmodule->getInput("pos");
        ASSERT_NE(nullptr, posInputLink);

        //check that fbm.pos is connected to input
        auto outputLink = posInputLink->getOutputLink();
        ASSERT_NE(nullptr, outputLink);
        EXPECT_EQ(graph->getModule("inputs"), &(outputLink->getOwner()));
    }

    //verify output
    {
        auto *height = terrainModuleType->getOutput("height");
        ASSERT_NE(nullptr, height) << "Couldn't find a ModuleOutput named \"height\"";
        EXPECT_EQ("height", height->getName());
        auto heightSignalType = height->getSignalType();
        EXPECT_EQ(1, heightSignalType.dimensionality);
    }
}

TEST(ParserTest, VectorValues){
    auto input = readFile("./data/constants.nm.json");
    nm::Parser parser;
    if(!input){
        FAIL();
    }
    auto maybeTypeManager = parser.parseDocument(*input);
    if(!maybeTypeManager){
        FAIL() << "Couldn't parse document: " << *input;
    }
    nm::TypeManager &typeManager = *(*maybeTypeManager);

    auto terrainModuleType = typeManager.getUserType("terrain");
    ASSERT_NE(nullptr, terrainModuleType);
    auto fbmModule = terrainModuleType->getGraph()->getModule("fBm");
    ASSERT_NE(nullptr, fbmModule);
    {
        auto octavesInput = fbmModule->getInput("octaves");
        auto octavesValue = octavesInput->getUnlinkedValue();
        EXPECT_EQ(6, octavesValue[0]);
    }

    {
        auto positionInput = fbmModule->getInput("pos");
        auto positionValue = positionInput->getUnlinkedValue();
        EXPECT_EQ(1, positionValue[0]);
        EXPECT_EQ(2, positionValue[1]);
    }

    {
        auto seedInput = fbmModule->getInput("seed");
        auto seedValue = seedInput->getUnlinkedValue();
        EXPECT_EQ(123, seedValue[0]);
    }
}
