#include "openglcore.h"
#include <iostream>
#include"settings.h"
OpenGLCore::OpenGLCore(QWidget *parent)
    : QOpenGLWidget{parent}
{

}

void OpenGLCore::initShaders(){
    int success=0;
    char infoLog[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(1);
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(1);
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << infoLog;
        exit(1);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void OpenGLCore::drawPoints(){

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    if(Settings::getSettings().getVertexType()==circle){
        glEnable(GL_POINT_SMOOTH);
    }else{
        glEnable(GL_POINT_SPRITE);
    }
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    Vec3 vertex_color= Settings::getSettings().getVertexColor();
    glUniform3f(colorLoc, vertex_color.x,
                vertex_color.y,vertex_color.z);
    glPointSize(Settings::getSettings().getVertexSize());
    scene->Draw();
    if(Settings::getSettings().getVertexType()==circle){
        glDisable(GL_POINT_SMOOTH);
    }else{
        glDisable(GL_POINT_SPRITE);
    }
}
void OpenGLCore::paintGL()
{
    Vec3 bg_color= Settings::getSettings().getBackgroundColor();
    glClearColor(bg_color.x,bg_color.y,bg_color.z, 1.f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (this->scene!=nullptr)
    {
        glEnable(GL_DEPTH_TEST);
        glUseProgram(shaderProgram);
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        ///////AAALEEERT//////

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, nullptr);
        transformLoc = glGetUniformLocation(shaderProgram,"projection");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE,nullptr);
        transformLoc = glGetUniformLocation(shaderProgram,"view");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, nullptr);

        if(Settings::getSettings().getVertexType()!=none){
            drawPoints();
        }
        drawLines();
        update();
    }
}
void OpenGLCore::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLCore::initializeGL()
{
    initializeOpenGLFunctions();
    Vec3 bg_color= Settings::getSettings().getBackgroundColor();
    glClearColor(bg_color.x,bg_color.y,bg_color.z, 1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    initShaders();
}

void OpenGLCore::drawLines(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if(Settings::getSettings().getLineType()==dotted){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2,0x00ff);
    }

    glLineWidth(Settings::getSettings().getLineSize());
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    Vec3 line_color= Settings::getSettings().getVertexColor();
    glUniform3f(colorLoc, line_color.x,
                line_color.y,line_color.z);
    scene->Draw();
    if(Settings::getSettings().getLineType()==dotted){
        glDisable(GL_LINE_STIPPLE);
    }
}
