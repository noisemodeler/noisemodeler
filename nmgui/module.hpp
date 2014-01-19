#ifndef NMGUI_MODULE_H
#define NMGUI_MODULE_H

#include <QObject>
#include <QQmlListProperty>

namespace nmgui {

class ModuleInput;
class ModuleOutput;

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleInput> inputs READ inputs NOTIFY inputsChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleOutput> outputs READ outputs NOTIFY outputsChanged)
public:
    explicit Module(QObject *parent = 0);

    QString name() const;
    void setName(const QString &value);

    QQmlListProperty<ModuleInput> inputs();
    QQmlListProperty<ModuleOutput> outputs();

signals:
    void nameChanged();
    void inputsChanged();
    void outputsChanged();

public slots:

private:
    static void append_input(QQmlListProperty<ModuleInput> *list, ModuleInput *input);
    static ModuleInput* inputAt(QQmlListProperty<ModuleInput> *list, int index);
    static int inputsCount(QQmlListProperty<ModuleInput> *list);
    static void clearInputs(QQmlListProperty<ModuleInput> *list);

    static void append_output(QQmlListProperty<ModuleOutput> *list, ModuleOutput *output);
    static ModuleOutput* outputAt(QQmlListProperty<ModuleOutput> *list, int index);
    static int outputsCount(QQmlListProperty<ModuleOutput> *list);
    static void clearOutputs(QQmlListProperty<ModuleOutput> *list);

    QString m_name;
    QList<ModuleInput *> m_inputs;
    QList<ModuleOutput *> m_outputs;
};

} // namespace nmgui

#endif // NMGUI_MODULE_H
