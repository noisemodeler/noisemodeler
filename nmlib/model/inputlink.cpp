#include "inputlink.hpp"

#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/signaltype.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/module.hpp>

namespace nm {

InputLink::InputLink(Module &owner, const ModuleInput &type):
    m_owner(owner),
    c_moduleInput(type),
    p_outputLink(nullptr),
    m_unlinkedValue(type.getDefaultValue())
{
    linkChanged.connect([&](InputLink&){
        m_owner.traverseDescendants([](Module& module){
            module.dependenciesChanged(module);
        });
    });
}

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

SignalValue InputLink::getUnlinkedValue()
{
    return m_unlinkedValue;
}

bool InputLink::setUnlinkedValue(SignalValue newValue)
{
    //TODO make some sort of error output if there is a type mismatch
    if(!newValue.getSignalType().isConvertibleTo(c_moduleInput.getSignalType()))return false;
    m_unlinkedValue = newValue;
    unlinkedValueChanged(*this);
    return true;
}

} // namespace nm
