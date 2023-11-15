#include "mesh.h"
#include "Primitives.h"
#include <cstddef>

Mesh::Mesh(std::vector<Vertex> _verticies,std::vector<unsigned int> _indicies)
{
    verticies = _verticies;
    indicies = _indicies;
    initializeOpenGLFunctions();

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _verticies.size()*sizeof(Vertex), _verticies.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicies.size()*sizeof(unsigned int), _indicies.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), offsetof(Vertex,position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3), offsetof(Vertex,normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vec2), offsetof(Vertex, tex_coord));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}   


void Mesh::Draw(){
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicies.size(),GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
}

Mesh::~Mesh(){

 glDeleteBuffers(1,&VBO);
 glDeleteBuffers(1,&EBO);
 glDeleteVertexArrays(1,&VAO);

}