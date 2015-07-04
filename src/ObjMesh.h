/*
 * RenderBody.h
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#ifndef OBJMESH_H_
#define OBJMESH_H_

#include <vector>
#include <memory>
#include <bullet/btBulletCollisionCommon.h>

namespace app {

namespace gl {
	class ShaderBase;
	class Mesh;
};

class ObjMesh {

public:
struct xyz_ {
	btScalar x;
	btScalar y;
	btScalar z;
};

struct idx_triangle {
	int v[3];
	int n[3];
	int uv[3];
};

struct uv_ {
	btScalar u;
	btScalar v;
};

	ObjMesh(const std::string& fname, std::shared_ptr<app::gl::ShaderBase>, const float& scale=1.f);

	std::shared_ptr<app::gl::Mesh> getMesh() const {
		return mesh;
	}

	std::shared_ptr<btCollisionShape> getShape() const {
		return mesh_shape;
	}

	virtual ~ObjMesh();

private:

	void create_mesh(const float&);

	std::vector<idx_triangle> triangles;
	std::vector<xyz_> vertices;
	std::vector<xyz_> normals;
	std::vector<uv_> uvs;
	btStridingMeshInterface *iface;
	std::shared_ptr<app::gl::ShaderBase> shader;
	std::shared_ptr<app::gl::Mesh> mesh;
	std::shared_ptr<btBvhTriangleMeshShape> mesh_shape;
};

} /* namespace app */

#endif /* OBJMESH_H_ */
