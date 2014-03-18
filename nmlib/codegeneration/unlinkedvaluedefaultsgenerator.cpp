#include "unlinkedvaluedefaultsgenerator.hpp"

#include <nmlib/codegeneration/inlinegenerator.hpp>

#include <nmlib/model/module.hpp>
#include <nmlib/model/moduleinput.hpp>

#include <nmlib/util.hpp>

namespace nm {

void UnlinkedValueDefaultsGenerator::generateDefaults(InlineGenerator &gen, std::ostream &out)
{
    for(auto inputLink : m_module.getInputs()){
        auto variableName = inputLink->getModuleInput().getName();
        auto defaultValue = make_unique<SignalValue>(inputLink->getUnlinkedValue());

        Assignment assignment(
            make_unique<Variable>(variableName),
            make_unique<Value>(std::move(defaultValue))
        );
        assignment.gen(gen, out);
    }

}

} // namespace nm
