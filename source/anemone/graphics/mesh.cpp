#include "mesh.hpp"

Mesh::Mesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices)
{
	this->vertices = vertices;
	this->indices = indices;

    SetupMesh();
}

void Mesh::Draw(std::shared_ptr<Shader> shader)
{
    vao.Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    vao.Unbind();
}

void Mesh::SetupMesh()
{
	vao.CreateVAO();
    vao.Bind();

    vbo.CreateVBO(vertices);
    vbo.Bind();

    ebo.CreateEBO(indices);
    ebo.Bind();

    vao.LinkVBO(vbo, 5, 0, 0);
    vao.LinkVBO(vbo, 5, 1, 3);

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();
}
