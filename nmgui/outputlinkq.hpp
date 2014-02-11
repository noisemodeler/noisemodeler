#ifndef NMGUI_MODULEOUTPUT_HPP
#define NMGUI_MODULEOUTPUT_HPP

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <nmlib/util/signals.hpp>

namespace nm{
class OutputLink;
}

namespace nmgui {

class InputLinkQ;

class OutputLinkQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QQmlListProperty<nmgui::InputLinkQ> links READ links NOTIFY linksChanged)
public:
    explicit OutputLinkQ(nm::OutputLink* outputLink = nullptr, QObject *parent = 0);
    virtual ~OutputLinkQ();
    static OutputLinkQ *fromOutputLink(nm::OutputLink &outputLink);
    nm::OutputLink& outputLink();

    QQmlListProperty<InputLinkQ> links();

    QString name() const;

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
