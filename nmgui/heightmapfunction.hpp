#ifndef NMGUI_HEIGHTMAPFUNCTION_HPP
#define NMGUI_HEIGHTMAPFUNCTION_HPP

#include <inputlinkq.hpp>
#include <outputlinkq.hpp>

#include <QObject>

namespace nmgui {

class HeightMapFunction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(nmgui::InputLinkQ* inputLink READ inputLink WRITE setInputLink NOTIFY inputLinkChanged)
    Q_PROPERTY(nmgui::OutputLinkQ* outputLink READ outputLink WRITE setOutputLink NOTIFY outputLinkChanged)
public:
    explicit HeightMapFunction(QObject *parent = 0);

    //getters
    InputLinkQ *inputLink() const {return m_inputLink;}
    OutputLinkQ *outputLink() const {return m_outputLink;}

    //setters
    void setInputLink(InputLinkQ *newLink);
    void setOutputLink(OutputLinkQ *newLink);

signals:
    void inputLinkChanged();
    void outputLinkChanged();
    //this signal is emitted whenever the function changes, a catchall for inputlinkchanged, outputlinkchanged, dependencieschanged...
    void functionChanged();

private:
    InputLinkQ *m_inputLink;
    OutputLinkQ *m_outputLink;
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAPFUNCTION_HPP
