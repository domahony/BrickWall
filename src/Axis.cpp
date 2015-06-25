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
#include "glm/gtc/type_ptr.hpp"

namespace app {
namespace gl {

static const GLchar* getVS() {
	return R"(#version 150 core
    in vec3 position;
    uniform mat4 view;
    void main() {
       //gl_Position = vec4(mat3(view) * position, 1.0);
       gl_Position = view * vec4(position, 1.0);
    }
)";
}

static const GLchar* getFS() {
	return R"(#version 150 core
    uniform vec3 color;
    out vec4 outColor;
    void main() {
       outColor = vec4(color, 1.0);
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
		0.5f, 0, 0,
		-0.5f, 0, 0,
		0, 0.5f, 0,
		0, -0.5f, 0,
		0, 0, 0.5f,
		0, 0, -0.5f,

		//0, 0, -0.5f,
		//0.2, 0, -0.2,
		//-0.2, 0, -0.2,

		0, 0, 0.5f,
		0.2, 0, 0.2,
		-0.2, 0, 0.2,

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
    //glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

Axis::
Axis() : shader(new AxisShader), vao(initVAO(shader))
{

}

void Axis::
render(const app::CameraPtr camera) const
{

	glm::mat4 s(glm::scale(glm::mat4(1.f), glm::vec3(0.2f)));
	glm::mat4 t(glm::translate(glm::mat4(1.f), glm::vec3(-0.8f, -0.8f, 0.f)));

	glm::mat4 m1(glm::mat3(camera->getOrientation()));
	glm::mat4 m2(glm::lookAt(camera->getViewPos(), glm::vec3(0), glm::vec3(0, 1.f, 0)));

	//m1 = t * s * glm::inverse(m1); //glm::mat4(glm::mat3(m2));
	//m1 = t * s * glm::mat4(glm::mat3(m2)) * m1;

	m1 = glm::mat4(glm::mat3(m2)) * glm::inverse(m1);

	glBindVertexArray(vao);
	shader->enable();
	shader->enableVertexAttribs();
	//shader->setCameraMatrix(glm::value_ptr(glm::mat4(camera->getOrientation())));
	shader->setCameraMatrix(glm::value_ptr(m1));
	shader->setUniform("color", glm::vec3(1.f, 0, 0));
	glDrawArrays(GL_LINES, 0, 2);
	shader->setUniform("color", glm::vec3(0, 1.f, 0));
	glDrawArrays(GL_LINES, 2, 2);
	shader->setUniform("color", glm::vec3(0, 0, 1.f));
	glDrawArrays(GL_LINES, 4, 2);
	shader->setUniform("color", glm::vec3(1.f, 1.f, 1.f));
	glDrawArrays(GL_TRIANGLES, 6, 3);
	glBindVertexArray(0);
	glUseProgram(0);
}

} /* namespace gl */
} /* namespace app */
