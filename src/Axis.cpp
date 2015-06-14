/*
 * Axis.cpp
 *
 *  Created on: Jun 13, 2015
 *      Author: domahony
 */

#include <memory>
#include "types.h"
#include "Axis.h"
#include "ShaderBase.h"

namespace app {
namespace gl {

static const GLchar* getVS() {
	return R"(#version 150 core
    in vec3 position;
    //uniform mat4 model;
    //uniform mat4 view;
    //uniform mat4 proj;
    void main() {
       //gl_Position = proj * view * model * vec4(position, 1.0);
       gl_Position = vec4(position, 1.0);
    }
)";
}

static const GLchar* getFS() {
	return R"(#version 150 core
    out vec4 outColor;
    void main() {
       outColor = vec4(1.0,1.0,1.0,1.0);
    };
)";

}

class AxisShader : public ShaderBase
{
public:
	AxisShader() : ShaderBase(getVS(), getFS())
	{ }

};

static GLuint
initVAO(std::shared_ptr<app::gl::ShaderBase> shader)
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
Axis() : shader(new AxisShader), vao(initVAO(shader))
{

}

void Axis::
render() const
{
	shader->enable();
	shader->enableVertexAttribs();
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, 2);
	glDrawArrays(GL_LINES, 2, 2);
	glDrawArrays(GL_LINES, 4, 2);
	glBindVertexArray(0);
}

} /* namespace gl */
} /* namespace app */
