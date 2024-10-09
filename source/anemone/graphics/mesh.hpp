#pragma once
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "vbo.hpp"
#include "vao.hpp"
#include "ebo.hpp"
#include "shader.hpp"

class Mesh
{
public:
    Mesh(const std::vector<float>& vertices, const std::vector<GLuint>& indices);
    void Draw(std::shared_ptr<Shader> shader);
private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;

    VAO vao;
    VBO vbo;
    EBO ebo;

    void SetupMesh();
    
};