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

    void Draw(Entity* e,Style s);


};

#endif // RENDERER_H
