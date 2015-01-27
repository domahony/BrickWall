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
#include "GroundShader.h"

namespace app {
namespace gl {


GroundGL::GroundGL() : model_to_world(1.) {

	/*
    GLfloat vertices[] = {
        -1.0f, -1.0f, -0.5f,
         1.0f, -1.0f, -0.5f,
         1.0f,  1.0f, -0.5f,
         1.0f,  1.0f, -0.5f,
        -1.0f,  1.0f, -0.5f,
        -1.0f, -1.0f, -0.5f,
    };
    */

    GLfloat vertices[] = {
    	-10.0f, 0.0f, 10.0f,
    	-10.0f, 0.0f, -10.0f,
    	10.0f, 0.0f, -10.0f,

    	/*
        -1.0f, -0.0f, -1.0f,
         1.0f, -0.0f, -1.0f,
         1.0f, -0.0f,  1.0f,
         1.0f, -0.0f,  1.0f,
        -1.0f, -0.0f,  1.0f,
        -1.0f, -0.0f, -1.0f,
        */
    };

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    app::gl::GroundShader gshader;
    shader = gshader.getShader();

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

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(posAttrib);
    glBindVertexArray(0);
    glUseProgram(0);
}

} /* namespace gl */
} /* namespace app */
