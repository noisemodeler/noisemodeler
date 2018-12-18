#ifndef NMGUI_MODULEOUTPUTQ_HPP
#define NMGUI_MODULEOUTPUTQ_HPP

#include <nmlib/util/signals.hpp>

#include <QObject>

namespace nm {
class ModuleOutput;
}

namespace nmgui {

class ModuleOutputQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int dimensionality READ dimensionality CONSTANT)
public:
    explicit ModuleOutputQ(nm::ModuleOutput *moduleOutput = nullptr, QObject *parent = nullptr);
    static ModuleOutputQ* fromModuleOutput(nm::ModuleOutput &moduleOutput);

    QString name() const;
    int dimensionality() const;
    nm::ModuleOutput *moduleOutput(){return m_moduleOutput;}

private:
    nm::ModuleOutput* m_moduleOutput;

    boost::signals2::scoped_connection moduleOutputDestroyingConnection;
};

} // namespace nmgui

#endif // NMGUI_MODULEOUTPUTQ_HPP
