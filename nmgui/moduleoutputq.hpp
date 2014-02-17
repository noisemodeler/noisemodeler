#ifndef NMGUI_MODULEOUTPUTQ_HPP
#define NMGUI_MODULEOUTPUTQ_HPP

#include <QObject>

namespace nm {
class ModuleOutput;
}

namespace nmgui {

class ModuleOutputQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    explicit ModuleOutputQ(nm::ModuleOutput *moduleOutput = nullptr, QObject *parent = 0);
    static ModuleOutputQ* fromModuleOutput(nm::ModuleOutput &moduleOutput);

    QString name() const;

private:
    nm::ModuleOutput* m_moduleOutput;
};

} // namespace nmgui

#endif // NMGUI_MODULEOUTPUTQ_HPP
