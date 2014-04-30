#include "nmlib/serialization/serializer.hpp"
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
    EXPECT_EQ("", json);
}
