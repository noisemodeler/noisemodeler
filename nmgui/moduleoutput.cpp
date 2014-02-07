#include "moduleoutput.hpp"

namespace nmgui {

ModuleOutputQ::ModuleOutputQ(QObject *theParent) :
    QObject(theParent)
{
}

QString ModuleOutputQ::name() const
{
    return m_name;
}

void ModuleOutputQ::setName(const QString &value)
{
    if(value != m_name){
        m_name = value;
        emit nameChanged();
    }
}

} // namespace nmgui
