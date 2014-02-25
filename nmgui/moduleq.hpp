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
class ModuleTypeQ;

class ModuleQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::InputLinkQ> inputs READ inputs NOTIFY inputsChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::OutputLinkQ> outputs READ outputs NOTIFY outputsChanged)
    Q_PROPERTY(nmgui::ModuleTypeQ *moduleType READ moduleType CONSTANT)
public:
    explicit ModuleQ(nm::Module* module = nullptr, QObject *parent = 0);
    explicit ModuleQ(ModuleTypeQ& type, QObject *parent = 0);
    virtual ~ModuleQ();
    static ModuleQ* fromModule(nm::Module &module);

    QString name() const;
    void setName(const QString &value);
    QString description() const;
    void setDescription(const QString &value);
    ModuleTypeQ *moduleType();
    nm::Module *module() { return p_module; }

    Q_INVOKABLE int getDepth(); //TODO rename to depth and make it property with a notifier

    QQmlListProperty<InputLinkQ> inputs();
    QQmlListProperty<OutputLinkQ> outputs();

signals:
    void nameChanged();
    void descriptionChanged();
    void inputsChanged();
    void outputsChanged();
    void dependenciesChanged();

public slots:

private:
    static InputLinkQ* inputAt(QQmlListProperty<InputLinkQ> *list, int index);
    static int inputsCount(QQmlListProperty<InputLinkQ> *list);

    static OutputLinkQ* outputAt(QQmlListProperty<OutputLinkQ> *list, int index);
    static int outputsCount(QQmlListProperty<OutputLinkQ> *list);

    boost::signals2::scoped_connection nameChangedCon, descriptionChangedCon;
    boost::signals2::scoped_connection moduleDestroyedConnection;
    boost::signals2::scoped_connection dependenciesChangedConnection;
    boost::signals2::scoped_connection inputAddedCon, inputRemovedCon;
    boost::signals2::scoped_connection outputAddedCon, outputRemovedCon;

    nm::Module *p_module;
};

} // namespace nmgui

#endif // NMGUI_MODULE_H
