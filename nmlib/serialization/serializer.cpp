#include "serializer.hpp"

#include <nmlib/model/typemanager.hpp>

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

std::string Serializer::serialize(const TypeManager &typeManager)
{
    rapidjson::Document document;
    {
        rapidjson::Value moduleTypesValue;
        moduleTypesValue.SetArray();
        for(unsigned int i=0; i<typeManager.numUserTypes(); ++i){
            rapidjson::Value moduleTypeValue;
            moduleTypeValue.SetObject();
            moduleTypesValue.PushBack(moduleTypeValue, document.GetAllocator());
        }
        document.SetObject();
        document.AddMember("moduleTypes", moduleTypesValue, document.GetAllocator());
    }


    //make an std::string from the document
    StdStringStreamWrapper streamWrapper;
    rapidjson::PrettyWriter<StdStringStreamWrapper> writer(streamWrapper);
    document.Accept(writer);

    return streamWrapper.stream.str();
}

} // namespace nm
