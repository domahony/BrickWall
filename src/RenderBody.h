/*
 * RenderBody.h
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#ifndef RENDERBODY_H_
#define RENDERBODY_H_

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <iostream>
#include <bullet/LinearMath/btMotionState.h>
#include <glm/glm.hpp>

namespace app {

class RenderBody: public btMotionState {
public:
	RenderBody();
	virtual ~RenderBody();

	void getWorldTransform(btTransform& trans) const {
		trans = transform;
	}

	void setWorldTransform(const btTransform& trans) {
		transform = trans;
		std::cout << transform.getOrigin().getX() << ", " << transform.getOrigin().getY() << std::endl;
	}

	void render(glm::mat4& view, glm::mat4& proj);
private:
	btTransform transform;
	GLuint shader;
	GLuint vao;
};

} /* namespace app */

#endif /* RENDERBODY_H_ */
