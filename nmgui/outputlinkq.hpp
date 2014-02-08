#ifndef NMGUI_MODULEOUTPUT_HPP
#define NMGUI_MODULEOUTPUT_HPP

#include <QObject>

#include <nmlib/util/signals.hpp>

namespace nm{
class OutputLink;
}

namespace nmgui {

class OutputLinkQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    explicit OutputLinkQ(nm::OutputLink* outputLink = nullptr, QObject *parent = 0);
    virtual ~OutputLinkQ();
    static OutputLinkQ *fromOutputLink(nm::OutputLink &outputLink);
    nm::OutputLink& outputLink();

    QString name() const;

private:
    nm::OutputLink *m_outputLink;
    boost::signals2::scoped_connection m_outputLinkDestroyingConnection;
};

} // namespace nmgui

#endif // NMGUI_MODULEOUTPUT_HPP
