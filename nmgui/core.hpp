#ifndef NMGUI_CORE_HPP
#define NMGUI_CORE_HPP

#include <QObject>

namespace nmgui {

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString licenseText READ licenseText CONSTANT)
    Q_PROPERTY(QString versionString READ versionString CONSTANT)
public:
    explicit Core(QObject *parent = nullptr);
    QString licenseText() const;
    QString versionString() const;

private:
    QString m_licenseString;
};

} // namespace nmgui

#endif // NMGUI_CORE_HPP
