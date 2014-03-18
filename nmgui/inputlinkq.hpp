#ifndef NMGUI_MODULEINPUT_H
#define NMGUI_MODULEINPUT_H

#include <nmlib/util/signals.hpp>

#include <QObject>
#include <QVector4D>

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
    Q_PROPERTY(nmgui::OutputLinkQ* outputLink READ outputLink WRITE setOutputLink NOTIFY outputLinkChanged)
    Q_PROPERTY(QVector4D unlinkedValue READ unlinkedValue WRITE setUnlinkedValue NOTIFY unlinkedValueChanged)
public:
    explicit InputLinkQ(nm::InputLink* inputLink = nullptr, QObject *parent = nullptr);
    virtual ~InputLinkQ();
    static InputLinkQ *fromInputLink(nm::InputLink& setOutputLink);
    nm::InputLink &inputLink();

    QString name() const;
    int dimensionality() const;
    OutputLinkQ* outputLink();
    void setOutputLink(OutputLinkQ *value);
    ModuleQ *owner();

    //TODO convert from QVector4D to something more dynamic (this is just a quick and dirty hack)
    void setUnlinkedValue(QVector4D value);
    QVector4D unlinkedValue();

signals:
    void outputLinkChanged();
    void unlinkedValueChanged();

public slots:

private:
    nm::InputLink *m_inputLink;
    boost::signals2::scoped_connection m_inputLinkDestroyingConnection;
    boost::signals2::scoped_connection m_outputLinkChangedConnection;
    boost::signals2::scoped_connection m_unlinkedValueChangedConnection;
};

} // namespace nmgui

#endif // NMGUI_MODULEINPUT_H
