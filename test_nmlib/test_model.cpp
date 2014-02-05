#include <nmlib/model.hpp>

#include <gtest/gtest.h>

#include <fstream>

namespace {

TEST(ModelTest, SignalType){
    auto signalType = nm::SignalType{4};
    EXPECT_EQ(4, signalType.dimensionality);
}

TEST(ModelTest, BuiltinModuleType){
    nm::BuiltinModuleType moduleType{"test", "testdescription"};
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

TEST(ModelTest, CompositeModuleTypeBasic){
    //TODO why doesn't it work with a simple stack allocation?
    std::unique_ptr<nm::CompositeModuleType> moduleType{new nm::CompositeModuleType("test", "testdescription")};
    EXPECT_EQ("test", moduleType->getName());
    EXPECT_EQ("testdescription", moduleType->getDescription());
}

}
