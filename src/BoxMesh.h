/*
 * RenderBody.h
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#ifndef BOXMESH_H_
#define BOXMESH_H_

#include "types.h"
#include <iostream>
#include <bullet/LinearMath/btMotionState.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include <vector>

namespace app {

class BoxMesh {
public:
	BoxMesh();
	virtual ~BoxMesh();

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
	GLuint shader;
	GLuint vao;
	GLenum mode;
	GLint first_idx;
	GLsizei count;

};

} /* namespace app */

#endif /* BOXMESH_H_ */
