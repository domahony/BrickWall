/*
 * RenderBody.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#include "BoxMesh.h"
#include "GroundShader.h"

namespace app {

static GLuint initVAO(GLuint shader, std::vector<GLuint>& v, std::map<std::string, GLuint>& uniform);
static GLuint initShader();

BoxMesh::BoxMesh():
		shader(initShader()),
		vao(initVAO(shader, vertex_attrib_idx, uniform)),
		mode(GL_TRIANGLES),
		first_idx(0), count(36) {

}

BoxMesh::~BoxMesh() {
	// TODO Auto-generated destructor stub
}

static GLuint
initShader()
{
	app::gl::GroundShader s;
	return s.getShader();
}

static GLuint
initVAO(GLuint shader, std::vector<GLuint>& v, std::map<std::string, GLuint>& uniform)
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

    GLint uniModel = glGetUniformLocation(shader, "model");
    uniform["model"] = uniModel;
    GLint uniView = glGetUniformLocation(shader, "view");
    uniform["view"] = uniView;
    GLint uniProj = glGetUniformLocation(shader, "proj");
    uniform["proj"] = uniProj;

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shader, "position");

    GLuint vao;

    // Create and bind Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    v.push_back(posAttrib);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

} /* namespace app */
