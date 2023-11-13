#ifndef LIGHT_H
#define LIGHT_H
#include"entity.h"

struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};


class Light: public Entity
{
public:
    Light();
protected:
    Color color;
};

#endif // LIGHT_H
