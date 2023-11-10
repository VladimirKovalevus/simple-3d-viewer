#include "transformmatrix4x4.h"
#include <cmath>
#include<math.h>
TransformMatrix4x4::TransformMatrix4x4()
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

}

void TransformMatrix4x4::setTranslation(float x,float y,float z){
    translation.x=x;
    translation.y=y;
    translation.z=z;
}


void TransformMatrix4x4::setScale(float x,float y,float z){
    scale.x=x;
    scale.y=y;
    scale.z=z;   
}
const Matrix TransformMatrix4x4::data(){
    Matrix a(4,4);

    for(int i  =0; i<a.getRows();i++){
        a(i,i) = 1;
    }
    /////////////////////////
    //    Translation      //
    /////////////////////////
    
    a(3,0) = translation.x;
    a(3,1) = translation.y;
    a(3,2) = translation.z;

    /////////////////////////
    //        Scale        //
    /////////////////////////

    a(0,0) = scale.x;
    a(1,1) = scale.y;
    a(2,2) = scale.z;

    /////////////////////////
    //      Rotation       //
    /////////////////////////

    a(0,0) *= cos(rotation.y)*cos(rotation.z);
    a(0,1) *= cos(rotation.y)*cos(rotation.z);
    a(0,2) *= -sin(rotation.y);


    a(1,0) *= sin(rotation.x)*sin(rotation.y)*sin(rotation.z)
            - cos(rotation.x)*cos(rotation.z);
    
    a(1,1) *= sin(rotation.x)*sin(rotation.y)*sin(rotation.z)
            + cos(rotation.x)*cos(rotation.z);

    a(1,2) *= cos(rotation.y)*sin(rotation.z);

    a(2,0) *= cos(rotation.x)*sin(rotation.y)*cos(rotation.z)
            + sin(rotation.x)*sin(rotation.z);

    a(2,1) *= sin(rotation.x)*sin(rotation.y)*cos(rotation.z)
            - cos(rotation.x)*sin(rotation.z);

    a(2,2) *= cos(rotation.y)*cos(rotation.z);

    return a;
    
}
