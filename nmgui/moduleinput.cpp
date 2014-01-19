#include "moduleinput.h"

namespace nmgui {

ModuleInput::ModuleInput(QObject *parent) :
    QObject(parent), m_source(NULL)
{
}

QString ModuleInput::name() const
{
    return m_name;
}

void ModuleInput::setName(const QString &value)
{
    if(value != m_name){
        m_name = value;
        emit nameChanged();
    }
}

ModuleOutput *ModuleInput::source()
{
    return m_source;
}

void ModuleInput::setSource(ModuleOutput *value)
{
    if(value != m_source){
        m_source = value;
        emit sourceChanged();
    }
}

} // namespace nmgui