#ifndef NM_SERIALIZER_HPP
#define NM_SERIALIZER_HPP

#include <string>

namespace nm {

class TypeManager;

class Serializer
{
public:
    Serializer();
    std::string serialize(const TypeManager& typeManager);
};

} // namespace nm

#endif // NM_SERIALIZER_HPP
