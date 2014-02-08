#ifndef NMGUI_MODULE_H
#define NMGUI_MODULE_H

#include <QQmlListProperty>

#include <nmlib/util/signals.hpp>

namespace nm {
class Module;
}

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
    virtual ~ModuleQ();

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
    static InputLinkQ* inputAt(QQmlListProperty<InputLinkQ> *list, int index);
    static int inputsCount(QQmlListProperty<InputLinkQ> *list);

    static OutputLinkQ* outputAt(QQmlListProperty<OutputLinkQ> *list, int index);
    static int outputsCount(QQmlListProperty<OutputLinkQ> *list);

    boost::signals2::scoped_connection moduleDestroyedConnection;

    nm::Module *p_module;
};

} // namespace nmgui

#endif // NMGUI_MODULE_H
