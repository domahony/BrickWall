/*
 * Renderer.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: domahony
 */

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

namespace app {
namespace gl {

Renderer::Renderer() :
		view(glm::lookAt(
				glm::vec3(0.0f, -5.0f, 2.f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f))),
		proj(glm::perspective(45.0f, 800.0f / 600.0f, 1.0f, 100.0f))
{

}

void Renderer::
render(GroundGL& ground)
{
	ground.render(view, proj);
}

void Renderer::
render(Body* body)
{
	body->render(view, proj);
}

void Renderer::
render(const app::RenderBody& b)
{

	GLuint shader = b.getShader();

	glUseProgram(shader);

	GLuint uniModel = b.getShaderUniform("model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(b.getMode()));

	GLuint uniView = b.getShaderUniform("view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(camera.getView()));

	GLuint unitProj = b.getShaderUniform("proj");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(viewPort.getProj()));

	GLuint vao = b.getVAO();
	glBindVertexArray(vao);

	std::vector<GLuint> idx = b.getVertexAttribIdx();
	for (auto i: idx.begin()) {
		glEnableVertexAttribArray(i);
	}

	GLenum mode = b.getMode();
	GLint first = b.getFirstIdx();
	GLsizei count = b.getCount();

	glDrawArrays(mode, first, count);

	glUseProgram(0);
	glBindVertexArray(0);

}

Renderer::~Renderer() {

}

} /* namespace gl */
} /* namespace app */
