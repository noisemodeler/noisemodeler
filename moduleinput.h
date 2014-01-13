#ifndef NMGUI_MODULEINPUT_H
#define NMGUI_MODULEINPUT_H

#include <QObject>

namespace nmgui {

class ModuleInput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit ModuleInput(QObject *parent = 0);
    QString name() const;
    void setName(const QString &value);

signals:
    void nameChanged();

public slots:

private:
    QString m_name;
};

} // namespace nmgui

#endif // NMGUI_MODULEINPUT_H
