/*
 * RenderBody.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#include "types.h"
#include "ObjMesh.h"
#include "Shader.h"
#include <fstream>
#include <boost/tokenizer.hpp>

struct xyz {
	float x;
	float y;
	float z;
};

struct Verts {
	xyz pos;
	xyz norm;
};

using namespace boost;
using namespace std;

namespace app {

static GLfloat* loadVertices(const std::string& fname, vector<Verts>&);
static GLuint initVAO(const std::string& fname, std::shared_ptr<app::gl::Shader> shader);

ObjMesh::ObjMesh(const std::string& fname, std::shared_ptr<app::gl::Shader> shader):
		app::gl::Mesh(shader, initVAO(fname, shader), GL_TRIANGLES, 0, 36)
{

}

ObjMesh::~ObjMesh() {
	// TODO Auto-generated destructor stub
}

static GLuint
initVAO(const std::string& fname, std::shared_ptr<app::gl::Shader> shader)
{

	vector<Verts> v;

	loadVertices(fname, v);

	GLuint vbo;

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, v.size()/sizeof(Verts), &v[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shader->getShader(), "position");

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

static GLfloat*
loadVertices(const std::string& fname, vector<Verts>& verts)
{
	ifstream f(fname.c_str());

	vector<xyz> pos;
	vector<xyz> norms;


	while (!f.eof()) {

		string line;
		getline(f, line);

		tokenizer<boost::char_separator<char>> tok(line, boost::char_separator<char>(" "));

		auto i = tok.begin();

		if (*i == "v") {
			xyz v;
			++i;
			v.x = stof(*i);
			++i;
			v.y = stof(*i);
			++i;
			v.z = stof(*i);
			pos.push_back(v);
		}

		if (*i == "vn") {
			xyz v;
			++i;
			v.x = stof(*i);
			++i;
			v.y = stof(*i);
			++i;
			v.z = stof(*i);
			norms.push_back(v);
		}

		if (*i == "f") {

			++i;

			boost::char_separator<char> sep("/", 0, boost::keep_empty_tokens);

			for (int V = 0; V < 3; V++) {

				/*
				 * not sure what's wrong with this loop.
				 */
				tokenizer<boost::char_separator<char>> tok2(*i++, sep);

				auto j = tok2.begin();

				int p_idx = std::stoi(*j);
				++j;
				++j;
				int n_idx = std::stoi(*j);

				Verts vert;

				vert.pos = pos[p_idx-1];
				vert.norm = norms[n_idx-1];

				verts.push_back(vert);
			}

		}
	}
}

} /* namespace app */
