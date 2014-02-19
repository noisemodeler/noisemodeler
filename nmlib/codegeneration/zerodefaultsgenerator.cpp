#include <nmlib/codegeneration/zerodefaultsgenerator.hpp>

#include <nmlib/codegeneration/inlinegenerator.hpp>

#include <nmlib/model/module.hpp>
#include <nmlib/model/signalvalue.hpp>
#include <nmlib/model/moduleinput.hpp>

#include <nmlib/util.hpp>

namespace nm {

void ZeroDefaultsGenerator::generateDefaults(InlineGenerator &gen, std::ostream &out)
{
    for(auto inputLink : m_module.getInputs()){
        auto variableName = inputLink->getModuleInput().getName();
        auto signalType = inputLink->getModuleInput().getSignalType();
        auto zero = make_unique<SignalValue>(signalType);

        auto assignment = make_unique<Assignment>(
            make_unique<Variable>(variableName),
            make_unique<Value>(std::move(zero))
        );
        assignment->gen(gen, out);
    }
}

} // namespace nm
