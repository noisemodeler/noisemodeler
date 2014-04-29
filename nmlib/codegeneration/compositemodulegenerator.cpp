#include "compositemodulegenerator.hpp"

namespace nm {

CompositeModuleGenerator::CompositeModuleGenerator()
{
}

void CompositeModuleGenerator::generateDefaults(InlineGenerator &/*gen*/, std::ostream &/*out*/)
{
    //just use unlinkeddefaults
}

void CompositeModuleGenerator::generateBody(InlineGenerator &/*gen*/, std::ostream &/*out*/)
{
    //gather inputs/outputs
    //create remaps
    //call generatefromlinks?
}

} // namespace nm
