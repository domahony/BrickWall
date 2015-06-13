/*
 * ShaderBase.h
 *
 *  Created on: Jun 13, 2015
 *      Author: domahony
 */

#include "types.h"
#include <btBulletDynamicsCommon.h>

#ifndef SHADERBASE_H_
#define SHADERBASE_H_

namespace app {
namespace gl {

class ShaderBase {
public:
	ShaderBase(const GLchar* vs, const GLchar* fs) : shader(glCreateProgram())
{
    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, nullptr);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

	}
	virtual ~ShaderBase() {
		// TODO Auto-generated destructor stub
	}

	GLuint getShader() const {
		return shader;
	}

	void setViewPos(const btScalar* v) const {
		GLint uni = glGetUniformLocation(shader, "viewPos");
		glUniform3f(uni, v[0], v[1], v[2]);
	}

	void setLightPos(const btScalar* v) const {
		GLint uni = glGetUniformLocation(shader, "lightPos");
		glUniform3f(uni, v[0], v[1], v[2]);
	}

	void setCameraMatrix(const btScalar* m) const {

		GLint uniModel = glGetUniformLocation(shader, "view");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, m);

	}

	void setViewportMatrix(const btScalar* m) const {

		GLint uniModel = glGetUniformLocation(shader, "proj");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, m);

	}

	void setModelMatrix(const btScalar* m) const {

		GLint uniModel = glGetUniformLocation(shader, "model");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, m);

	}

	void enable() const {
		glUseProgram(shader);
	}

	void enableVertexAttribs() const {

		GLint posAttrib = glGetAttribLocation(shader, "position");
		glEnableVertexAttribArray(posAttrib);

		posAttrib = glGetAttribLocation(shader, "normal");
		glEnableVertexAttribArray(posAttrib);
	}

private:
	GLuint shader;

private:

};

} /* namespace gl */
} /* namespace app */

#endif /* SHADERBASE_H_ */
