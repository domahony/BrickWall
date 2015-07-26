/*
 * World.h
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <random>
#include <btBulletDynamicsCommon.h>
#include "ViewPort.h"
#include "Camera.h"
#include "Axis.h"
#include "AppObject.h"
#include "Vehicle.h"

namespace app {

class World {
public:
	World();
	virtual ~World();

	void addRigidBody(btRigidBody* body) {
		dynamicsWorld->addRigidBody(body);
	}

	void stepSimulation() {
        dynamicsWorld->stepSimulation(1/60.f, 10);
	}

	void addToWorld(std::shared_ptr<app::gl::AppObject>& o, const btRigidBody::btRigidBodyConstructionInfo& ctor)
	{
		btRigidBody::btRigidBodyConstructionInfo c(ctor);
		c.m_motionState = o.get();

		if (!c.m_collisionShape)
			c.m_collisionShape = o->getCollisionShape().get();

		std::shared_ptr<btRigidBody> rigid(std::make_shared<btRigidBody>(c));
		o->setRigidBody(rigid);
		o->setMass(c.m_mass);
		o->setInitialInertia(c.m_localInertia);

		rigid->setUserPointer(o.get());
		dynamicsWorld->addRigidBody(rigid.get());

		objects.push_back(o);
	}

	void addVehicle(app::gl::Vehicle* v)
	{
		dynamicsWorld->addAction(v);
	}

	void move_vehicle_forward() {

	}

	void reset();

	void render(const app::ViewPort& vp, const app::CameraPtr camera) const;

private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    std::vector<std::shared_ptr<app::gl::AppObject>> objects;
    app::gl::Axis axis;
    std::random_device device;
    std::mt19937 gen;
    std::uniform_real_distribution<> disx;
    std::uniform_real_distribution<> disy;
    std::uniform_real_distribution<> disz;

};

typedef std::shared_ptr<World> WorldPtr;

} /* namespace app */

#endif /* WORLD_H_ */
