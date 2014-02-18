#ifndef NM_MODULEGENERATOR_HPP
#define NM_MODULEGENERATOR_HPP

#include <nmlib/codegeneration/bodygenerator.hpp>
#include <nmlib/codegeneration/defaultsgenerator.hpp>

namespace nm {

class ModuleGenerator : public BodyGenerator, public DefaultsGenerator
{
};

} // namespace nm

#endif // NM_MODULEGENERATOR_HPP
