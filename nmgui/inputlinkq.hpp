#ifndef NMGUI_MODULEINPUT_H
#define NMGUI_MODULEINPUT_H

#include <QObject>

#include <nmlib/model.hpp>

namespace nmgui {

class OutputLinkQ;

class InputLinkQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(nmgui::OutputLinkQ* source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit InputLinkQ(nm::InputLink* inputLink = nullptr, QObject *parent = nullptr);
    QString name() const;
    OutputLinkQ* source();
    void setSource(OutputLinkQ *value);

signals:
    void sourceChanged();

public slots:

private:
    OutputLinkQ* m_source;
    nm::InputLink *m_inputLink;
};

} // namespace nmgui

#endif // NMGUI_MODULEINPUT_H
