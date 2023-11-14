#include "mesh.h"

Mesh::Mesh()
{

}


void Mesh::Draw(){
    glBindVertexArray(VAO);
    ///////////////////////////
    /// \brief glDrawElements//
    ///                      //
    /// ALEEEEEEEEEEEEEEEERT //
    ///                      //
    ///                      //
    ///////////////////////////
    glDrawElements(GL_TRIANGLES, nullptr,GL_UNSIGNED_INT,(void*)0);
    glBindVertexArray(0);
}
