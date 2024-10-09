#pragma once

#include <GL/glew.h>
#include <vector>

class EBO
{
public:
    GLuint ID;
    EBO();
    void CreateEBO(const std::vector<GLuint>& indices);
    void Bind();
    void Unbind();
    void Delete();

};