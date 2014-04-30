#include "serializer.hpp"

//TODO get rapidjson to fix these warnings
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#include <rapidsjon/prettywriter.h>
#include <rapidsjon/document.h>
#include <rapidsjon/stringbuffer.h>

#include <sstream>
#include <iostream> //TODO remove

namespace {

//implements rapidjson::Stream
template <typename Encoding>
struct GenericStdStringStreamWrapper {
    typedef typename Encoding::Ch Ch;
    GenericStdStringStreamWrapper(){}
//    Ch Peek() const { return *src_; }
//    Ch Take() { return *src_++; }
//    size_t Tell() const { return src_ - head_; }
    Ch* PutBegin() { return 0; }
    void Put(Ch c) { stream << c; }
    size_t PutEnd(Ch*) { return 0; }
    std::stringstream stream;
};
typedef GenericStdStringStreamWrapper<rapidjson::UTF8<> > StdStringStreamWrapper;

}

namespace nm {

Serializer::Serializer()
{
}

std::string Serializer::serialize(const TypeManager &/*typeManager*/)
{
    //TODO
    rapidjson::Document document;
    document.Parse<0>("{ \"hello\": \"world\" }");
//    document.AddMember("test", "test", document.GetAllocator());

    //make an std::string from the document
    StdStringStreamWrapper streamWrapper;
    rapidjson::PrettyWriter<StdStringStreamWrapper> writer(streamWrapper);
    document.Accept(writer);

    return streamWrapper.stream.str();
}

} // namespace nm
