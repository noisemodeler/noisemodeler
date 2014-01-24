#include <nmlib/parser.hpp>

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
    auto modules = parser.parse("Malformed");
    EXPECT_FALSE(modules);
}

TEST(ParserTest, BlankDocument){
    nm::Parser parser;
    auto modules = parser.parse(R"( {"moduleTypes":[]} )");
    if(!modules){
        FAIL();
    }
    EXPECT_EQ(0, (*modules).size());
}

TEST(ParserTest, OneModuleType){
    nm::Parser parser;
    auto input = readFile("./data/onemoduletype.json");
    if(!input){
        FAIL() << "Couldn't read file";
    }

    auto maybeModules = parser.parse(*input);
    if(!maybeModules){
        FAIL() << "Parser didn't return a list of modules";
    }
    auto &modules = *maybeModules;
    ASSERT_EQ(1, modules.size());

    auto it = modules.find("terrainHeight");
    ASSERT_NE(modules.end(), it) << "Couldn't fint ModuleType terrainHeight";
    std::unique_ptr<nm::ModuleType> &terrainModuleTypePtr = (it->second);

    EXPECT_EQ("terrainHeight", terrainModuleTypePtr->getName());
    EXPECT_EQ("determines elevation based on position", terrainModuleTypePtr->getDescription());
}
