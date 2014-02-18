#ifndef NM_BODYGENERATOR_HPP
#define NM_BODYGENERATOR_HPP

#include <ostream>

namespace nm {

class InlineGenerator;

class BodyGenerator
{
public:
    virtual void generateBody(InlineGenerator &gen, std::ostream &out) = 0;
    virtual ~BodyGenerator() {}
};

} // namespace nm

#endif // NM_BODYGENERATOR_HPP
