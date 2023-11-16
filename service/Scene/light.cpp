#include "light.h"

Light::Light(Color color,Vec3 dir)
{
    _color = color;
    _dir   = dir;
}

void Light::setDirection(Vec3 dir){
    _dir = dir;
}
void Light::setColor(Color color){
    _color = color;
}
Vec3  Light::getDirection() const{
    return _dir;
}
Color Light::getColor() const{
    return _color;
}

