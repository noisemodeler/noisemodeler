#ifndef NMGUI_MODULEOUTPUT_HPP
#define NMGUI_MODULEOUTPUT_HPP

#include <QObject>

namespace nm{
class OutputLink;
}

namespace nmgui {

class OutputLinkQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
public:
    explicit OutputLinkQ(nm::OutputLink* outputLink = nullptr, QObject *parent = 0);
    static OutputLinkQ *fromOutputLink(nm::OutputLink &outputLink);

    QString name() const;

private:
    nm::OutputLink *m_outputLink;
};

} // namespace nmgui

#endif // NMGUI_MODULEOUTPUT_HPP
