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
#include <map>
#include <string>
#include <vector>

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

	GLuint getShader() const {
		return shader;
	}

	GLuint getVAO() const {
		return vao;
	}

	GLuint getShaderUniform(const std::string& str) const {

		auto iter = uniform.find(str);

		if (iter == uniform.cend()) {
			return -1;
		} else {
			return iter->second;
		}
	}

	void render(glm::mat4& view, glm::mat4& proj);

	GLenum getMode() const {
		return mode;
	}

	GLint getFirstIdx() const {
		return first_idx;
	}

	GLsizei getCount() const {
		return count;
	}

	const std::vector<GLuint> getVertexAttribIdx() const {
			return vertex_attrib_idx;
	}

private:
	std::map<std::string, GLuint> uniform;
	std::vector<GLuint> vertex_attrib_idx;
	btTransform transform;
	GLuint shader;
	GLuint vao;
	GLenum mode;
	GLint first_idx;
	GLsizei count;
};

} /* namespace app */

#endif /* RENDERBODY_H_ */
