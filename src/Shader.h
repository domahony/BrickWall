/*
 * Shader.h
 *
 *  Created on: Jan 27, 2015
 *      Author: domahony
 */

#ifndef SHADER_H_
#define SHADER_H_

#include "types.h"
#include <btBulletDynamicsCommon.h>

namespace app {
namespace gl {

class Shader {
public:
	Shader() : shader(glCreateProgram())
{

	const GLchar* vertexSource = R"(#version 150 core
    in vec3 position;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;
    void main() {
       gl_Position = proj * view * model * vec4(position, 1.0);
    }
)";

	const GLchar* fragmentSource = R"(#version 150 core
    out vec4 outColor;
    void main() {
       outColor = vec4(1.0,1.0,1.0,1.0);
    };
)";

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

	}
	~Shader() {
		// TODO Auto-generated destructor stub
	}

	void enable() const {
		glUseProgram(shader);
	}

	GLuint getShader() const {
		return shader;
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

	}

private:
	GLuint shader;

};

} /* namespace gl */
} /* namespace app */

#endif /* SHADER_H_ */
