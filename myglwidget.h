#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H


#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QDir>

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core
{
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer *m_vertexBuffer;
    QOpenGLBuffer *m_indexBuffer;
    QOpenGLShaderProgram *m_computeProgram;
    QOpenGLShaderProgram *m_renderProgram;
    QOpenGLShader *m_computeShader;
    QOpenGLShader *m_fragmentShader;
    QOpenGLShader *m_vertexShader;
    QOpenGLTexture *m_texture;
    float roll;

public:
    MyGLWidget(QWidget *parent);
    ~MyGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

signals:

public slots:
};

#endif // MYGLWIDGET_H
