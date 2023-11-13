#ifndef ENTITY_H
#define ENTITY_H
#include"../transformmatrix4x4.h"
#include<vector>
#include<memory>



class Entity
{
public:
    virtual void addChildren(Entity* e)=0;
protected:
    TransformMatrix4x4 m_transform;
    std::vector<Entity*> m_children;
    Entity* m_parent;
};

#endif // ENTITY_H
