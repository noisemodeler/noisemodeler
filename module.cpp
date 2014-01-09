#include "module.h"

namespace nmgui {

Module::Module(QObject *parent) :
    QObject(parent)
{
}

void Module::setName(const QString &value)
{
    if(value != m_name){
        m_name = value;
        emit nameChanged();
    }
}

QString Module::name() const
{
    return m_name;
}

} // namespace nmgui
