#ifndef MESH_H
#define MESH_H

#include<vector>

#include "Primitives.h"
#include "../transformmatrix4x4.h"
#include "../Scene/entity.h"
#include <QtOpenGL/QOpenGLFunctions_3_3_Core>



class Mesh: public Entity , public QOpenGLFunctions_3_3_Core
{
public:
    Mesh(std::vector<Vertex> verticies,std::vector<unsigned int> indicies);
    void Draw();
    ~Mesh();
private:
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indicies;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

};

#endif // MESH_H
