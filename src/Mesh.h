/*
 * Mesh.h
 *
 *  Created on: Jan 26, 2015
 *      Author: domahony
 */

#ifndef MESH_H_
#define MESH_H_

/*
#include <string>
*/

#include "types.h"
#include <bullet/LinearMath/btMotionState.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include "Shader.h"
#include "Camera.h"
#include "ViewPort.h"

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
		vao(vao),
		mode(mode),
		first_idx(first_idx),
		count(count)
	{

	}

	~Mesh() {
		// TODO Auto-generated destructor stub
	}


	void render(const app::Camera& c, const app::ViewPort& vp, const btTransform& transform) const;

private:
	std::shared_ptr<app::gl::Shader> shader;

	GLuint vao;
	GLenum mode;
	GLint first_idx;
	GLsizei count;

};

} /* namespace gl */
} /* namespace app */

#endif /* MESH_H_ */
