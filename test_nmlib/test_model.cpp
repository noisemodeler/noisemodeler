#include <nmlib/model.hpp>
#include <nmlib/util.hpp>

#include <gtest/gtest.h>

#include <fstream>

namespace {

TEST(ModelTest, SignalType){
    auto signalType = nm::SignalType{4};
    EXPECT_EQ(4, signalType.dimensionality);
}

//tests if changes to the moduletype propagates to instantiated modules
TEST(ModelTest, ModuleTypeToModulePropagation){
    nm::ModuleType moduleType{"test"};
    auto moduleInput = moduleType.addInput("testinput", nm::SignalType{3});
    auto moduleOutput = moduleType.addOutput("testoutput", nm::SignalType{2});
    nm::Module module{moduleType, "a"};
    EXPECT_EQ(1, module.getInputSize());
    EXPECT_EQ(1, module.getOutputSize());
    auto input1 = module.getInput(0);
    auto output1 = module.getOutput(0);
    ASSERT_NE(nullptr, input1);
    ASSERT_NE(nullptr, output1);
    EXPECT_EQ("testinput", input1->getModuleInput().getName());
    EXPECT_EQ("testoutput", output1->getModuleOutput().getName());

    EXPECT_EQ(true, moduleType.removeInput(moduleInput));
    EXPECT_EQ(true, moduleType.removeOutput(moduleOutput));
    EXPECT_EQ(0, module.getInputSize());
    EXPECT_EQ(0, module.getOutputSize());
    EXPECT_EQ(nullptr, module.getInput("testinput"));
    EXPECT_EQ(nullptr, module.getOutput("testoutput"));

    moduleType.addInput("testinput2", nm::SignalType{3});
    moduleType.addOutput("testoutput2", nm::SignalType{3});
    EXPECT_EQ(1, module.getInputSize());
    EXPECT_EQ(1, module.getOutputSize());
    auto input2 = module.getInput(0);
    auto output2 = module.getOutput(0);
    ASSERT_NE(nullptr, input2);
    ASSERT_NE(nullptr, output2);
    EXPECT_EQ("testinput2", input2->getModuleInput().getName());
    EXPECT_EQ("testoutput2", output2->getModuleOutput().getName());
}

TEST(ModelTest, TopologicalTraversal){
    //create a simple test module type
    auto moduleType = make_unique<nm::ModuleType>("test", "testdescription");
    moduleType->addInput("in1", nm::SignalType{1});
    moduleType->addInput("in2", nm::SignalType{1});
    moduleType->addOutput("result", nm::SignalType{1});

    //create some modules
    nm::Module a(*moduleType, "a");
    nm::Module b(*moduleType, "b");
    nm::Module c(*moduleType, "c");
    nm::Module d(*moduleType, "d");

    //connect them together. a is connected to b which is connected to both c and d
    a.getInput("in1")->link(*b.getOutput("result"));
    b.getInput("in1")->link(*c.getOutput("result"));
    b.getInput("in2")->link(*d.getOutput("result"));

    std::vector<std::string> names;

    auto appendName = [&](nm::Module& module){
        names.push_back(module.getName());
    };

    nm::Module::topologicallyTraverseDependencies({a.getOutput("result")}, appendName);
    EXPECT_EQ("a", names.back()); //we expect a to be last because it depends on everything
    EXPECT_EQ("b", names[2]); //b depends on everything except a, so we expect it to be second last
    EXPECT_EQ(4, names.size()); //just check that all nodes were visited
}

TEST(ModelTest, ModuleDepthAndHeight){
    //create a simple test module type
    nm::ModuleType moduleType{"test", "testdescription"};
    moduleType.addInput("in1", nm::SignalType{1});
    moduleType.addInput("in2", nm::SignalType{1});
    moduleType.addOutput("result", nm::SignalType{1});

    //create some modules
    nm::Module a(moduleType, "a");
    nm::Module b(moduleType, "b");
    nm::Module c(moduleType, "c");
    nm::Module d(moduleType, "d");

    //connect them together. a is connected to b which is connected to both c and d
    a.getInput("in1")->link(*b.getOutput("result"));
    b.getInput("in1")->link(*c.getOutput("result"));
    b.getInput("in2")->link(*d.getOutput("result"));

    EXPECT_EQ(2, a.getDepth());
    EXPECT_EQ(1, b.getDepth());
    EXPECT_EQ(0, c.getDepth());
    EXPECT_EQ(0, d.getDepth());

    EXPECT_EQ(0, a.getHeight());
    EXPECT_EQ(1, b.getHeight());
    EXPECT_EQ(2, c.getHeight());
    EXPECT_EQ(2, d.getHeight());

}

TEST(ModelTest, GraphSimple){
    nm::ModuleType moduleType{"test", "testdescription"};
    nm::Graph graph;
    EXPECT_EQ(0, graph.numModules());
    auto module = graph.createModule(moduleType);
    ASSERT_NE(nullptr, module);
    EXPECT_EQ(1, graph.numModules());
    EXPECT_EQ(module, graph.getModule("test_1"));
    EXPECT_EQ(module, graph.getModule(0));
    bool touched = false;
    graph.moduleRemoved.connect([&](nm::Graph&, nm::Module& cbModule, unsigned int){
        EXPECT_EQ(module, &cbModule);
        touched = true;
    });
    auto moduleUP = graph.removeModule(*module);
    EXPECT_EQ(module, moduleUP.get());
    EXPECT_EQ(true, touched);
    EXPECT_EQ(0, graph.numModules());
}

TEST(ModelTest, LinkUnlinkAll){
    nm::ModuleType moduleType{"test", "testdescription"};
    moduleType.addInput("in1", nm::SignalType{1});
    moduleType.addOutput("out1", nm::SignalType{1});
    nm::Module a{moduleType, "a"}, b{moduleType, "b"};
    EXPECT_EQ(nullptr, a.getOutput(0)->getLink(0));
    EXPECT_EQ(nullptr, a.getInput(0)->getOutputLink());
    a.getInput(0)->link(*b.getOutput(0));
    EXPECT_EQ(b.getOutput(0), a.getInput(0)->getOutputLink());
    EXPECT_EQ(a.getInput(0), b.getOutput(0)->getLink(0));
    b.getOutput(0)->unlinkAll();
    EXPECT_EQ(nullptr, a.getInput(0)->getOutputLink());
    EXPECT_EQ(nullptr, b.getOutput(0)->getLink(0));
}

}
