#ifndef NMGUI_FBOINSGHEIGHTMAPRENDERER_HPP
#define NMGUI_FBOINSGHEIGHTMAPRENDERER_HPP

#include "inputlinkq.hpp"
#include "outputlinkq.hpp"

#include <QtQuick/QQuickFramebufferObject>
#include <QtGui/QOpenGLShaderProgram>
#include <nmlib/model.hpp>

namespace nmgui {

class HeightMapInFboRenderer;

class FboInSGHeightMapRenderer : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(nmgui::InputLinkQ* inputLink READ inputLink WRITE setInputLink NOTIFY inputLinkChanged)
    Q_PROPERTY(nmgui::OutputLinkQ* outputLink READ outputLink WRITE setOutputLink NOTIFY outputLinkChanged)

    //TODO domainless
    Q_PROPERTY(QRectF domain READ domain WRITE setDomain NOTIFY domainChanged)

public:
    explicit FboInSGHeightMapRenderer(QQuickItem *the_parent = 0);

    InputLinkQ *inputLink() const {return m_inputLink;}
    OutputLinkQ *outputLink() const {return m_outputLink;}
    QRectF domain() const {return m_domain;}
    void setInputLink(InputLinkQ *newLink);
    void setOutputLink(OutputLinkQ *newLink);
    void setDomain(QRectF domain){m_domain = domain; update();}

    //QQuickFrameBufferObject
    Renderer *createRenderer() const override;

signals:
    void inputLinkChanged();
    void outputLinkChanged();
    void domainChanged();

private slots:
    void handleModelChanged();

private:
    bool m_generatorDirty;
    InputLinkQ *m_inputLink;
    OutputLinkQ *m_outputLink;
    QRectF m_domain;

    friend class HeightMapInFboRenderer;
};

} // namespace nmgui

#endif // NMGUI_FBOINSGHEIGHTMAPRENDERER_HPP
