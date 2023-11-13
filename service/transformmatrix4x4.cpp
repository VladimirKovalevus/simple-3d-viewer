#include "transformmatrix4x4.h"
#include <cmath>
#include<math.h>
TransformMatrix4x4::TransformMatrix4x4(): m_matrix{4,4}
{
    rotation.x = 0;
    rotation.y = 0;
    rotation.z = 0;

    translation.x = 0;
    translation.y = 0;
    translation.z = 0;

    scale.x = 1;
    scale.y = 1;
    scale.z = 1;
}

void TransformMatrix4x4::setRotation(float x,float y,float z){
    rotation.x=x;
    rotation.y=y;
    rotation.z=z;

    m_matrix =apply_matrix();
}

void TransformMatrix4x4::setTranslation(float x,float y,float z){
    translation.x=x;
    translation.y=y;
    translation.z=z;

    m_matrix =apply_matrix();
}


void TransformMatrix4x4::setScale(float x,float y,float z){
    scale.x=x;
    scale.y=y;
    scale.z=z;
    m_matrix =apply_matrix();
}




Matrix TransformMatrix4x4::apply_matrix()
{
    Matrix _translate(4,4),_rotate(4,4),_scale(4,4);

    for(int i  =0; i<4;i++){
        _translate(i,i) = 1;
        _rotate(i,i) = 1;
        _scale(i,i)=1;
    }
    /////////////////////////
    //    Translation      //
    /////////////////////////

    _translate(3,0) = translation.x;
    _translate(3,1) = translation.y;
    _translate(3,2) = translation.z;

    /////////////////////////
    //        Scale        //
    /////////////////////////

    _scale(0,0) = scale.x;
    _scale(1,1) = scale.y;
    _scale(2,2) = scale.z;

    /////////////////////////
    //      Rotation       //
    /////////////////////////

    _rotate(0,0) = cos(rotation.y)*cos(rotation.z);
    _rotate(0,1) = cos(rotation.y)*cos(rotation.z);
    _rotate(0,2) = -sin(rotation.y);


    _rotate(1,0) = sin(rotation.x)*sin(rotation.y)*sin(rotation.z)
                    - cos(rotation.x)*cos(rotation.z);

    _rotate(1,1) = sin(rotation.x)*sin(rotation.y)*sin(rotation.z)
                    + cos(rotation.x)*cos(rotation.z);

    _rotate(1,2) = cos(rotation.y)*sin(rotation.z);

    _rotate(2,0) = cos(rotation.x)*sin(rotation.y)*cos(rotation.z)
                    + sin(rotation.x)*sin(rotation.z);

    _rotate(2,1) = sin(rotation.x)*sin(rotation.y)*cos(rotation.z)
                    - cos(rotation.x)*sin(rotation.z);

    _rotate(2,2) = cos(rotation.y)*cos(rotation.z);
    return _rotate*_translate*_scale;
}
float* TransformMatrix4x4::data(){
    return m_matrix.data();
    
}
