/*
 * Renderer.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: domahony
 */

#include "types.h"
#include "Renderer.h"
#include "Camera.h"
#include "ViewPort.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace app {
namespace gl {

Renderer::Renderer() :
		view(glm::lookAt(
				glm::vec3(0.0f, -5.0f, 2.f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f))),
		proj(glm::perspective(75.0f, 800.0f / 600.0f, 1.0f, 100.0f))
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
render(const app::ViewPort& vp, const app::Camera& camera, const app::RenderBody& b) const
{
	GLuint shader = b.getShader();

	glUseProgram(shader);

	GLuint vao = b.getVAO();
	glBindVertexArray(vao);

	GLuint uniModel = b.getShaderUniform("model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(b.getModelMatrix()));

	GLuint uniView = b.getShaderUniform("view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(camera.getMatrix()));

	GLuint uniProj = b.getShaderUniform("proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(vp.getProjMatrix()));

	std::vector<GLuint> idx = b.getVertexAttribIdx();
	for (auto i: idx) {
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
