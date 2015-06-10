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
	_k(glm::normalize(eye - center)),
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
	float c = std::cos(0.5f * glm::pi<float>() / 180.0f);
	float s = std::sin(0.5f * glm::pi<float>() / 180.0f);
	glm::quat rotation(c, s * _k);
	orientation = glm::normalize(rotation * orientation);
}

void Camera::
right() {
	float c = std::cos(-0.5f * glm::pi<float>() / 180.0f);
	float s = std::sin(-0.5f * glm::pi<float>() / 180.0f);
	glm::quat rotation(c, s * _k);
	orientation = glm::normalize(rotation * orientation);
}

void Camera::
up() {
	float c = std::cos(-0.5f * glm::pi<glm::vec3::value_type>() / 180.0f);
	float s = std::sin(-0.5f * glm::pi<glm::vec3::value_type>() / 180.0f);
	glm::quat rotation(c, s * _j);
	orientation = glm::normalize(rotation * orientation);
	//_i = glm::pitch(orientation);
}

void Camera::
down() {
	float c = std::cos(0.5f * glm::pi<float>() / 180.0f);
	float s = std::sin(0.5f * glm::pi<float>() / 180.0f);
	glm::quat rotation(c, s * _j);
	orientation = glm::normalize(rotation * orientation);
	//_i = glm::pitch(orientation);
}

} /* namespace app */
