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

static void loadVertices(const std::string& fname, vector<Verts>&);
static GLuint initVAO(const std::string& fname, std::shared_ptr<app::gl::Shader> shader, int& n_verts);

ObjMesh::ObjMesh(const std::string& fname, std::shared_ptr<app::gl::Shader> shader):
		app::gl::Mesh(shader, initVAO(fname, shader, n_verts), GL_TRIANGLES, 0, n_verts)
{

}

ObjMesh::~ObjMesh() {
	// TODO Auto-generated destructor stub
}

static GLuint
initVAO(const std::string& fname, std::shared_ptr<app::gl::Shader> shader, int& n_verts)
{

	vector<Verts> v;

	loadVertices(fname, v);
	for (auto i = v.begin(); i != v.end(); ++i) {
		std::cout << "("
			<< (*i).pos.x << ", "
			<< (*i).pos.y << ", "
			<< (*i).pos.z << ")"
				<< std::endl;
		std::cout << "("
			<< (*i).norm.x << ", "
			<< (*i).norm.y << ", "
			<< (*i).norm.z << ")"
				<< std::endl;
	}

	n_verts = v.size() * 2;

	std::cout << "Total Size: " << (v.size() * sizeof(Verts)) / sizeof(GLfloat) << std::endl;

	//std::exit(0);

	GLuint vbo;

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(v[0]), &v[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shader->getShader(), "position");
    GLint normAttrib = glGetAttribLocation(shader->getShader(), "normal");

    GLuint vao;

    // Create and bind Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), 0);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return vao;
}

static void xxxx(const std::string& , const vector<xyz>&, const vector<xyz>&, vector<Verts>& verts);

static void
loadVertices(const std::string& fname, vector<Verts>& verts)
{
	ifstream f(fname.c_str());

	vector<xyz> pos;
	vector<xyz> norms;

	bool done = false;
	while (!done) {

		string line;
		getline(f, line);
		if (f.eof()) {
			break;
		}

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
			auto vert1 = *i++;
			auto vert2 = *i++;
			auto vert3 = *i;

			std::string _v[] = {vert1,vert2,vert3};

			for (int V = 0; V < 3; V++) {
				xxxx(_v[V], pos, norms, verts);
			}

		}
	}
}

static void xxxx(const std::string& str, const vector<xyz>& pos, const vector<xyz>& norms, vector<Verts>& verts)
{

				boost::char_separator<char> sep("/", 0, boost::keep_empty_tokens);
				tokenizer<boost::char_separator<char>> tok2(str, sep);

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

} /* namespace app */
