#include "inputlinkq.hpp"
#include "outputlinkq.hpp"
#include "moduleq.hpp"

#include <nmlib/model/inputlink.hpp>
#include <nmlib/model/moduleinput.hpp>

#include <QVector4D>

namespace nmgui {

InputLinkQ::InputLinkQ(nm::InputLink *inputLink, QObject *p) :
    QObject(p),
    m_inputLink(inputLink)
{
    m_inputLink->setUserData(this);
    m_inputLinkDestroyingConnection = m_inputLink->destroying.connect([&](nm::InputLink&){
        deleteLater();
        m_inputLink->setUserData(nullptr);
        m_inputLink = nullptr;
    });

    m_outputLinkChangedConnection = m_inputLink->linkChanged.connect([&](nm::InputLink&){
        outputLinkChanged();
    });
    m_unlinkedValueChangedConnection = m_inputLink->unlinkedValueChanged.connect([&](nm::InputLink&){
        unlinkedValueChanged();
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

nm::InputLink *InputLinkQ::inputLink()
{
    return m_inputLink;
}

QString InputLinkQ::name() const
{
    auto str = m_inputLink->getModuleInput().getName();
    return QString::fromUtf8(str.data(), str.size());
}

int InputLinkQ::dimensionality() const
{
    return m_inputLink->getModuleInput().getSignalType().dimensionality;
}

OutputLinkQ *InputLinkQ::outputLink()
{
    auto outputLink = m_inputLink->getOutputLink();
    return outputLink != nullptr ? OutputLinkQ::fromOutputLink(*outputLink) : nullptr;
}

void InputLinkQ::setOutputLink(OutputLinkQ *value)
{
    if(value == outputLink())return;
    if(value == nullptr){
        m_inputLink->unlink();
    } else {
        m_inputLink->link(*value->outputLink());
    }
    emit outputLinkChanged();
}

ModuleQ *InputLinkQ::owner()
{
    return ModuleQ::fromModule(m_inputLink->getOwner());
}

void InputLinkQ::setUnlinkedValue(QVector4D value)
{
    std::vector<float> values(dimensionality());
    for(int i = 0; i<dimensionality(); ++i){
        values[i] = value[i];
    }
    m_inputLink->setUnlinkedValue(nm::SignalValue{values});
}

QVector4D InputLinkQ::unlinkedValue()
{
    nm::SignalValue signalValue = m_inputLink->getUnlinkedValue();
    QVector4D ret;
    for(int i=0; i<dimensionality(); ++i){
        ret[i] = signalValue[i];
    }
    return ret;
}

} // namespace nmgui
