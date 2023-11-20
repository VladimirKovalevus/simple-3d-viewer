#ifndef __CONTROLLER_OBSERVER__
#define __CONTROLLER_OBSERVER__
#include <vector>

#include "../service/openglcore.h"

class Observable{
    virtual void update()=0;
    virtual void makeCurrent()=0;
};


class Observer{
public:
    Observer();
    void addSlave(Observable* slave);
    void update();
private:
    std::vector< Observable* > _slaves;
};

#endif // __CONTROLLER_OBSERVER__