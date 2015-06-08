/*
 * Camera.h
 *
 *  Created on: Jan 13, 2015
 *      Author: domahony
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace app {

class Camera {
public:
	Camera();
	virtual ~Camera();

	glm::mat4 getMatrix() const {
		return glm::translate(orientation, eye * -1.f);
	}

	glm::vec3 getViewPos() const {
		return eye;
	}

	void left();
	void right();
	void up();
	void down();

private:
	glm::vec3 eye;
	glm::mat4 orientation;
	glm::mat4 matrix;
};

typedef std::shared_ptr<Camera> CameraPtr;

} /* namespace app */

#endif /* CAMERA_H_ */
