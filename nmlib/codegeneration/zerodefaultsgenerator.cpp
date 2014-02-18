#include <nmlib/codegeneration/zerodefaultsgenerator.hpp>

#include <nmlib/codegeneration/inlinegenerator.hpp>

#include <nmlib/model/module.hpp>
#include <nmlib/model/signalvalue.hpp>
#include <nmlib/model/moduleinput.hpp>

namespace nm {

void ZeroDefaultsGenerator::generateDefaults(InlineGenerator &gen, std::ostream &out)
{
    for(auto inputLink : m_module.getInputs()){
        gen.assignVariable(inputLink->getModuleInput().getName(), SignalValue{inputLink->getModuleInput().getSignalType()}, out);
    }
}

} // namespace nm
