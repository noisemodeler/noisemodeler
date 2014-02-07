#include "moduleinput.hpp"

namespace nmgui {

ModuleInputQ::ModuleInputQ(QObject *p) :
    QObject(p), m_source(NULL)
{
}

QString ModuleInputQ::name() const
{
    return m_name;
}

void ModuleInputQ::setName(const QString &value)
{
    if(value != m_name){
        m_name = value;
        emit nameChanged();
    }
}

ModuleOutputQ *ModuleInputQ::source()
{
    return m_source;
}

void ModuleInputQ::setSource(ModuleOutputQ *value)
{
    if(value != m_source){
        m_source = value;
        emit sourceChanged();
    }
}

} // namespace nmgui
