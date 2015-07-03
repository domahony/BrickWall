/*
 * AppObject.h
 *
 *  Created on: Jul 2, 2015
 *      Author: domahony
 */

#ifndef APPOBJECT_H_
#define APPOBJECT_H_

namespace app {
namespace gl {

class AppObject {
public:
	AppObject() {
		// TODO Auto-generated constructor stub

	}
	~AppObject() {
		// TODO Auto-generated destructor stub
	}

private:
	std::shared_ptr<Mesh> mesh;
	btTransform local_size;

	std::shared_ptr<btStridingMeshInterface> iface;
	std::shared_ptr<btBvhTriangleMeshShape> shape;
	std::shared_ptr<RenderBody> render;
	std::shared_ptr<btRigidBody> rigid;

};

} /* namespace gl */
} /* namespace app */

#endif /* APPOBJECT_H_ */
