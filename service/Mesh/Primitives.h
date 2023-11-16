#ifndef PRIMITIVES_H
#define PRIMITIVES_H

struct Vec3{
    Vec3(){
        x=0;
        y=0;
        z=0;
    }
    Vec3(float _x,float _y,float _z){
        x=_x;
        y=_y;
        z=_z;
    }
    float x;
    float y;
    float z;
};
struct Vec2{
    Vec2(){
        x=0;
        y=0;
    }
    Vec2(float _x,float _y){
        x=_x;
        y=_y;
    }
    float x;
    float y;
};

struct Vertex{
    Vec3 position;
    Vec3 normal;
    Vec2 tex_coord;
};


#endif // PRIMITIVES_H
