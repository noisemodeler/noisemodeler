#include <nmlib/parser.hpp>

#include <gtest/gtest.h>

TEST(ParserTest, Constructor) {
    nm::Parser* parser = new nm::Parser();
    delete parser;
    SUCCEED();
}
