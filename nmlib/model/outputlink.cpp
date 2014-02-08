#include <nmlib/model/outputlink.hpp>

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/moduleinput.hpp>
#include <nmlib/model/moduleoutput.hpp>
#include <nmlib/model/signaltype.hpp>

namespace nm {

OutputLink::~OutputLink()
{
    destroying(*this);
}

bool OutputLink::addLink(InputLink &input)
{
    if(input.getModuleInput().getSignalType().isConvertibleTo(c_moduleOutput.getSignalType())){
        return false;
    }
    input.link(*this);
    bool changed = m_inputLinks.insert(&input).second;
    if(!changed)return false;
    linksChanged(*this);
    return true;
}

bool OutputLink::unlink(InputLink *input)
{
    std::set<InputLink*>::iterator it = m_inputLinks.find(input);
    if(it==m_inputLinks.end())return false;
    m_inputLinks.erase(it);
    linksChanged(*this);
    return true;
}

void OutputLink::unlinkAll()
{
    if(m_inputLinks.empty())return;
    m_inputLinks.clear();
    linksChanged(*this);
}

} // namespace nm
