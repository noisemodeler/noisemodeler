#ifndef NM_DEFAULTSGENERATOR_HPP
#define NM_DEFAULTSGENERATOR_HPP

#include <ostream>

namespace nm {

class InlineGenerator;

/**
 * @brief Generates the definitions and default values module inputs
 * @ingroup codegeneration
 */
class DefaultsGenerator
{
public:
    virtual void generateDefaults(InlineGenerator &gen, std::ostream &out) = 0;
    virtual ~DefaultsGenerator(){}
};

} // namespace nm

#endif // NM_DEFAULTSGENERATOR_HPP
