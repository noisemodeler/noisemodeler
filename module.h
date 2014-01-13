#ifndef NMGUI_MODULE_H
#define NMGUI_MODULE_H

#include <QObject>
#include <QQmlListProperty>

namespace nmgui {

class ModuleInput;
class ModuleOuput;

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleInput> inputs READ inputs NOTIFY inputsChanged)
public:
    explicit Module(QObject *parent = 0);

    QString name() const;
    void setName(const QString &value);

    QQmlListProperty<ModuleInput> inputs();

signals:
    void nameChanged();
    void inputsChanged();

public slots:

private:
    static void append_input(QQmlListProperty<ModuleInput> *list, ModuleInput *input);
    static ModuleInput* inputAt(QQmlListProperty<ModuleInput> *list, int index);
    static int inputsCount(QQmlListProperty<ModuleInput> *list);
    static void clearInputs(QQmlListProperty<ModuleInput> *list);

    QString m_name;
    QList<ModuleInput *> m_inputs;
};

} // namespace nmgui

#endif // NMGUI_MODULE_H
