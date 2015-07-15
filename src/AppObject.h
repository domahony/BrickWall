/*
 * AppObject.h
 *
 *  Created on: Jul 2, 2015
 *      Author: domahony
 */

#ifndef APPOBJECT_H_
#define APPOBJECT_H_

#include "Mesh.h"
#include "bullet/btBulletDynamicsCommon.h"


namespace app {

class World;

namespace gl {


class AppObject : public btMotionState {
public:
	AppObject(std::shared_ptr<Mesh>, std::shared_ptr<btCollisionShape>, const btTransform& pos);

	AppObject(const AppObject& ao) {
		this->mesh = ao.mesh;
		this->iface = ao.iface;
		this->shape = ao.shape;
		this->wtransform = ao.wtransform;
		this->mass = ao.mass;
		this->inertia = ao.inertia;
	}

	virtual ~AppObject() {
		std::cout << "Freeing AppObject " << this << std::endl;
	}

	void addToWorld(std::shared_ptr<app::World> w, const btRigidBody::btRigidBodyConstructionInfo& ctor);

	void getWorldTransform(btTransform& trans) const {
		trans = wtransform;
	}

	void setMass(float mass) {
		this->mass = mass;
	}

	float getMass() const {
		return mass;
	}

	void setInitialInertia(const btVector3& v) {
		inertia = v;
	}

	btVector3 getInitialInertia() const {
		return inertia;
	}

	void setWorldTransform(const btTransform& trans) {
		wtransform = trans;
	}

	std::shared_ptr<btCollisionShape> getCollisionShape() const {
		return shape;
	}

	void setRigidBody(std::shared_ptr<btRigidBody> r) {
		rigid = r;
	}

	void render(const app::CameraPtr& c, const app::ViewPort& vp) const;

private:
	std::shared_ptr<Mesh> mesh;
	btTransform wtransform;

	std::shared_ptr<btStridingMeshInterface> iface;
	std::shared_ptr<btCollisionShape> shape;
	std::shared_ptr<btRigidBody> rigid;
	float mass;
	btVector3 inertia;

};

} /* namespace gl */
} /* namespace app */

#endif /* APPOBJECT_H_ */
