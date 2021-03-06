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
#include "ShaderBase.h"
#include "Camera.h"
#include "ViewPort.h"

namespace app {
namespace gl {

class Mesh {
public:
	Mesh(
			std::shared_ptr<ShaderBase> shader,
			const GLuint& vao,
			const GLenum& mode,
			const GLint& first_idx,
			const GLsizei& count):
		shader(shader),
		vao(vao),
		mode(mode),
		first_idx(first_idx),
		count(count),
		local(btTransform::getIdentity())
	{

	}

	~Mesh() {
		// TODO Auto-generated destructor stub
	}


	void render(const app::CameraPtr& c, const app::ViewPort& vp, const btTransform& transform) const;

private:
	std::shared_ptr<app::gl::ShaderBase> shader;

	GLuint vao;
	GLenum mode;
	GLint first_idx;
	GLsizei count;
	btTransform local;

};

} /* namespace gl */
} /* namespace app */

#endif /* MESH_H_ */
