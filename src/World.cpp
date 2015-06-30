/*
 * World.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#include "World.h"
#include "Mesh.h"
#include "ViewPort.h"
#include "Camera.h"
#include "RenderBody.h"

namespace app {

World::World():
	broadphase(new btDbvtBroadphase()),
	collisionConfiguration(new btDefaultCollisionConfiguration()),
	dispatcher(new btCollisionDispatcher(collisionConfiguration)),
	solver(new btSequentialImpulseConstraintSolver()),
	dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration))
{
    dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

void World::
reset()
{
	btCollisionObjectArray a = dynamicsWorld->getCollisionObjectArray();

	for (int i = 0; i < a.size(); i++) {
		auto o = a[i];
		if (!o->isStaticOrKinematicObject()) {
			std::cout << "Object: " << o->getUserPointer() << std::endl;
			btTransform t = o->getWorldTransform();
			btVector3 v = t.getOrigin();
			v.setY(50);
			t.setOrigin(v);
			o->setWorldTransform(t);
			o->setActivationState(1);
			o->activate(true);
		}
	}
}

void World::
render(const app::ViewPort& vp, const app::CameraPtr camera) const {
	btCollisionObjectArray a = dynamicsWorld->getCollisionObjectArray();

	axis.render(camera);
	for (int i = 0; i < a.size(); i++) {

		auto r = static_cast<app::RenderBody*>(a[i]->getUserPointer());
		r->render(camera, vp);

	}
}

World::~World() {
	// TODO Auto-generated destructor stub
}

} /* namespace app */
