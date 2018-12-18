#include <nmlib/serialization/serializer.hpp>
#include <nmlib/serialization/parser.hpp>
#include <nmlib/model/typemanager.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/graph.hpp>
#include <nmlib/model/module.hpp>

#include <gtest/gtest.h>

TEST(SerializerTest, Constructor) {
    nm::Serializer* serializer = new nm::Serializer();
    delete serializer;
    SUCCEED();
}

TEST(SerializerTest, EmptyDocument) {
    nm::TypeManager typeManager;
    nm::Serializer serializer;
    std::string json = serializer.serialize(typeManager);
    nm::Parser parser;
    auto maybeTypeManager = parser.parseDocument(json);
    if(!maybeTypeManager){
        FAIL();
    }
    auto &typeManager2 = **maybeTypeManager;
    EXPECT_EQ(0, typeManager2.numUserTypes());
}

TEST(SerializerTest, OneModuleType) {
    nm::TypeManager typeManager;
    typeManager.initBuiltinTypes();
    {
        auto moduleType = make_unique<nm::ModuleType>("test");
        moduleType->addInput("in1", nm::SignalType{1});
        moduleType->addOutput("out1", nm::SignalType{1});
        auto input = moduleType->getInputModule()->getOutput("in1");
        moduleType->getOutputModule()->getInput("out1")->link(*input);
        auto absModule = moduleType->getGraph()->createModule(*typeManager.getBuiltinType("abs"), "testmodule");
        absModule->getInput(0)->link(*input); //connect abs input to the graph input
        typeManager.addUserType(std::move(moduleType));
    }

    nm::Serializer serializer;
    std::string json = serializer.serialize(typeManager);
    nm::Parser parser;
    auto maybeTypeManager = parser.parseDocument(json);
    if(!maybeTypeManager){
        FAIL() << "Couldn't parse document:\n" << json;
    }
    auto &typeManager2 = **maybeTypeManager;
    EXPECT_EQ(1, typeManager2.numUserTypes());

    {
        unsigned int i = 0;
        auto moduleType = typeManager2.getUserType(i);
        ASSERT_NE(nullptr, moduleType);
        ASSERT_EQ("test", moduleType->getName());
        ASSERT_TRUE(moduleType->isComposite());

        //verify that there is an input
        auto moduleInput = moduleType->getInput("in1");
        ASSERT_NE(nullptr, moduleInput);
        EXPECT_EQ("in1", moduleInput->getName());
        EXPECT_EQ(1, moduleInput->getSignalType().dimensionality);

        //check that there is an output as well
        auto moduleOutput = moduleType->getOutput("out1");
        ASSERT_NE(nullptr, moduleOutput) << json;
        EXPECT_EQ(1, moduleInput->getSignalType().dimensionality);

        //check that there's a graph
        auto graph = moduleType->getGraph();
        ASSERT_NE(nullptr, graph);

        //there should also be an inputs module in the graph
        auto inputsModule = graph->getModule("inputs");
        EXPECT_NE(nullptr, inputsModule);
        EXPECT_EQ(inputsModule, moduleType->getInputModule());

        //and the testModule
        auto testModule = graph->getModule("testmodule");
        ASSERT_NE(nullptr, testModule) << "Couldn't find testModule in document:\n" << json;
        //check that it's still connected
        EXPECT_NE(nullptr, testModule->getInput(0)->getOutputLink()) << "testModule.source was not connected: \n" << json;
    }
}

TEST(SerializerTest, DisconnectedOutput) {
    nm::TypeManager typeManager;
    typeManager.initBuiltinTypes();
    nm::ModuleType *terrainType = typeManager.createUserType("terrain");
    terrainType->addOutput("bongo", nm::SignalType{2});
    nm::Serializer serializer;
    std::string json = serializer.serialize(typeManager);

    std::cout << json << "\n";

    nm::Parser parser;
    auto maybeTypeManager = parser.parseDocument(json);
    if(!maybeTypeManager){
        FAIL() << "Couldn't parse document:\n" << json;
    }
    nm::TypeManager &typeManager2 = **maybeTypeManager;
    EXPECT_EQ(1, typeManager2.numUserTypes());

    nm::ModuleType *terrainTypeParsed = typeManager2.getUserType("terrain");
    ASSERT_NE(nullptr, terrainTypeParsed);
    nm::ModuleOutput *bongoOutput = terrainTypeParsed->getOutput("bongo");
    ASSERT_NE(nullptr, bongoOutput);
    EXPECT_EQ(2, bongoOutput->getSignalType().dimensionality);
}
