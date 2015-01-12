/*
 * Renderer.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: domahony
 */

#include "Renderer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

Renderer::~Renderer() {

}

} /* namespace gl */
} /* namespace app */
