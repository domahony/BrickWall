/*
 * GroundShader.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: domahony
 */

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include "GroundShader.h"
#include <string>

namespace app {
namespace gl {

using std::string;

static GLuint compileShader();

GroundShader::GroundShader() : shader(compileShader()) {
	// TODO Auto-generated constructor stub

}

GroundShader::~GroundShader() {
	// TODO Auto-generated destructor stub
}

static GLuint
compileShader()
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
    GLuint ret = glCreateProgram();
    glAttachShader(ret, vertexShader);
    glAttachShader(ret, fragmentShader);
    glLinkProgram(ret);

    return ret;
}

} /* namespace gl */
} /* namespace app */
