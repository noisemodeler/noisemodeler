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
    if(!input.getModuleInput().getSignalType().isConvertibleTo(c_moduleOutput.getSignalType())){
        return false;
    }
    input.link(*this);
    //TODO make sure there isn't already an input for this moduleinput
    m_inputLinks.push_back(&input);
    linksChanged(*this);
    return true;
}

bool OutputLink::unlink(InputLink *input)
{
    input->unlink();
    auto it = std::find(begin(m_inputLinks), end(m_inputLinks), input);
    if(it==m_inputLinks.end())return false;
    m_inputLinks.erase(it);
    linksChanged(*this);
    return true;
}

void OutputLink::unlinkAll()
{
    if(m_inputLinks.empty())return;
    for(auto &inputLink : m_inputLinks){
        unlink(inputLink);
    }
}

InputLink *OutputLink::getLink(unsigned int index) {
    if(index>=m_inputLinks.size())return nullptr;
    return m_inputLinks[index];
}

} // namespace nm
