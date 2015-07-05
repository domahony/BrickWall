/*
 * AppObject.h
 *
 *  Created on: Jul 2, 2015
 *      Author: domahony
 */

#ifndef APPOBJECT_H_
#define APPOBJECT_H_

#include "World.h"
#include "Mesh.h"
#include "bullet/btBulletDynamicsCommon.h"


namespace app {
namespace gl {

class AppObject : btMotionState {
public:
	AppObject(std::shared_ptr<Mesh>, std::shared_ptr<btCollisionShape>);

	void addToWorld(app::WorldPtr world, const btRigidBody::btRigidBodyConstructionInfo& ctor);

	void getWorldTransform(btTransform& trans) const {
		trans = wtransform;
	}

	void setWorldTransform(const btTransform& trans) {
		wtransform = trans;
	}

	void render(const app::CameraPtr& c, const app::ViewPort& vp) const;

private:
	std::shared_ptr<Mesh> mesh;
	btTransform wtransform;

	std::shared_ptr<btStridingMeshInterface> iface;
	std::shared_ptr<btCollisionShape> shape;
	std::shared_ptr<btRigidBody> rigid;

};

} /* namespace gl */
} /* namespace app */

#endif /* APPOBJECT_H_ */
