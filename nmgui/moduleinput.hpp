#ifndef NMGUI_MODULEINPUT_H
#define NMGUI_MODULEINPUT_H

#include <QObject>

namespace nmgui {

class ModuleOutputQ;

class ModuleInputQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(nmgui::ModuleOutputQ* source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit ModuleInputQ(QObject *parent = 0);
    QString name() const;
    void setName(const QString &value);
    ModuleOutputQ* source();
    void setSource(ModuleOutputQ *value);

signals:
    void nameChanged();
    void sourceChanged();

public slots:

private:
    QString m_name;
    ModuleOutputQ* m_source;
};

} // namespace nmgui

#endif // NMGUI_MODULEINPUT_H
