#ifndef ENTITY_H
#define ENTITY_H
#include"../transformmatrix4x4.h"
#include<vector>
#include<memory>


typedef std::unique_ptr<Entity> e_pointer;

class Entity
{
public:
    virtual void Draw()=0;
    virtual void addChildren(e_pointer e)=0;
    virtual void moveChildren(e_pointer oldParent,e_pointer newParent)=0;
protected:
    TransformMatrix4x4 m_transform;
    std::vector<e_pointer> m_children;
    e_pointer m_parent;
};

#endif // ENTITY_H
