#ifndef NMGUI_MODULE_H
#define NMGUI_MODULE_H

#include <QObject>
#include <QQmlListProperty>

#include <nmlib/model.hpp>

namespace nmgui {

class InputLinkQ;
class OutputLinkQ;

class ModuleQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::InputLinkQ> inputs READ inputs NOTIFY inputsChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::OutputLinkQ> outputs READ outputs NOTIFY outputsChanged)
public:
    explicit ModuleQ(nm::Module* module = nullptr, QObject *parent = 0);

    QString name() const;
    void setName(const QString &value);

    QQmlListProperty<InputLinkQ> inputs();
    QQmlListProperty<OutputLinkQ> outputs();

signals:
    void nameChanged();
    void inputsChanged();
    void outputsChanged();

public slots:

private:
    static void append_input(QQmlListProperty<InputLinkQ> *list, InputLinkQ *input);
    static InputLinkQ* inputAt(QQmlListProperty<InputLinkQ> *list, int index);
    static int inputsCount(QQmlListProperty<InputLinkQ> *list);
    static void clearInputs(QQmlListProperty<InputLinkQ> *list);

    static void append_output(QQmlListProperty<OutputLinkQ> *list, OutputLinkQ *output);
    static OutputLinkQ* outputAt(QQmlListProperty<OutputLinkQ> *list, int index);
    static int outputsCount(QQmlListProperty<OutputLinkQ> *list);
    static void clearOutputs(QQmlListProperty<OutputLinkQ> *list);

    QString m_name;
    QList<InputLinkQ *> m_inputs;
    QList<OutputLinkQ *> m_outputs;

    nm::Module *p_module;
};

} // namespace nmgui

#endif // NMGUI_MODULE_H
