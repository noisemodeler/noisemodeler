#include "functioncallbodygenerator.hpp"

namespace nm {

void FunctionCallBodyGenerator::generateBody(InlineGenerator &gen, std::ostream &out)
{
    m_fcall.gen(gen, out);
}

} // namespace nm
