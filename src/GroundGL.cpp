/*
 * GroundGL.cpp
 *
 *  Created on: Dec 30, 2014
 *      Author: domahony
 */
#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GroundGL.h"

namespace app {
namespace gl {

// Shader sources
static const GLchar* vertexSource =
    "#version 150 core\n"
    "in vec3 position;"
    "uniform mat4 model;"
    "uniform mat4 view;"
    "uniform mat4 proj;"
    "void main() {"
    "   gl_Position = proj * view * model * vec4(position, 1.0);"
    "}";

static const GLchar* fragmentSource =
    "#version 150 core\n"
    "out vec4 outColor;"
    "void main() {"
    "   outColor = vec4(1.0,1.0,1.0,1.0);"
    "}";


GroundGL::GroundGL() : model_to_world(1.) {

    GLfloat vertices[] = {
        -1.0f, -1.0f, -0.5f,
         1.0f, -1.0f, -0.5f,
         1.0f,  1.0f, -0.5f,
         1.0f,  1.0f, -0.5f,
        -1.0f,  1.0f, -0.5f,
        -1.0f, -1.0f, -0.5f,
    };

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    shader = glCreateProgram();
    glAttachShader(shader, vertexShader);
    glAttachShader(shader, fragmentShader);
    glLinkProgram(shader);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shader, "position");

    // Create and bind Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}

GroundGL::~GroundGL() {
}

void GroundGL::render(glm::mat4& view, glm::mat4& proj) {

    glUseProgram(shader);

    GLint uniModel = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model_to_world));

    GLint uniView = glGetUniformLocation(shader, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    GLint uniProj = glGetUniformLocation(shader, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    GLint posAttrib = glGetAttribLocation(shader, "position");

    glBindVertexArray(vao);
    glEnableVertexAttribArray(posAttrib);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(posAttrib);
    glBindVertexArray(0);
    glUseProgram(0);
}

} /* namespace gl */
} /* namespace app */
