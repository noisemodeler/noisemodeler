#include "core.hpp"

#include <QFile>

namespace nmgui {

Core::Core(QObject *parent) :
    QObject(parent),
    m_licenseString("ERROR: License placeholder not replaced")
{
    QFile data(":/LICENSE.md");
    data.open(QIODevice::ReadOnly);
    m_licenseString = QString(data.readAll());
    data.close();
}

QString Core::licenseText() const
{
    return m_licenseString;
}

QString Core::versionString() const
{
    return NMVER;
}

} // namespace nmgui
