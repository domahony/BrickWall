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
#include <memory>
#include "Shader.h"

namespace app {
namespace gl {

class Mesh {
public:
	Mesh(
			std::shared_ptr<Shader> shader,
			const GLuint& vao,
			const GLenum& mode,
			const GLint& first_idx,
			const GLsizei& count):
		shader(shader),
		vertex_attrib_idx(vertex_attrib_idx),
		shader(shader),
		vao(vao),
		mode(mode),
		first_idx(first_idx),
		count(count)
	{

	}

	~Mesh() {
		// TODO Auto-generated destructor stub
	}

	GLuint getShader() const {
		return shader->getShader();
	}

	GLuint getVAO() const {
		return vao;
	}

	GLuint getShaderUniform(const std::string& str) const {
		return shader->getUniform(str);
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
	std::shared_ptr<app::gl::Shader> shader;
	std::map<std::string, GLuint> uniform;
	std::vector<GLuint> vertex_attrib_idx;

	GLuint vao;
	GLenum mode;
	GLint first_idx;
	GLsizei count;

};

} /* namespace gl */
} /* namespace app */

#endif /* MESH_H_ */
