#ifndef NMGUI_MODULETYPE_QHPP
#define NMGUI_MODULETYPE_QHPP

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <nmlib/util/signals.hpp>

namespace nm {
class ModuleType;
}

namespace nmgui {

class ModuleInputQ;
class ModuleOutputQ;
class GraphQ;

class ModuleTypeQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(bool removable READ removable CONSTANT)
    Q_PROPERTY(bool builtin READ builtin CONSTANT)
    Q_PROPERTY(bool graphInput READ graphInput CONSTANT)
    Q_PROPERTY(bool graphOutput READ graphOutput CONSTANT)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleInputQ> inputs READ inputs NOTIFY inputsChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleOutputQ> outputs READ outputs NOTIFY outputsChanged)
    Q_PROPERTY(nmgui::GraphQ* graph READ graph CONSTANT)
public:
    //should have been protected, but not allowed by qt
    explicit ModuleTypeQ(nm::ModuleType *moduleType = nullptr, QObject *parent = 0);
    static ModuleTypeQ *fromModuleType(nm::ModuleType &moduleType);
    static ModuleTypeQ *fromModuleType(const nm::ModuleType &moduleType);

    QString name() const;
    void setName(const QString &value);
    QString description() const;
    void setDescription(const QString &value);
    bool removable() const;
    bool builtin() const;
    bool graphInput() const;
    bool graphOutput() const;
    QQmlListProperty<ModuleInputQ> inputs();
    QQmlListProperty<ModuleOutputQ> outputs();
    GraphQ *graph();
    nm::ModuleType* moduleType() const {return m_moduleType;}

public slots:
    bool removeInput(nmgui::ModuleInputQ *moduleInput);
    bool removeOutput(nmgui::ModuleOutputQ *moduleOutput);
    bool addInput(QString name, int dimensionality);
    bool addOutput(QString name, int dimensionality);

signals:
    void inputsChanged();
    void outputsChanged();
    void nameChanged();
    void descriptionChanged();

private:

    nm::ModuleType *m_moduleType;

    static ModuleInputQ* inputAt(QQmlListProperty<ModuleInputQ> *list, int index);
    static int inputsCount(QQmlListProperty<ModuleInputQ> *list);

    static ModuleOutputQ* outputAt(QQmlListProperty<ModuleOutputQ> *list, int index);
    static int outputsCount(QQmlListProperty<ModuleOutputQ> *list);

    boost::signals2::scoped_connection moduleTypeDestroyedConnection;
    boost::signals2::scoped_connection inputAddedCon, outputAddedCon;
    boost::signals2::scoped_connection inputRemovedCon, outputRemovedCon;
    boost::signals2::scoped_connection nameChangedCon, descriptionChangedCon;
};

} // namespace nmgui

#endif // NMGUI_MODULETYPEQ_HPP
