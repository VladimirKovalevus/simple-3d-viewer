#include "entity.h"


void Entity::Draw(){
    for(auto it:m_children){
        it->Draw();
    }
}
void Entity::addChildren(Entity* e){
    m_children.push_back(e);
}
void Entity::removeChildren(int pos){
    auto to_del= m_children.begin()+pos;
    delete m_children[pos];
    m_children.erase(to_del);
}
