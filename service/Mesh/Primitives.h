#ifndef PRIMITIVES_H
#define PRIMITIVES_H

struct Vec3{
    float x;
    float y;
    float z;
};
struct Vec2{
    float x;
    float y;
};

struct Vertex{
    Vec3 position;
    Vec3 normal;
    Vec2 tex_coord;
};


#endif // PRIMITIVES_H
