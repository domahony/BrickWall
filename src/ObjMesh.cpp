/*
 * RenderBody.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#include "types.h"
#include "ObjMesh.h"
#include "Shader.h"
#include "Mesh.h"
#include <fstream>
#include <boost/tokenizer.hpp>

using namespace boost;
using namespace std;

namespace app {

static void init(const string&, shared_ptr<app::gl::Shader>, vector<ObjMesh::idx_triangle>&, vector<ObjMesh::xyz_>&, vector<ObjMesh::xyz_>&);

ObjMesh::ObjMesh(const std::string& fname, std::shared_ptr<app::gl::Shader> shader):
		triangles(), vertices(), normals(), shader(shader)
{
	init(fname, shader, triangles, vertices, normals);

	create_mesh();

	btTriangleMesh *tmesh = new btTriangleMesh();

	for (auto v = triangles.begin(); v != triangles.end(); ++v) {

		btVector3 vec[3];
		for (int i = 0; i < 3; ++i) {
			vec[i].setValue(
					vertices[(*v).v[i]].x,
					vertices[(*v).v[i]].y,
					vertices[(*v).v[i]].z
			);
		}

		tmesh->addTriangle(vec[0], vec[1], vec[2], true);
	}

	iface = tmesh;
	mesh_shape = new btBvhTriangleMeshShape(tmesh, false);
}

void  ObjMesh::
create_mesh() {

	vector<GLfloat> verts;

	for (auto v = triangles.begin(); v != triangles.end(); ++v) {

		for (int i = 0; i < 3; ++i) {
			verts.push_back( vertices[(*v).v[i]].x );
			verts.push_back( vertices[(*v).v[i]].y );
			verts.push_back( vertices[(*v).v[i]].z );

			verts.push_back( normals[(*v).n[i]].x );
			verts.push_back( normals[(*v).n[i]].y );
			verts.push_back( normals[(*v).n[i]].z );
		}
	}

	GLuint vbo;

    // Create a Vertex Buffer Object and copy the vertex data to it
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(verts[0]), &verts[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shader->getShader(), "position");
    GLint normAttrib = glGetAttribLocation(shader->getShader(), "normal");

    GLuint vao;

    // Create and bind Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mesh = shared_ptr<app::gl::Mesh>(new app::gl::Mesh(shader, vao, GL_TRIANGLES, 0, verts.size() * 2));
}

ObjMesh::~ObjMesh() {
	// TODO Auto-generated destructor stub
}

static void
loadVertices(const std::string& fname, vector<ObjMesh::idx_triangle>& triangles, vector<ObjMesh::xyz_>& vertices, vector<ObjMesh::xyz_>& normals);

static void
init(const string& fname, shared_ptr<app::gl::Shader> shader, vector<ObjMesh::idx_triangle>& triangles, vector<ObjMesh::xyz_>& vertices, vector<ObjMesh::xyz_>& normals)
{
	loadVertices(fname, triangles, vertices, normals);
	int tri_count = 0;

	for (auto i = triangles.begin(); i != triangles.end(); ++i) {

		std::cout << "("
			<< (*i).v[0] << ", "
			<< (*i).v[1] << ", "
			<< (*i).v[2] << ") "
			<< std::endl ;

		std::cout << "("
			<< (*i).n[0] << ", "
			<< (*i).n[1] << ", "
			<< (*i).n[2] << ") "
			<< std::endl
			<< std::endl;
	}
}

static void xxxx(const std::string&, int, ObjMesh::idx_triangle&);

static void
loadVertices(const std::string& fname, vector<ObjMesh::idx_triangle>& triangles, vector<ObjMesh::xyz_>& vertices, vector<ObjMesh::xyz_>& normals)
{
	ifstream f(fname.c_str());

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
			ObjMesh::xyz_ v;
			++i;
			v.x = stof(*i);
			++i;
			v.y = stof(*i);
			++i;
			v.z = stof(*i);
			vertices.push_back(v);
		}

		if (*i == "vn") {
			ObjMesh::xyz_ n;
			++i;
			n.x = stof(*i);
			++i;
			n.y = stof(*i);
			++i;
			n.z = stof(*i);
			normals.push_back(n);
		}

		if (*i == "f") {

			++i;
			auto vert1 = *i++;
			auto vert2 = *i++;
			auto vert3 = *i;

			std::string _v[] = {vert1,vert2,vert3};

			ObjMesh::idx_triangle t_idx;
			for (int V = 0; V < 3; V++) {
				xxxx(_v[V], V, t_idx);
			}

			triangles.push_back(t_idx);
		}
	}
}

static void xxxx(const std::string& str, int cnt, ObjMesh::idx_triangle& idx)
{
				boost::char_separator<char> sep("/", 0, boost::keep_empty_tokens);
				tokenizer<boost::char_separator<char>> tok2(str, sep);

				auto j = tok2.begin();

				int p_idx = std::stoi(*j);
				++j;
				++j;
				int n_idx = std::stoi(*j);

				idx.v[cnt] = p_idx - 1;
				idx.n[cnt] = n_idx - 1;
}

} /* namespace app */
