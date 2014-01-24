#include "parser.hpp"

#include <rapidsjon/document.h>

#include <iostream>

namespace nm {

namespace {

optional<std::unique_ptr<ModuleType> > parseModuleType(const rapidjson::Value &type)
{
    auto &nameValue = type["name"];
    if(nameValue.IsNull()){
        std::cerr << "Module missing required field \"name\"\n";
        return {};
    }

    return {{}};
}

optional<std::map<std::string, std::unique_ptr<ModuleType> > > parseModuleTypeArray(const rapidjson::Value &array)
{
    return std::map<std::string, std::unique_ptr<ModuleType>>();
}

} // namespace

Parser::Parser()
{
}

optional<std::map<std::string, std::unique_ptr<ModuleType> > > Parser::parse(std::string input)
{
    rapidjson::Document document;
    document.Parse<0>(input.c_str());

    if(document.HasParseError()){
        std::cerr << "Couldn't parse json document\n";
        return {};
    }

    auto &moduleTypes = document["moduleTypes"];

    if(moduleTypes.IsNull()){
        std::cerr << "moduleTypes not present in root of document\n";
        return {};
    }

    return parseModuleTypeArray(moduleTypes);

}

} // namespace nm
