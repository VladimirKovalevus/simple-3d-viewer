#ifndef OPENGLCORE_H
#define OPENGLCORE_H

#include <QObject>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>

class OpenGLCore : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit OpenGLCore(QWidget *parent = nullptr);



private:

    void cleanUp();
    void initShaders();
    void drawLines();
    void drawPoints();


    unsigned int VAO=0;
    unsigned int VBO=0;
    unsigned int EBO=0;
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
