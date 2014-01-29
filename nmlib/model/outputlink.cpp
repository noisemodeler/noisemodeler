#include <nmlib/model/outputlink.hpp>

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/signaltype.hpp>

namespace nm {

bool OutputLink::addLink(InputLink *input)
{
    if(input == nullptr || input->getModuleInput().getSignalType().isConvertibleTo(c_moduleOutput.getSignalType())){
        return false;
    }
    input->link(this);
    return m_inputLinks.insert(input).second;
}

bool OutputLink::unlink(InputLink *input)
{
    std::set<InputLink*>::iterator it = m_inputLinks.find(input);
    if(it != m_inputLinks.end()){
        m_inputLinks.erase(it);
        return true;
    } else {
        return false;
    }
}

void OutputLink::unlinkAll()
{
    m_inputLinks.clear();
}

} // namespace nm
