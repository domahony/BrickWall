/*
 * Axis.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: domahony
 */

#include "types.h"
#include "Axis.h"

namespace app {
namespace gl {

static GLuint
initVAO(std::shared_ptr<app::gl::Shader> shader)
{
	GLfloat vertices[] = {
		-0.5f, 0, 0,
		0.5f, 0, 0,
		0, -0.5f, 0,
		0, 0.5f, 0,
		0, 0, -0.5f,
		0, 0, 0.5f,
	};

	GLuint vbo;

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shader->getShader(), "position");

    GLuint vao;

    // Create and bind Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

Axis::
Axis() : vao(initVAO(0))
{

}

void Axis::
render()
{
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);
}

} /* namespace gl */
} /* namespace app */
