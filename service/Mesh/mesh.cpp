#include "mesh.h"

Mesh::Mesh()
{

}


void Mesh::Draw(){
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(colorLoc, (float)settings->color_vertex[0]/255.f,
                (float)settings->color_vertex[1]/255.f,(float)settings->color_vertex[2]/255.f);
    glBindVertexArray(VAO);
    glPointSize(settings->size_vertex);
    ///////////////////////////
    /// \brief glDrawElements//
    ///                      //
    /// ALEEEEEEEEEEEEEERT   //
    ///                      //
    ///                      //
    ///////////////////////////
    glDrawElements(GL_POINTS, nullptr,GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
}
