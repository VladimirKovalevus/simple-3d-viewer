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

void OpenGLCore::initModel(QString path)
{
    makeCurrent();
    cleanUp();

//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, model->vertex_array.vertex_length*sizeof(vertex_t), model->vertex_array.vertex, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->index_array.facet_length*4, model->index_array.facet, GL_STATIC_DRAW);

//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

//    glBindVertexArray(0);
    doneCurrent();
}

void OpenGLCore::drawPoints(){

    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    if(settings->type_vertex==circle){
        glEnable(GL_POINT_SMOOTH);
    }else{
        glEnable(GL_POINT_SPRITE);
    }
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(colorLoc, (float)settings->color_vertex[0]/255.f,
                (float)settings->color_vertex[1]/255.f,(float)settings->color_vertex[2]/255.f);
    glBindVertexArray(VAO);
    glPointSize(settings->size_vertex);
    glDrawElements(GL_POINTS, model->index_array.facet_length,GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
    if(settings->type_vertex==circle){
        glDisable(GL_POINT_SMOOTH);
    }else{
        glDisable(GL_POINT_SPRITE);
    }
}
void OpenGLCore::paintGL()
{
    glClearColor((float)settings->color_background[0]/255.f
                 ,(float)settings->color_background[1]/255.f
                 ,(float)settings->color_background[2]/255.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (this->VAO!=0)
    {
        glEnable(GL_DEPTH_TEST);
        glUseProgram(shaderProgram);
        transforming();
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, transform.data());
        transformLoc = glGetUniformLocation(shaderProgram,"projection");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, projection.data());
        transformLoc = glGetUniformLocation(shaderProgram,"view");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, camera.data());

        if(settings->type_vertex!=none){
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
    glClearColor((float)settings->color_background[0]/255.f
                 ,(float)settings->color_background[1]/255.f
                 ,(float)settings->color_background[2]/255.f, 1.f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
}

void OpenGLCore::drawLines(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if(settings->type_line==dotted){
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2,0x00ff);
    }

    glLineWidth(settings->size_line);
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(colorLoc, (float)settings->color_line[0]/255.f,
                (float)settings->color_line[1]/255.f,(float)settings->color_line[2]/255.f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, model->index_array.facet_length,GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
    if(settings->type_line==dotted){
        glDisable(GL_LINE_STIPPLE);
    }
}
