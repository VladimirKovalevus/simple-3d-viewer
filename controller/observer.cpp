#include "observer.hpp"

Observer::Observer(){

}
void Observer::addSlave(Observable* slave){
    _slaves.push_back(slave);
}

void Observer::update(){
    for(auto& it : _slaves){
        it->makeCurrent();
        it->update();
    }
}

