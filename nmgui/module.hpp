#ifndef NMGUI_MODULE_H
#define NMGUI_MODULE_H

#include <QObject>
#include <QQmlListProperty>

#include <nmlib/model.hpp>

namespace nmgui {

class ModuleInputQ;
class ModuleOutputQ;

class Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleInputQ> inputs READ inputs NOTIFY inputsChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleOutputQ> outputs READ outputs NOTIFY outputsChanged)
public:
    explicit Module(nm::Module* module = nullptr, QObject *parent = 0);

    QString name() const;
    void setName(const QString &value);

    QQmlListProperty<ModuleInputQ> inputs();
    QQmlListProperty<ModuleOutputQ> outputs();

signals:
    void nameChanged();
    void inputsChanged();
    void outputsChanged();

public slots:

private:
    static void append_input(QQmlListProperty<ModuleInputQ> *list, ModuleInputQ *input);
    static ModuleInputQ* inputAt(QQmlListProperty<ModuleInputQ> *list, int index);
    static int inputsCount(QQmlListProperty<ModuleInputQ> *list);
    static void clearInputs(QQmlListProperty<ModuleInputQ> *list);

    static void append_output(QQmlListProperty<ModuleOutputQ> *list, ModuleOutputQ *output);
    static ModuleOutputQ* outputAt(QQmlListProperty<ModuleOutputQ> *list, int index);
    static int outputsCount(QQmlListProperty<ModuleOutputQ> *list);
    static void clearOutputs(QQmlListProperty<ModuleOutputQ> *list);

    QString m_name;
    QList<ModuleInputQ *> m_inputs;
    QList<ModuleOutputQ *> m_outputs;

    nm::Module *p_module;
};

} // namespace nmgui

#endif // NMGUI_MODULE_H
