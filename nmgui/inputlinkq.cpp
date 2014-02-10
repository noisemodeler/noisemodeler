#include "inputlinkq.hpp"
#include "outputlinkq.hpp"

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/moduleinput.hpp>

namespace nmgui {

InputLinkQ::InputLinkQ(nm::InputLink *inputLink, QObject *p) :
    QObject(p),
    m_inputLink(inputLink)
{
    m_inputLink->setUserData(this);
    m_inputLinkDestroyingConnection = m_inputLink->destroying.connect([&](nm::InputLink&){
        deleteLater();
        m_inputLink->setUserData(nullptr);
});
}

InputLinkQ::~InputLinkQ()
{
    if(m_inputLink!=nullptr)m_inputLink->setUserData(nullptr);
}

InputLinkQ *InputLinkQ::fromInputLink(nm::InputLink &outputLink)
{
    auto userData = outputLink.getUserData();
    if(userData!=nullptr){
        return static_cast<InputLinkQ*>(userData);
    } else {
        return new InputLinkQ(&outputLink);
    }
}

nm::InputLink &InputLinkQ::inputLink()
{
    return *m_inputLink;
}

QString InputLinkQ::name() const
{
    auto str = m_inputLink->getModuleInput().getName();
    return QString::fromUtf8(str.data(), str.size());
}

OutputLinkQ *InputLinkQ::outputLink()
{
    auto outputLink = m_inputLink->getOutputLink();
    return outputLink != nullptr ? OutputLinkQ::fromOutputLink(*outputLink) : nullptr;
}

void InputLinkQ::outputLink(OutputLinkQ *value)
{
    if(value == outputLink())return;
    m_inputLink->link(value->outputLink());
    emit outputLinkChanged();
}

} // namespace nmgui
