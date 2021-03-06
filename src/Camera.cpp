/*
 * Camera.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: domahony
 */

#include "Camera.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>

namespace app {

Camera::Camera():
		rota_angle(9.0f),
		eye(-1.0f, 15.5f, 35.0f),
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

glm::quat
rotate(const glm::quat& q, const float& a, const glm::vec3& axis)
{
	auto angle = a / glm::vec3::value_type(2);
	auto c = std::cos(glm::radians(angle));
	auto s = std::sin(glm::radians(angle));

	glm::quat rotation(c, s * axis);
	return glm::normalize(rotation * q);
}

glm::vec3
rotate(const glm::vec3& v, const float& angle, const glm::vec3& axis)
{
	return glm::normalize(glm::mat3(glm::rotate(glm::mat4(1), angle, axis)) * v);
	//return v;
}

void Camera::
left() {
	//orientation = rotate(orientation, -1.f * rota_angle, glm::vec3(0,1.f,0));
	orientation = rotate(orientation, -1.f * rota_angle, _j);

	glm::mat3 m = glm::mat3_cast(orientation);
	_i = glm::normalize(glm::column(m, 0));
	_k = glm::cross(_i, _j);
}

void Camera::
right() {
	//orientation = rotate(orientation, rota_angle, glm::vec3(0,1.0,0));
	orientation = rotate(orientation, 1.f * rota_angle, _j);
	glm::mat3 m = glm::mat3_cast(orientation);
	_i = glm::normalize(glm::column(m, 0));
	_k = glm::cross(_i, _j);
}

void Camera::
up() {
	orientation = rotate(orientation, -1.f * rota_angle, glm::vec3(1.f, 0, 0));
	glm::mat3 m = glm::mat3_cast(orientation);
	_j = glm::normalize(glm::column(m, 1));
	_k = glm::cross(_i, _j);
}

void Camera::
down() {
	orientation = rotate(orientation, rota_angle, glm::vec3(1.f, 0, 0));
	glm::mat3 m = glm::mat3_cast(orientation);
	_j = glm::normalize(glm::column(m, 1));
	_k = glm::cross(_i, _j);
}

void Camera::
forward() {
	glm::vec4 e(getMatrix() * glm::vec4(eye, 1));
	e += glm::vec4(0,0,-1,0);
	eye = glm::vec3(glm::inverse(getMatrix()) * e);
}

void Camera::
backward() {
	glm::vec4 e(getMatrix() * glm::vec4(eye, 1));
	e += glm::vec4(0,0,1,0);
	eye = glm::vec3(glm::inverse(getMatrix()) * e);
}

} /* namespace app */
