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
#include <glm/gtc/constants.hpp>

namespace app {

Camera::Camera():
		eye(9.0f, 32.0f, -9.0f),
		center(0.f, 0.f, 0.f),
		upv(0.f, 1.f, 0.f),
	_k(-1.f * glm::normalize(center - eye)),
	_i(glm::normalize(glm::cross(glm::normalize(upv), _k))),
	_j(glm::normalize(glm::cross(_k, _i)))
{
	orientation = glm::quat_cast(glm::mat3(_i, _j, _k));
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::
left() {
	glm::quat rotation(1.f * glm::pi<float>() / 360.0f, _j);
	orientation = glm::normalize(rotation * orientation);
}

void Camera::
right() {
	glm::quat rotation(-1.f * glm::pi<float>() / 360.0f, _j);
	orientation = glm::normalize(rotation * orientation);
}

void Camera::
up() {
	glm::quat rotation(-1.f * glm::pi<float>() / 360.0f, _i);
	orientation = glm::normalize(rotation * orientation);
}

void Camera::
down() {
	glm::quat rotation(1.f * glm::pi<float>() / 360.0f, _i);
	orientation = glm::normalize(rotation * orientation);
}

} /* namespace app */
