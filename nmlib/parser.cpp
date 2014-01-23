#include "parser.hpp"

#include <rapidsjon/document.h>

#include <iostream>
using std::cout;

namespace nm {

Parser::Parser()
{
}

std::map<std::string, std::unique_ptr<ModuleType> > Parser::parse(std::string input)
{
    rapidjson::Document d;
    d.Parse<0>(input.c_str());
    auto &a = d["moduleTypes"];

    cout << a.IsNull() << std::endl;

}

} // namespace nm
