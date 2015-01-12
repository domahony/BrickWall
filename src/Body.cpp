/*
 * Body.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#include "Body.h"
#include "GroundShader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#
namespace app {

static GLuint initShader();
static GLuint initVAO(GLuint shader);

Body::Body() :
    box(new btBoxShape(btVector3(1,1,1))),
    mass(1),
	transform(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0))),
	shader(initShader()),
	vao(initVAO(shader))
{
    btVector3 fallInertia(0, 0, 0);
    box->calculateLocalInertia(mass, fallInertia);
    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, this, box, fallInertia);
    fallRigidBody = new btRigidBody(fallRigidBodyCI);

}

void Body::
render(glm::mat4& view, glm::mat4& proj) {

    glUseProgram(shader);

    glm::mat4 model_to_world;
    transform.getOpenGLMatrix(glm::value_ptr(model_to_world));

    GLint uniModel = glGetUniformLocation(shader, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model_to_world));

    GLint uniView = glGetUniformLocation(shader, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    GLint uniProj = glGetUniformLocation(shader, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    GLint posAttrib = glGetAttribLocation(shader, "position");

    glBindVertexArray(vao);
    glEnableVertexAttribArray(posAttrib);

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisableVertexAttribArray(posAttrib);
    glBindVertexArray(0);
    glUseProgram(0);

}

Body::~Body() {
	// TODO Auto-generated destructor stub
}

static GLuint
initShader()
{
	app::gl::GroundShader s;
	return s.getShader();
}

static GLuint
initVAO(GLuint shader)
{
	GLfloat vertices[] = {
	    -0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f,  0.5f, -0.5f,
	     0.5f,  0.5f, -0.5f,
	    -0.5f,  0.5f, -0.5f,
	    -0.5f, -0.5f, -0.5f,

	    -0.5f, -0.5f,  0.5f,
	     0.5f, -0.5f,  0.5f,
	     0.5f,  0.5f,  0.5f,
	     0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f,  0.5f,
	    -0.5f, -0.5f,  0.5f,

	    -0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f, -0.5f,
	    -0.5f, -0.5f, -0.5f,
	    -0.5f, -0.5f, -0.5f,
	    -0.5f, -0.5f,  0.5f,
	    -0.5f,  0.5f,  0.5f,

	     0.5f,  0.5f,  0.5f,
	     0.5f,  0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f,  0.5f,
	     0.5f,  0.5f,  0.5f,

	    -0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f, -0.5f,
	     0.5f, -0.5f,  0.5f,
	     0.5f, -0.5f,  0.5f,
	    -0.5f, -0.5f,  0.5f,
	    -0.5f, -0.5f, -0.5f,

	    -0.5f,  0.5f, -0.5f,
	     0.5f,  0.5f, -0.5f,
	     0.5f,  0.5f,  0.5f,
	     0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f,  0.5f,
	    -0.5f,  0.5f, -0.5f,
	};

	GLuint vbo;

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    app::gl::GroundShader gshader;
    shader = gshader.getShader();

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shader, "position");

    GLuint vao;

    // Create and bind Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

} /* namespace app */
