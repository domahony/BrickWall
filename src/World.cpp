/*
 * World.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#include "Renderer.h"
#include "World.h"

#include "BoxMesh.h"
#include "ViewPort.h"
#include "Camera.h"

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
render(const app::ViewPort& vp, const app::Camera camera, const app::gl::Renderer& renderer) const {
	btCollisionObjectArray a = dynamicsWorld->getCollisionObjectArray();

	for (int i = 0; i < a.size(); i++) {

		auto shape = a[i]->getCollisionShape();

		auto r = static_cast<app::RenderBody*>(a[i]->getUserPointer());
		//auto r = static_cast<app::RenderBody*>(shape->getUserPointer());

		if (r) {
			renderer.render(vp, camera, *r);
		}

	}
}

World::~World() {
	// TODO Auto-generated destructor stub
}

} /* namespace app */
