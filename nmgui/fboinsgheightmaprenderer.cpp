#include "fboinsgheightmaprenderer.hpp"

#include "heightmapterrainrenderer.hpp"

#include "moduleq.hpp"

#include <nmlib/codegeneration/glsl/glslgenerator.hpp>

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLContext>
#include <sstream>

namespace nmgui {

class HeightMapInFboRenderer : public QQuickFramebufferObject::Renderer {

    // Renderer interface
protected:
    void render() override {
        m_heightMapRenderer.render();
        update();
    }
    //QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

    //this is the only function where it is safe to communicate with the QQuickFrameBufferObject
    void synchronize(QQuickFramebufferObject *fbo) override
    {
        FboInSGHeightMapRenderer* fboInSGMapRenderer = dynamic_cast<FboInSGHeightMapRenderer*>(fbo);

        //TODO: could perhaps move compilation out of sync function
        if(fboInSGMapRenderer->m_generatorDirty){
            std::string source = "void elevation(in vec2 coords, out float height){height = 0.5;}";
            if(fboInSGMapRenderer->m_inputLink != nullptr && fboInSGMapRenderer->m_outputLink != nullptr){
                source = nm::glsl::GlslGenerator::compileToGlslFunction(
                            fboInSGMapRenderer->m_inputLink->inputLink(),
                            fboInSGMapRenderer->m_outputLink->outputLink(),
                            "elevation");
            }
            fboInSGMapRenderer->m_generatorDirty = false;
            m_heightMapRenderer.setGeneratorSource(source);
        }

        m_heightMapRenderer.setDomain(fboInSGMapRenderer->m_domain);
    }
private:
    HeightMapTerrainRenderer m_heightMapRenderer;
};

FboInSGHeightMapRenderer::FboInSGHeightMapRenderer(QQuickItem *the_parent) :
    QQuickFramebufferObject(the_parent),
    m_generatorDirty(true),
    m_inputLink(nullptr),
    m_outputLink(nullptr),
    m_domain(0,0,1,1)
{
}

void FboInSGHeightMapRenderer::setInputLink(InputLinkQ *newLink)
{
    if(newLink==m_inputLink){
        return;
    }
    m_inputLink = newLink;
    emit inputLinkChanged();
}

void FboInSGHeightMapRenderer::setOutputLink(OutputLinkQ *newLink)
{
    if(newLink==m_outputLink){
        return;
    }
    //dicsonnect all signals, since we are about to forget about this input
    if(m_outputLink!=nullptr)disconnect(m_outputLink, 0, this, 0);
    m_outputLink = newLink;
    connect(m_outputLink->owner(), SIGNAL(dependenciesChanged()), this, SLOT(handleModelChanged()));
    emit outputLinkChanged();
}

void FboInSGHeightMapRenderer::handleModelChanged()
{
    m_generatorDirty = true;
    update();
}

QQuickFramebufferObject::Renderer *FboInSGHeightMapRenderer::createRenderer() const
{
    return new HeightMapInFboRenderer();
}

} // namespace nmgui
