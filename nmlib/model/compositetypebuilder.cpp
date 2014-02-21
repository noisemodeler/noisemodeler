#include <nmlib/model/compositetypebuilder.hpp>

#include <nmlib/model/graph.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

namespace nm {

std::unique_ptr<nm::ModuleType> nm::CompositeTypeBuilder::releaseModuleType() { return std::unique_ptr<ModuleType>{m_moduleType.release()}; }

bool CompositeTypeBuilder::addInput(std::string /*name*/, SignalType /*signalType*/)
{
    //TODO
    std::cerr << "not implemented\n";
    return false;
}

bool CompositeTypeBuilder::exportOutput(const OutputLink &/*outputLink*/, std::string /*externalName*/)
{
    //TODO
    std::cerr << "not implemented\n";
    return false;
}

} // namespace nm
