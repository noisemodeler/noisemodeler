#ifndef NMGUI_MODULEOUTPUT_HPP
#define NMGUI_MODULEOUTPUT_HPP

#include <QObject>

namespace nmgui {

class ModuleOutput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit ModuleOutput(QObject *parent = 0);
    QString name() const;
    void setName(const QString &value);

signals:
    void nameChanged();

public slots:

private:
    QString m_name;
};

} // namespace nmgui

#endif // NMGUI_MODULEOUTPUT_HPP
