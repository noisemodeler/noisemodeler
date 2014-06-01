#ifndef NM_PARSER_HPP
#define NM_PARSER_HPP

#include <nmlib/optional.hpp>

#include <map>
#include <memory>

namespace nm {

class TypeManager;

/**
 * @brief Converts json strings to TypeManager%s
 * @ingroup serialization
 *
 * A parser is typically used like this:
 *
 * ~~~{.cpp}
 * //replace readfile with your file reading function
 * std::string json = readFile("terrain.nm.json");
 * Parser parser;
 * auto maybeTypeManager = parser.parseDocument(json);
 * if(!maybeTypeManager){
 *     //error handling
 * }
 * TypeManager& typeManager = **maybeTypeManager;
 *
 * //use the type manager
 * ~~~
 *
 */
class Parser
{
public:
    explicit Parser();
    optional<std::unique_ptr<TypeManager>> parseDocument(std::string json);
};

} // namespace nm

#endif // NM_PARSER_HPP
