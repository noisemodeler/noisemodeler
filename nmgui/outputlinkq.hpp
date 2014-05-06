#ifndef NMGUI_MODULEOUTPUT_HPP
#define NMGUI_MODULEOUTPUT_HPP

#include <nmlib/util/signals.hpp>

#include <QObject>
#include <QtQml/QQmlListProperty>

namespace nm{
class OutputLink;
}

namespace nmgui {

class InputLinkQ;
class ModuleQ;

class OutputLinkQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(nmgui::ModuleQ* owner READ owner CONSTANT)
    Q_PROPERTY(int dimensionality READ dimensionality CONSTANT)
    Q_PROPERTY(QQmlListProperty<nmgui::InputLinkQ> links READ links NOTIFY linksChanged)
public:
    explicit OutputLinkQ(nm::OutputLink* outputLink = nullptr, QObject *parent = 0);
    virtual ~OutputLinkQ();
    static OutputLinkQ *fromOutputLink(nm::OutputLink &outputLink);
    nm::OutputLink& outputLink();

    int dimensionality() const;
    QQmlListProperty<InputLinkQ> links();
    QString name() const;
    ModuleQ *owner();

signals:
    void linksChanged();

private:
    static InputLinkQ* linkAt(QQmlListProperty<InputLinkQ> *list, int index);
    static int linkCount(QQmlListProperty<InputLinkQ> *list);

    nm::OutputLink *m_outputLink;
    boost::signals2::scoped_connection m_outputLinkDestroyingConnection;
    boost::signals2::scoped_connection m_linksChangedConnection;
};

} // namespace nmgui

#endif // NMGUI_MODULEOUTPUT_HPP
