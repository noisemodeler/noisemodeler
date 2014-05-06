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
 */
class Parser
{
public:
    explicit Parser();
    optional<std::unique_ptr<TypeManager>> parseDocument(std::string json);
};

} // namespace nm

#endif // NM_PARSER_HPP
