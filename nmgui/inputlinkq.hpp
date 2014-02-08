#ifndef NMGUI_MODULEINPUT_H
#define NMGUI_MODULEINPUT_H

#include <QObject>

namespace nm {
class InputLink;
}

namespace nmgui {

class OutputLinkQ;

class InputLinkQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(nmgui::OutputLinkQ* outputLink READ outputLink WRITE outputLink NOTIFY sourceChanged)
public:
    explicit InputLinkQ(nm::InputLink* inputLink = nullptr, QObject *parent = nullptr);
    static InputLinkQ *fromInputLink(nm::InputLink& outputLink);

    QString name() const;
    OutputLinkQ* outputLink();
    void outputLink(OutputLinkQ *value);

signals:
    void sourceChanged();

public slots:

private:
    OutputLinkQ* m_source;
    nm::InputLink *m_inputLink;
};

} // namespace nmgui

#endif // NMGUI_MODULEINPUT_H
