/*
 * RenderBody.h
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#ifndef RENDERBODY_H_
#define RENDERBODY_H_

#include "types.h"
#include <memory>
#include <iostream>
#include <bullet/LinearMath/btMotionState.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "BoxMesh.h"
#include <map>
#include <string>
#include <vector>

namespace app {

class RenderBody: public btMotionState {
public:
	RenderBody(const std::shared_ptr<app::BoxMesh> mesh, const btTransform& trans) : mesh(mesh), transform(trans) {

	}

	virtual ~RenderBody() {

	}

	void getWorldTransform(btTransform& trans) const {
		trans = transform;
	}

	void setWorldTransform(const btTransform& trans) {
		transform = trans;
		std::cout << "Yeah! " << transform.getOrigin().getX() << ", " << transform.getOrigin().getY() << std::endl;
	}

	GLuint getShader() const {
		return mesh->getShader();
	}

	GLuint getVAO() const {
		return mesh->getVAO();
	}

	GLuint getShaderUniform(const std::string& str) const {
		return mesh->getShaderUniform(str);
	}

	GLenum getMode() const {
		return mesh->getMode();
	}

	GLint getFirstIdx() const {
		return mesh->getFirstIdx();
	}

	GLsizei getCount() const {
		return mesh->getCount();
	}

	const std::vector<GLuint> getVertexAttribIdx() const {
		return mesh->getVertexAttribIdx();
	}

	glm::mat4 getModelMatrix() const {
		glm::mat4 ret;
		transform.getOpenGLMatrix(glm::value_ptr(ret));

		return ret;
	}

private:

	btTransform transform;
	std::shared_ptr<app::BoxMesh> mesh;

};

} /* namespace app */

#endif /* RENDERBODY_H_ */
