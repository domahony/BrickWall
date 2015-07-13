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
#include "AppObject.h"

namespace app {

World::World():
	broadphase(new btDbvtBroadphase()),
	collisionConfiguration(new btDefaultCollisionConfiguration()),
	dispatcher(new btCollisionDispatcher(collisionConfiguration)),
	solver(new btSequentialImpulseConstraintSolver()),
	dynamicsWorld(new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration)),
	device(),
	gen(std::random_device()()),
	disx(-9.1, 9.2),
	disy(55, 80),
	disz(-9.3, 9.0)
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

			if (v.getY() < -10) {

				std::shared_ptr<app::gl::AppObject> new_object;

				dynamicsWorld->removeCollisionObject(o);
				for (auto i = objects.begin(); i != objects.end(); ++i) {
					if (i->get() == o->getUserPointer()) {
						new_object = std::make_shared<app::gl::AppObject>(*(i->get()));
						v.setX(disx(gen));
						v.setY(disy(gen));
						v.setZ(disz(gen));
						t.setOrigin(v);
						new_object->setWorldTransform(t);
						objects.erase(i);
						break;
					}
				}
				addToWorld(new_object,
						btRigidBody::btRigidBodyConstructionInfo(new_object->getMass(),
								nullptr, nullptr, new_object->getInitialInertia()));
			} else {

				v.setX(disx(gen));
				v.setY(disy(gen));
				v.setZ(disz(gen));
				t.setOrigin(v);
				o->setWorldTransform(t);
				o->setInterpolationLinearVelocity(btVector3(0,0,0));
				o->setInterpolationAngularVelocity(btVector3(0,0,0));
				o->setActivationState(1);
				o->activate(true);
			}

		}
	}
}

void World::
render(const app::ViewPort& vp, const app::CameraPtr camera) const {
	btCollisionObjectArray a = dynamicsWorld->getCollisionObjectArray();

	axis.render(camera);
	for (int i = 0; i < a.size(); i++) {

		//auto r = static_cast<app::RenderBody*>(a[i]->getUserPointer());
		auto r = static_cast<app::gl::AppObject*>(a[i]->getUserPointer());
		r->render(camera, vp);

	}
}

World::~World() {
	// TODO Auto-generated destructor stub
}

} /* namespace app */
