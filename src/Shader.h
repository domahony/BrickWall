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
    in vec3 normal;
    out vec3 normOut;
    out vec3 pos;
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;
    void main() {
       gl_Position = proj * view * model * vec4(position, 1.0);
       normOut = normal; 
       pos = position;
    }
)";

	const GLchar* fragmentSource = R"(#version 150 core
    
    in vec3 normOut;
    in vec3 pos;
    out vec4 outColor;
    uniform vec3 eye;
    uniform vec3 light;
    uniform mat4 model;
    void main() {

       vec4 constantColor = vec4(0.9, 0.9, 0.9, 1.0);
       //vec3 omniPos = vec3(inverse(model) * vec4(10, 1, -8, 0));
       vec3 omniPos = vec3(inverse(model) * vec4(0, 5.5, 20, 0));
       //vec3 omniPos = vec3(vec4(0, 3, 0, 1));
       float invOmniRad = 1.0/250.0;
       vec3 omniColor = vec3(1.0, 1.0, 1.0);
       vec3 viewPos = vec3(inverse(model) * vec4(0.0, 5.5, 20.0, 0));
       //vec3 viewPos = vec3(vec4(0.0, 5.5, 20.0, 1));
       vec3 ambientLightColor = vec3(0.2, 0.2, 0.2);
       float specExponent = 200;
       vec4 mattDiff = vec4(1.0, 1.0, 1.0, 1.0);
       vec4 mattSpec = mattDiff;

       vec3 N = normalize(normOut);
       vec3 L = omniPos - pos; 
       float dist = length(L);
       L /= dist;

       vec3 V = normalize(viewPos - pos);
       vec3 H = normalize(V + L);

       vec3 lightColor = omniColor * max(1 - dist * invOmniRad, 0);
       float diffFactor = max(dot(N,L), 0);
       float specFactor = pow(max(dot(N,H), 0), specExponent);

       vec3 diffColor = lightColor * diffFactor + ambientLightColor;
       vec3 specColor = lightColor * specFactor;

       outColor = mattDiff;
       outColor.rgb *= diffColor;
       outColor.rgb += mattSpec.rgb * specColor;

       outColor *= constantColor;

       //outColor = vec4(1.0,1.0,1.0,1.0);
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
