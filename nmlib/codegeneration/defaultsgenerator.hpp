#ifndef NM_DEFAULTSGENERATOR_HPP
#define NM_DEFAULTSGENERATOR_HPP

#include <ostream>

namespace nm {

class InlineGenerator;

class DefaultsGenerator
{
public:
    virtual void generateDefaults(InlineGenerator &gen, std::ostream &out) = 0;
    virtual ~DefaultsGenerator(){}
};

} // namespace nm

#endif // NM_DEFAULTSGENERATOR_HPP
