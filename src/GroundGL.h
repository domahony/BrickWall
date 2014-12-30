/*
 * GroundGL.h
 *
 *  Created on: Dec 30, 2014
 *      Author: domahony
 */

#ifndef GROUNDGL_H_
#define GROUNDGL_H_
#include <GL/gl.h>
#include <glm/glm.hpp>

namespace app {
namespace gl {

class GroundGL {
public:
	GroundGL();
	void render(glm::mat4&, glm::mat4&);

	virtual ~GroundGL();

private:
	glm::mat4 model_to_world;
	GLuint vbo;
	GLuint vao;
	GLuint shader;
};

} /* namespace gl */
} /* namespace app */

#endif /* GROUNDGL_H_ */
