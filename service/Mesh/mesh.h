#ifndef MESH_H
#define MESH_H

#include<vector>

#include "Primitives.h"
#include "../transformmatrix4x4.h"





class Mesh
{
public:
    Mesh();
private:
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indicies;
    TransformMatrix4x4 transformation;
};

#endif // MESH_H
