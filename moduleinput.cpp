#include "moduleinput.h"

namespace nmgui {

ModuleInput::ModuleInput(QObject *parent) :
    QObject(parent)
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

} // namespace nmgui
