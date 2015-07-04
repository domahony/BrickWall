/*
 * AppObject.h
 *
 *  Created on: Jul 2, 2015
 *      Author: domahony
 */

#ifndef APPOBJECT_H_
#define APPOBJECT_H_

#include "World.h"

namespace app {
namespace gl {

class AppObject : btMotionState {
public:
	AppObject(app::World& world);

	void getWorldTransform(btTransform& trans) const {
		trans = wtransform;
	}

	void setWorldTransform(const btTransform& trans) {
		wtransform = trans;
		std::cout << "Yeah! " << wtransform.getOrigin().getX() << ", " << wtransform.getOrigin().getY() << std::endl;
	}

	void render(const app::CameraPtr& c, const app::ViewPort& vp) const;

private:
	std::shared_ptr<Mesh> mesh;
	btTransform local_size;
	btTransform wtransform;

	std::shared_ptr<btStridingMeshInterface> iface;
	std::shared_ptr<btBvhTriangleMeshShape> shape;
	std::shared_ptr<btRigidBody> rigid;

};

} /* namespace gl */
} /* namespace app */

#endif /* APPOBJECT_H_ */
