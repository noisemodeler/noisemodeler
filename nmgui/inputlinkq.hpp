#ifndef NMGUI_MODULEINPUT_H
#define NMGUI_MODULEINPUT_H

#include <nmlib/util/signals.hpp>

#include <QObject>

namespace nm {
class InputLink;
}

namespace nmgui {

class OutputLinkQ;
class ModuleQ;

class InputLinkQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(nmgui::ModuleQ* owner READ owner CONSTANT)
    Q_PROPERTY(int dimensionality READ dimensionality CONSTANT)
    Q_PROPERTY(nmgui::OutputLinkQ* outputLink READ outputLink WRITE outputLink NOTIFY outputLinkChanged)
public:
    explicit InputLinkQ(nm::InputLink* inputLink = nullptr, QObject *parent = nullptr);
    virtual ~InputLinkQ();
    static InputLinkQ *fromInputLink(nm::InputLink& outputLink);
    nm::InputLink &inputLink();

    QString name() const;
    int dimensionality() const;
    OutputLinkQ* outputLink();
    void outputLink(OutputLinkQ *value);
    ModuleQ *owner();

signals:
    void outputLinkChanged();

public slots:

private:
    nm::InputLink *m_inputLink;
    boost::signals2::scoped_connection m_inputLinkDestroyingConnection;
};

} // namespace nmgui

#endif // NMGUI_MODULEINPUT_H
