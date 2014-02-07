#include "inputlinkq.hpp"

namespace nmgui {

InputLinkQ::InputLinkQ(nm::InputLink *inputLink, QObject *p) :
    QObject(p), m_source(NULL), m_inputLink(inputLink)
{
}

QString InputLinkQ::name() const
{
    auto str = m_inputLink->getModuleInput().getName();
    return QString::fromUtf8(str.data(), str.size());
}

OutputLinkQ *InputLinkQ::source()
{
    return m_source;
}

void InputLinkQ::setSource(OutputLinkQ *value)
{
    if(value != m_source){
        m_source = value;
        emit sourceChanged();
    }
}

} // namespace nmgui
