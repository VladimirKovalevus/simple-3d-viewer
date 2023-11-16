#ifndef ENTITY_H
#define ENTITY_H
#include"../transformmatrix4x4.h"
#include<vector>
#include<memory>



class Entity
{
public:
    virtual void Draw();
    virtual void addChildren(Entity* e);
    virtual void removeChildren(int pos);

protected:
    TransformMatrix4x4 m_transform;
    std::vector<Entity*> m_children;
};

#endif // ENTITY_H
