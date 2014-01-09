#ifndef NMGUI_MODULE_H
#define NMGUI_MODULE_H

#include <QObject>

namespace nmgui {

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    explicit Module(QObject *parent = 0);

    QString name() const;
    void setName(const QString &value);

signals:
    void nameChanged();

public slots:

private:
    QString m_name;
};

} // namespace nmgui

#endif // NMGUI_MODULE_H
