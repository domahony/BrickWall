/*
 * Camera.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: domahony
 */

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace app {

Camera::Camera():matrix(glm::lookAt(
		glm::vec3(-1.0f, 0.5f, 10.f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)))
{

}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

} /* namespace app */
