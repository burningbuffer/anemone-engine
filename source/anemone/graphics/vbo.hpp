#pragma once
#include <GL/glew.h>
#include <vector>
class VBO 
{
public:
    unsigned int ID;
    VBO();
    void CreateVBO(const std::vector<float>& vertices);
    void Bind();
    void Unbind();
    void Delete();
};