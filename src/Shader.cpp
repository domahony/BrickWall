/*
 * Shader.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: domahony
 */

#include "Shader.h"
#include <string>
#include <memory>


namespace app {
namespace gl {

using std::string;
using std::shared_ptr;

Shader::
Shader(shared_ptr<ShaderSource> source) : shader(glCreateProgram())
{

	const GLchar *vertexSource = source->get_vertex_source().c_str();
	const GLchar *fragmentSource = source->get_fragment_source().c_str();

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

Shader::
~Shader() {
		// TODO Auto-generated destructor stub
	}

} /* namespace gl */
} /* namespace app */
