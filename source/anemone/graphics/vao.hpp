#pragma once

#include <GL/glew.h>
#include "vbo.hpp"

class VAO
{
public:
    GLuint ID;
    VAO();
    void CreateVAO();
    void LinkVBO(VBO& VBO, int lineSize, GLuint layout, int offset);
    void Bind();
    void Unbind();
    void Delete();

};