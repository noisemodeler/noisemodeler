#ifndef NMGUI_TEXTURERENDERER_HPP
#define NMGUI_TEXTURERENDERER_HPP

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>

namespace nmgui {

class TextureRenderer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)
public:
    explicit TextureRenderer(QQuickItem *the_parent = 0);

    qreal t() const {return m_t;}
    void setT(qreal new_t);

signals:
    void tChanged();

public slots:
    void paint();
    void cleanup();
    void sync();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    QOpenGLShaderProgram *m_program;

    qreal m_t;
    qreal m_thread_t;
};

} // namespace nmgui

#endif // NMGUI_TEXTURERENDERER_HPP
