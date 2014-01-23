#include "parser.hpp"

#include <rapidsjon/document.h>

namespace nm {

Parser::Parser()
{
}

nm::optional<std::map<std::string, std::unique_ptr<ModuleType> > > Parser::parse(std::string input)
{
    rapidjson::Document d;
    d.Parse<0>(input.c_str());

    if(d.HasParseError()){
        return nm::optional<std::map<std::string, std::unique_ptr<ModuleType>>>();
    }

//    auto &a = d["moduleTypes"];
    return nm::optional<std::map<std::string, std::unique_ptr<ModuleType>>>(std::map<std::string, std::unique_ptr<ModuleType>>());
}

} // namespace nm
