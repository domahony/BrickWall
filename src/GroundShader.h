/*
 * GroundShader.h
 *
 *  Created on: Jan 10, 2015
 *      Author: domahony
 */

#ifndef GROUNDSHADER_H_
#define GROUNDSHADER_H_

#include <GL/gl.h>

namespace app {
namespace gl {

class GroundShader {
public:
	GroundShader();
	virtual ~GroundShader();

private:
	GLuint shader;
};

} /* namespace gl */
} /* namespace app */

#endif /* GROUNDSHADER_H_ */
