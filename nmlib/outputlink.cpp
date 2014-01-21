#include <nmlib/outputlink.hpp>

#include <nmlib/inputlink.hpp>
#include <nmlib/moduleinput.hpp>
#include <nmlib/moduleoutput.hpp>
#include <nmlib/signaltype.hpp>

namespace nm {

bool OutputLink::addLink(InputLink *input)
{
    if(input == nullptr || input->p_type->p_type->isConvertibleTo(*(p_type->p_type))){
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
