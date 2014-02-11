#include "outputlinkq.hpp"
#include "inputlinkq.hpp"

#include <nmlib/model/outputlink.hpp>
#include <nmlib/model/moduleoutput.hpp>

namespace nmgui {

OutputLinkQ::OutputLinkQ(nm::OutputLink* outputLink, QObject *theParent) :
    QObject(theParent),
    m_outputLink(outputLink)
{
//    QASSERT(outputLink!=nullptr);

    //forward events
    m_linksChangedConnection = m_outputLink->linksChanged.connect([&](nm::OutputLink&){
        emit linksChanged();
    });

    //make provide a way for other wrappers to get to this wrapper
    m_outputLink->setUserData(this);

    //make sure wrapper is deleted when model is destroyed
    m_outputLinkDestroyingConnection = m_outputLink->destroying.connect([&](nm::OutputLink&){
        deleteLater();
        m_outputLink->setUserData(nullptr);
    });
}

OutputLinkQ::~OutputLinkQ()
{
    if(m_outputLink!=nullptr)m_outputLink->setUserData(nullptr);
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

nm::OutputLink &OutputLinkQ::outputLink()
{
    return *m_outputLink;
}

QQmlListProperty<InputLinkQ> OutputLinkQ::links()
{
    return QQmlListProperty<InputLinkQ>(this, 0, nullptr, &OutputLinkQ::linkCount, &OutputLinkQ::linkAt, nullptr);
}

QString OutputLinkQ::name() const
{
    auto name = m_outputLink->getModuleOutput().getName();
    return QString::fromUtf8(name.data(), name.size());
}

InputLinkQ *OutputLinkQ::linkAt(QQmlListProperty<InputLinkQ> *list, int index)
{
    OutputLinkQ* outputLinkQ= qobject_cast<OutputLinkQ *>(list->object);
    if(outputLinkQ){
        auto inputLink = outputLinkQ->m_outputLink->getLink(index);
        Q_ASSERT(inputLink!=nullptr);
        return InputLinkQ::fromInputLink(*inputLink);
    } else {
        return nullptr;
    }
}

int OutputLinkQ::linkCount(QQmlListProperty<InputLinkQ> *list)
{
    OutputLinkQ *outputLinkQ= qobject_cast<OutputLinkQ *>(list->object);
    if(outputLinkQ){
        return outputLinkQ->m_outputLink->numLinks();
    } else {
        return 0;
    }
}

} // namespace nmgui
