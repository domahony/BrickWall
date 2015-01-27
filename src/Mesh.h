/*
 * Mesh.h
 *
 *  Created on: Jan 26, 2015
 *      Author: domahony
 */

#ifndef MESH_H_
#define MESH_H_

/*
#include <bullet/LinearMath/btMotionState.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
*/
#include "types.h"
#include <map>
#include <vector>

namespace app {
namespace gl {

class Mesh {
public:
	Mesh() {
		// TODO Auto-generated constructor stub

	}
	~Mesh() {
		// TODO Auto-generated destructor stub
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

} /* namespace gl */
} /* namespace app */

#endif /* MESH_H_ */
