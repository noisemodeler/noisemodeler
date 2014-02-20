#ifndef NMGUI_MODULEINPUTQ_HPP
#define NMGUI_MODULEINPUTQ_HPP

#include <QObject>

namespace nm {
class ModuleInput;
}

namespace nmgui {

class ModuleInputQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    explicit ModuleInputQ(nm::ModuleInput *moduleInput = nullptr, QObject *parent = 0);
    static ModuleInputQ* fromModuleInput(nm::ModuleInput &moduleInput);

    QString name() const;

private:
    nm::ModuleInput* m_moduleInput;
};

} // namespace nmgui

#endif // NMGUI_MODULEINPUTQ_HPP