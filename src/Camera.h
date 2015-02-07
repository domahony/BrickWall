/*
 * Camera.h
 *
 *  Created on: Jan 13, 2015
 *      Author: domahony
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

namespace app {

class Camera {
public:
	Camera();
	virtual ~Camera();

	glm::mat4 getMatrix() const {
		return matrix;
	}

	glm::vec3 getViewPos() const {
		return eye;
	}

private:
	glm::vec3 eye;
	glm::mat4 matrix;

};

} /* namespace app */

#endif /* CAMERA_H_ */
