#ifndef __SCENE__
#define __SCENE__
#include <vector>
#include "light.h"
#include "entity.h"

class Scene{

    void addToRoot(Entity* e);
    void addToNode(Entity* parent, Entity* e);
    void removeEntity(Entity* e);
    void addLightSource(Light ls);
    void removeLightSource(size_t pos);
    Entity getRoot();    
private:
Entity root;
std::vector<Light> light_sources;
std::vector<Entity*> entities;

};

#endif