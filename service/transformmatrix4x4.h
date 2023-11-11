#ifndef TRANSFORMMATRIX4X4_H
#define TRANSFORMMATRIX4X4_H

#include "matrix/matrix.hpp"

#include "Mesh/Primitives.h"


class TransformMatrix4x4 {

public:
    TransformMatrix4x4();


    void setRotation(float x,float y,float z);
    void setTranslation(float x ,float y,float z);
    void setScale(float x ,float y,float z);
    
    const float *data();

private:

    Matrix apply_matrix();
    Matrix m_matrix;
    Vec3 rotation;
    Vec3 scale;
    Vec3 translation;

};

#endif // TRANSFORMMATRIX4X4_H
