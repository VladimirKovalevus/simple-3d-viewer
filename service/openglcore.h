#ifndef OPENGLCORE_H
#define OPENGLCORE_H

#include <QObject>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>
#include "Scene/entity.h"
#include "../controller/observer.hpp"
class OpenGLCore : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core,public Observable
{
    Q_OBJECT
public:
    explicit OpenGLCore(QWidget *parent = nullptr);


protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    void initShaders();
    void drawLines();
    void drawPoints();

    Entity *scene;

    unsigned int vertexShader=0;
    unsigned int fragmentShader=0;
    unsigned int shaderProgram=0;


    const char* vertexShaderSource =R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;


uniform vec3 color;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;


void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1.0f);
    vertexColor = vec4(color, 1.0);
})";
    const char* fragmentShaderSource =R"(
#version 330 core
out vec4 FragColor;
in vec4 vertexColor;

void main()
{
    FragColor = vertexColor;
})";

};

#endif // OPENGLCORE_H
