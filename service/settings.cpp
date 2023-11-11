#include "settings.h"


Settings& getInstance(){
    static Settings instance;

    return instance;
}


Settings::Settings()
{

}
