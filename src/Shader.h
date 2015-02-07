/*
 * Shader.h
 *
 *  Created on: Jan 27, 2015
 *      Author: domahony
 */

#ifndef SHADER_H_
#define SHADER_H_

#include "types.h"
#include <iostream>
#include <btBulletDynamicsCommon.h>

namespace app {
namespace gl {

class Shader {
public:

	Shader();

	~Shader();

	void enable() const {
		glUseProgram(shader);
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

	void enableVertexAttribs() const {

		GLint posAttrib = glGetAttribLocation(shader, "position");
		glEnableVertexAttribArray(posAttrib);

		posAttrib = glGetAttribLocation(shader, "normal");
		glEnableVertexAttribArray(posAttrib);
	}

private:
	GLuint shader;

};

} /* namespace gl */
} /* namespace app */

#endif /* SHADER_H_ */
