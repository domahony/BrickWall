/*
 * Camera.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: domahony
 */

#include "Camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace app {

Camera::Camera():eye(9.0f, 32.0f, -9.0f),
		/*
		matrix(glm::lookAt(
		eye,
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)))
		*/
		orientation(glm::translate(
				glm::lookAt(
						eye,
						glm::vec3(0.0f, 0.0f, 0.0f),
						glm::vec3(0.0f, 1.0f, 0.0f)),
				eye * 1.f)),
		matrix(glm::translate(glm::mat4(orientation), eye * -1.f))
{

	//right();
	//right();
	//right();
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::
left() {
	glm::quat q(orientation);
	//glm::quat q2(.01f, glm::axis(q));
	//q = glm::normalize(q * q2);

	std::cout << "Axis: "
			<< glm::axis(q).x << ", "
			<< glm::axis(q).y << ", "
			<< glm::axis(q).z << std::endl;
	std::cout << "Angle: " << glm::angle(q) << std::endl;
	q = glm::normalize(glm::rotate(q, 1.f, glm::axis(q)));

	orientation = glm::mat3_cast(q);
}

void Camera::
right() {
	glm::quat q(orientation);
	//glm::quat q2(.01f, glm::axis(q));
	//q = glm::normalize(q * q2);
	std::cout << "Axis: "
			<< glm::axis(q).x << ", "
			<< glm::axis(q).y << ", "
			<< glm::axis(q).z << std::endl;

	std::cout << "Angle: " << glm::angle(q) << std::endl;
	q = glm::normalize(glm::rotate(q, -1.f, glm::axis(q)));

	orientation = glm::mat3_cast(q);
}

void Camera::
up() {
	glm::quat q(orientation);
	//q = glm::normalize(glm::rotate(q, -1.f, glm::axis(q)));
	q = glm::normalize(glm::rotate(q, -1.f, glm::vec3(0,0,1)));
	orientation = glm::mat3_cast(q);
}

void Camera::
down() {
	glm::quat q(orientation);
	//q = glm::normalize(glm::rotate(q, 1.f, glm::axis(q)));
	q = glm::normalize(glm::rotate(q, 1.f, glm::vec3(0,0,1)));
	orientation = glm::mat3_cast(q);
}

} /* namespace app */
