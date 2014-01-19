#include "moduleoutput.hpp"

namespace nmgui {

ModuleOutput::ModuleOutput(QObject *parent) :
    QObject(parent)
{
}

QString ModuleOutput::name() const
{
    return m_name;
}

void ModuleOutput::setName(const QString &value)
{
    if(value != m_name){
        m_name = value;
        emit nameChanged();
    }
}

} // namespace nmgui
