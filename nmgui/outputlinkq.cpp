#include "outputlinkq.hpp"

#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/moduleoutput.hpp>

namespace nmgui {

OutputLinkQ::OutputLinkQ(nm::OutputLink* outputLink, QObject *theParent) :
    QObject(theParent),
    m_outputLink(outputLink)
{
//    QASSERT(outputLink!=nullptr);
    outputLink->setUserData(this);
}

OutputLinkQ *OutputLinkQ::fromOutputLink(nm::OutputLink &outputLink)
{
    auto userData = outputLink.getUserData();
    if(userData!=nullptr){
        return static_cast<OutputLinkQ*>(userData);
    } else {
        return new OutputLinkQ(&outputLink);
    }
}

QString OutputLinkQ::name() const
{
    auto name = m_outputLink->getModuleOutput().getName();
    return QString::fromUtf8(name.data(), name.size());
}

} // namespace nmgui
