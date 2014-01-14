#ifndef NMGUI_MODULEINPUT_H
#define NMGUI_MODULEINPUT_H

#include <QObject>

namespace nmgui {

class ModuleOutput;

class ModuleInput : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(nmgui::ModuleOutput* source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit ModuleInput(QObject *parent = 0);
    QString name() const;
    void setName(const QString &value);
    ModuleOutput* source();
    void setSource(ModuleOutput *value);

signals:
    void nameChanged();
    void sourceChanged();

public slots:

private:
    QString m_name;
    ModuleOutput* m_source;
};

} // namespace nmgui

#endif // NMGUI_MODULEINPUT_H
