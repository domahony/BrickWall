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
	class Shader;
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
};

	ObjMesh(const std::string& fname, std::shared_ptr<app::gl::Shader>);

	std::shared_ptr<app::gl::Mesh> getMesh() const {
		return mesh;
	}

	btCollisionShape* getShape() const {
		return mesh_shape;
	}

	virtual ~ObjMesh();

private:

	void create_mesh();

	std::vector<idx_triangle> triangles;
	std::vector<xyz_> vertices;
	std::vector<xyz_> normals;
	btStridingMeshInterface *iface;
	std::shared_ptr<app::gl::Shader> shader;
	std::shared_ptr<app::gl::Mesh> mesh;
	btBvhTriangleMeshShape *mesh_shape;
};

} /* namespace app */

#endif /* OBJMESH_H_ */
