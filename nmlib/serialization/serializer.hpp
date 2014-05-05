#ifndef NM_SERIALIZER_HPP
#define NM_SERIALIZER_HPP

#include <string>

namespace nm {

class TypeManager;

/**
 * @brief Serializes a TypeManager to a JSON string
 * @ingroup serialization
 */
class Serializer
{
public:
    Serializer();
    std::string serialize(const TypeManager& typeManager);
};

} // namespace nm

#endif // NM_SERIALIZER_HPP
