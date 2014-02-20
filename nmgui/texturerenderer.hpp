#ifndef NMGUI_TEXTURERENDERER_HPP
#define NMGUI_TEXTURERENDERER_HPP

#include "inputlinkq.hpp"
#include "outputlinkq.hpp"

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <nmlib/model.hpp>

namespace nmgui {

class TextureRenderer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
    Q_PROPERTY(nmgui::InputLinkQ* inputLink READ inputLink WRITE setInputLink NOTIFY inputLinkChanged)
    Q_PROPERTY(nmgui::OutputLinkQ* outputLink READ outputLink WRITE setOutputLink NOTIFY outputLinkChanged)
    Q_PROPERTY(QRectF domain READ domain WRITE setDomain NOTIFY domainChanged)
public:
    explicit TextureRenderer(QQuickItem *the_parent = 0);

    qreal t() const {return m_t;}
    InputLinkQ *inputLink() const {return m_inputLink;}
    OutputLinkQ *outputLink() const {return m_outputLink;}
    QRectF domain() const {return m_domain;}
    void setT(qreal new_t);
    void setInputLink(InputLinkQ *newLink);
    void setOutputLink(OutputLinkQ *newLink);
    void setDomain(QRectF domain){m_domain = domain;}

signals:
    void tChanged();
    void inputLinkChanged();
    void outputLinkChanged();
    void domainChanged();

public slots:
    void paint();
    void cleanup();
    void sync();

private slots:
    void handleWindowChanged(QQuickWindow *win);
    void handleModelChanged();

private:
    void compileProgram();
    QOpenGLShaderProgram *m_program;

    bool m_generatorDirty;
    std::string m_thread_generatorFunctionSource;
    bool m_thread_sourceDirty;
    InputLinkQ *m_inputLink;
    OutputLinkQ *m_outputLink;
    qreal m_t;
    qreal m_thread_t;
    QRectF m_domain;
    QRectF m_thread_domain;
};

} // namespace nmgui

#endif // NMGUI_TEXTURERENDERER_HPP
