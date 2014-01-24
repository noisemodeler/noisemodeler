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
    std::cerr << *input;

    auto modules = parser.parse(*input);
    if(!modules){
        FAIL();
    }
    EXPECT_EQ(1, (*modules).size());
}
