#ifndef LIGHT_H
#define LIGHT_H
#include"entity.h"

struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};


class Light
{
public:
    Light(Color color={1,1,1},Vec3 _dir={0,1,0});

    void setDirection(Vec3 dir);
    void setColor(Color color);
    Vec3 getDirection()const;
    Color getColor()const;

private:
    Vec3 _dir;
    Color _color;
};

#endif // LIGHT_H
