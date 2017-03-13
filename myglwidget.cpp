#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    roll=0.0;
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    setFormat(format);
}

MyGLWidget::~MyGLWidget()
{
    makeCurrent();
    delete m_computeShader;
    delete m_vertexShader;
    delete m_fragmentShader;
    delete m_texture;
    delete m_renderProgram;
    delete m_computeProgram;
    delete m_indexBuffer;
    delete m_vertexBuffer;
}

void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0,0,1,1);

    m_vao.create();
    if (m_vao.isCreated()){
        m_vao.bind();
        qDebug() << "VAO created!";
    }

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, -1.0f,
        1.0f, 1.0f
    };
    static const GLushort g_element_buffer_data[] = { 0, 1, 2, 3 };

    m_vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m_vertexBuffer->create();
    m_vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_vertexBuffer->bind();
    m_vertexBuffer->allocate(g_vertex_buffer_data,sizeof(g_vertex_buffer_data));

    m_indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m_indexBuffer->create();
    m_indexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer->bind();
    m_indexBuffer->allocate(g_element_buffer_data,sizeof(g_element_buffer_data));

    glActiveTexture(GL_TEXTURE0);
    //m_texture = new QOpenGLTexture(QImage(QDir::currentPath()+"/../OpenGLComputeExample/example_image.png").mirrored());
    m_texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_texture->create();
    m_texture->setFormat(QOpenGLTexture::RGBA8_UNorm);
    m_texture->setSize(512,512);
    m_texture->setMinificationFilter(QOpenGLTexture::Linear);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->allocateStorage();
    m_texture->bind();

    glBindImageTexture(0, m_texture->textureId(), 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA8);
    qDebug() << m_texture->width() << m_texture->height();

    m_computeShader = new QOpenGLShader(QOpenGLShader::Compute);
    m_computeShader->compileSourceFile(QDir::currentPath()+"/../OpenGLComputeExample/example.cs");

    m_vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    m_vertexShader->compileSourceFile(QDir::currentPath()+"/../OpenGLComputeExample/example.vs");

    m_fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    m_fragmentShader->compileSourceFile(QDir::currentPath()+"/../OpenGLComputeExample/example.fs");

    m_computeProgram = new QOpenGLShaderProgram();
    m_computeProgram->addShader(m_computeShader);
    m_computeProgram->link();
    m_computeProgram->bind();

    m_renderProgram = new QOpenGLShaderProgram();
    m_renderProgram->addShader(m_vertexShader);
    m_renderProgram->addShader(m_fragmentShader);
    m_renderProgram->link();
    m_renderProgram->bind();

    GLint posPtr = glGetAttribLocation(m_renderProgram->programId(), "pos");
    glVertexAttribPointer(posPtr, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posPtr);

    m_vao.release();
}

void MyGLWidget::paintGL()
{
    static GLint srcLoc= glGetUniformLocation(m_renderProgram->programId(),"srcTex");
    static GLint destLoc=glGetUniformLocation(m_computeProgram->programId(),"destTex");
    static GLint rollLoc=glGetUniformLocation(m_computeProgram->programId(),"roll");

//    qDebug() << srcLoc;
//    qDebug() << destLoc;
//    qDebug() << rollLoc;
//    qDebug() << roll;

    // compute
    m_vao.bind();

    m_computeProgram->bind();
    m_texture->bind();
    glUniform1i(destLoc,0);
    glUniform1f(rollLoc,roll);
    roll+=0.15;
    glDispatchCompute(m_texture->width()/16,m_texture->height()/16,1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    // draw
    m_renderProgram->bind();
    //glClear(GL_COLOR_BUFFER_BIT);
    m_texture->bind();
    glUniform1i(srcLoc,0);
    glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_SHORT,0);

    m_vao.release();
}

void MyGLWidget::resizeGL(int width, int height)
{
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(0, 1, 0, 1, 0, 1);
//    glMatrixMode(GL_MODELVIEW);
}

