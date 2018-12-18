#ifndef NM_PARSER_HPP
#define NM_PARSER_HPP

#include <map>
#include <memory>
#include <optional>

namespace nm {

class TypeManager;

/**
 * @ingroup serialization
 * @brief Converts json strings to TypeManager%s
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
    std::optional<std::unique_ptr<TypeManager>> parseDocument(std::string json);
};

} // namespace nm

#endif // NM_PARSER_HPP
