#include <nmlib/model.hpp>
#include <nmlib/util.hpp>

#include <gtest/gtest.h>

#include <fstream>

TEST(ModelConstantsTest, SingleDefaultValue){
    nm::ModuleType moduleType("testModuleType");
    //TODO move to separate tests
    moduleType.addInput("myConstant", 0.6f);
    nm::ModuleInput* moduleInput1 = moduleType.getInput("myConstant");
    ASSERT_NE(nullptr, moduleInput1);
    const nm::SignalValue defaultValue = moduleInput1->getDefaultValue();
    EXPECT_EQ(1, defaultValue.getSignalType().dimensionality);
    EXPECT_EQ(0.6f, moduleInput1->getDefaultValue()[0]);
}

TEST(ModelConstantsTest, TripleDefaultValue){
    nm::ModuleType moduleType("testModuleType");
    moduleType.addInput("myConstant", std::vector<float>{1,2,3});
    nm::ModuleInput* moduleInput2 = moduleType.getInput("myConstant");
    ASSERT_NE(nullptr, moduleInput2);
    const nm::SignalValue defaultValue = moduleInput2->getDefaultValue();
    EXPECT_EQ(3, defaultValue.getSignalType().dimensionality);
    EXPECT_EQ(1, defaultValue[0]);
    EXPECT_EQ(2, defaultValue[1]);
    EXPECT_EQ(3, defaultValue[2]);
}

TEST(ModelConstantsTest, DefaultValueInstantiated){
    nm::ModuleType moduleType("testModuleType");
    moduleType.addInput("myConstant", std::vector<float>{1,2,3});
    nm::Module module(moduleType, "testModule");
    nm::InputLink* inputLink = module.getInput("myConstant");
    ASSERT_NE(nullptr, inputLink);
    nm::SignalValue unlinkedValue = inputLink->getUnlinkedValue();
    EXPECT_EQ(3, unlinkedValue.getSignalType().dimensionality);
    EXPECT_EQ(1, unlinkedValue[0]);
    EXPECT_EQ(2, unlinkedValue[1]);
    EXPECT_EQ(3, unlinkedValue[2]);
}
