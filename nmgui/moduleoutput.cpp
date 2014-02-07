#include "outputlinkq.hpp"

namespace nmgui {

OutputLinkQ::OutputLinkQ(QObject *theParent) :
    QObject(theParent)
{
}

QString OutputLinkQ::name() const
{
    return m_name;
}

void OutputLinkQ::setName(const QString &value)
{
    if(value != m_name){
        m_name = value;
        emit nameChanged();
    }
}

} // namespace nmgui
