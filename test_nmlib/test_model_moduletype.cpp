#include <nmlib/model.hpp>
#include <nmlib/util.hpp>

#include <gtest/gtest.h>

#include <fstream>

TEST(ModelModuleTypeTest, BuiltinModuleType){
    nm::ModuleType moduleType{"test", "testdescription"};
    EXPECT_EQ("test", moduleType.getName());
    EXPECT_EQ("testdescription", moduleType.getDescription());

    //inputs
    moduleType.addInput("testinput", nm::SignalType{2});
    auto input = moduleType.getInput("testinput");
    ASSERT_NE(nullptr, input);
    EXPECT_EQ("testinput", input->getName());
    EXPECT_EQ(2, input->getSignalType().dimensionality);

    //outputs
    moduleType.addOutput("testoutput", nm::SignalType{3});
    auto output = moduleType.getOutput("testoutput");
    ASSERT_NE(nullptr, output);
    EXPECT_EQ("testoutput", output->getName());
    EXPECT_EQ(3, output->getSignalType().dimensionality);
}

TEST(ModelModuleTypeTest, PrimitiveModuleTypeBasic){
    //TODO why doesn't it work with a simple stack allocation?
    nm::ModuleType moduleType{"test", nm::ModuleType::Category::Primitive, "testdescription"};
    EXPECT_EQ("test", moduleType.getName());
    EXPECT_EQ("testdescription", moduleType.getDescription());
    EXPECT_FALSE(moduleType.isComposite());
    EXPECT_TRUE(moduleType.isPrimitive());
}

TEST(ModelModuleTypeTest, CompositeModuleTypeBasic){
    //TODO why doesn't it work with a simple stack allocation?
    nm::ModuleType moduleType{"test", "testdescription"};
    EXPECT_EQ("test", moduleType.getName());
    EXPECT_EQ("testdescription", moduleType.getDescription());
    EXPECT_TRUE(moduleType.isComposite());
    EXPECT_FALSE(moduleType.isPrimitive());
}

TEST(ModelModuleTypeTest, CompositeModuleTypeInputAdding){
    //TODO why doesn't it work with a simple stack allocation?
    nm::ModuleType moduleType{"test"};
    ASSERT_TRUE(moduleType.isComposite());
    moduleType.addInput("in1", nm::SignalType{1});
    auto moduleInput = moduleType.getInput("in1");
    EXPECT_EQ("in1", moduleInput->getName());
    auto graph = moduleType.getGraph();
    ASSERT_NE(nullptr, graph);
    auto inputsModule = graph->getModule("inputs");
    ASSERT_NE(nullptr, inputsModule);
    EXPECT_NE(nullptr, inputsModule->getInput("in1"));
}

