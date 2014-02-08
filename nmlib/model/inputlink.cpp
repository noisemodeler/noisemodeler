#include "inputlink.hpp"

#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/signaltype.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>

namespace nm {

InputLink::~InputLink()
{
    destroying(*this);
}

bool InputLink::link(OutputLink &output)
{
    if(&output == p_outputLink ||
            c_moduleInput.getSignalType() != output.getModuleOutput().getSignalType()){
        return false;
    }
    if(p_outputLink != nullptr){
        unlink();
    }
    p_outputLink = &output;
    output.addLink(*this);
    linkChanged(*this);
    return true;
}

void InputLink::unlink()
{
    if(p_outputLink == nullptr){
        return;
    }

    OutputLink *tmp = p_outputLink;
    p_outputLink = nullptr;
    if(tmp != nullptr){
        tmp->unlink(this);
    }
    linkChanged(*this);
}

} // namespace nm
