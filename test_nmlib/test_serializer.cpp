#include "nmlib/serialization/serializer.hpp"
#include "nmlib/serialization/parser.hpp"
#include "nmlib/model/typemanager.hpp"

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
        auto input = moduleType->getGraph()->getModule("inputs")->getOutput("in1");
        moduleType->getGraph()->getModule("outputs")->getInput("out1")->link(*input);
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
        auto graph = moduleType->getGraph();
        ASSERT_NE(nullptr, graph);
        EXPECT_EQ(1, moduleInput->getSignalType().dimensionality);

        //check that there is an output as well
        auto moduleOutput = moduleType->getOutput("out1");
        ASSERT_NE(nullptr, moduleOutput) << json;
        EXPECT_EQ(1, moduleInput->getSignalType().dimensionality);

        //there should also be an inputs module
        auto inputsModule = graph->getModule("inputs");
        ASSERT_NE(nullptr, inputsModule);
    }
}
