#include "renderer.h"




void Renderer::Draw(Entity* entity){
    
    unsigned int colorLoc = glGetUniformLocation(shaderProgram, "color");
    glUniform3f(colorLoc, (float)settings->color_vertex[0]/255.f,
                (float)settings->color_vertex[1]/255.f,(float)settings->color_vertex[2]/255.f);
    glPointSize(settings->size_vertex);
    entity->Draw();

}
