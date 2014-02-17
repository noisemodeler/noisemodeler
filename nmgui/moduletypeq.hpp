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

class ModuleTypeQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleInputQ> inputs READ inputs NOTIFY inputsChanged)
    Q_PROPERTY(QQmlListProperty<nmgui::ModuleOutputQ> outputs READ outputs NOTIFY outputsChanged)
public:
    //should have been protected, but not allowed by qt
    explicit ModuleTypeQ(nm::ModuleType *moduleType = nullptr, QObject *parent = 0);
    static ModuleTypeQ* fromModuleType(nm::ModuleType &moduleType);

    QString name() const;
    QQmlListProperty<ModuleInputQ> inputs();
    QQmlListProperty<ModuleOutputQ> outputs();

signals:
    void inputsChanged(); //TODO connect
    void outputsChanged();

private:
    nm::ModuleType *m_moduleType;

    static ModuleInputQ* inputAt(QQmlListProperty<ModuleInputQ> *list, int index);
    static int inputsCount(QQmlListProperty<ModuleInputQ> *list);

    static ModuleOutputQ* outputAt(QQmlListProperty<ModuleOutputQ> *list, int index);
    static int outputsCount(QQmlListProperty<ModuleOutputQ> *list);

//    boost::signals2::scoped_connection moduleTypeDestroyedConnection;
};

} // namespace nmgui

#endif // NMGUI_MODULETYPEQ_HPP
