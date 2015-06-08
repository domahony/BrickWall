/*
 * Mesh.cpp
 *
 *  Created on: Jan 26, 2015
 *      Author: domahony
 */

#include "Mesh.h"

namespace app {
namespace gl {

void Mesh::
render(const app::CameraPtr& c, const app::ViewPort& vp, const btTransform& transform) const {

		shader->enable();
		glBindVertexArray(vao);

		btScalar scalar[16];
		transform.getOpenGLMatrix(scalar);

		glm::vec4 lightPosModel = glm::inverse(glm::make_mat4(scalar)) * glm::vec4(-7, 3, 9, 1);

#ifdef DOM_VERBOSE
		std::cout << "(" <<
				lightPosModel.x << ", " <<
				lightPosModel.y << ", " <<
				lightPosModel.z << ", " <<
				lightPosModel.w << ")" <<
				std::endl;
#endif

		shader->setLightPos(glm::value_ptr(lightPosModel));

		glm::vec4 viewPos = glm::vec4(c->getViewPos(), 1);
		glm::vec4 viewPosModel = glm::inverse(glm::make_mat4(scalar)) * viewPos;

#ifdef DOM_VERBOSE
		std::cout << "(" <<
				viewPosModel.x << ", " <<
				viewPosModel.y << ", " <<
				viewPosModel.z << ", " <<
				viewPosModel.w << ")" <<
				std::endl;
#endif

		shader->setViewPos(glm::value_ptr(viewPosModel));

		//std::exit(1);
		shader->setCameraMatrix(glm::value_ptr(c->getMatrix()));
		shader->setViewportMatrix(glm::value_ptr(vp.getProjMatrix()));
		shader->setModelMatrix(scalar);
		shader->enableVertexAttribs();

		glDrawArrays(mode, first_idx, count);

		glUseProgram(0);
		glBindVertexArray(0);
}

} /* namespace gl */
} /* namespace app */
