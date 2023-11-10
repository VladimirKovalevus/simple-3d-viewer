#ifndef TRANSFORMMATRIX4X4_H
#define TRANSFORMMATRIX4X4_H

#include "matrix/matrix.hpp"

struct Vec3{
    float x;
    float y;
    float z;
};



class TransformMatrix4x4 {

public:
    TransformMatrix4x4();


    void setRotation(float x,float y,float z);
    void setTranslation(float x ,float y,float z);
    void setScale(float x ,float y,float z);
    
    const Matrix matrix();

private:
    Vec3 rotation;
    Vec3 scale;
    Vec3 translation;

};

#endif // TRANSFORMMATRIX4X4_H
