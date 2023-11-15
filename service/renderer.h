#ifndef RENDERER_H
#define RENDERER_H
#include"Scene/entity.h"

enum Style{
    dot,
    wire,
    solid,
    count,

};

class Renderer
{
public:
    static void Draw(Entity* e);
};

#endif // RENDERER_H
