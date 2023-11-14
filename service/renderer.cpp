#include "renderer.h"




void Renderer::Draw(Entity* entity,Style s){
    switch (s) {
    case dot:{
        break;
    }
    case wire:
    {
        break;

    }
    case solid:{

        break;
    }
    }
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(colorLoc, (float)settings->color_vertex[0]/255.f,
                (float)settings->color_vertex[1]/255.f,(float)settings->color_vertex[2]/255.f);
    glPointSize(settings->size_vertex);
    entity->Draw();
    switch (s) {
    case dot:{
        break;
    }
    case wire:
    {
        break;

    }
    case solid:{

        break;
    }
    }
}
