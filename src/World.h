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

	void reset();

	void render(const app::ViewPort& vp, const app::CameraPtr camera) const;

private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;
    app::gl::Axis axis;
    std::random_device device;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

};

typedef std::shared_ptr<World> WorldPtr;

} /* namespace app */

#endif /* WORLD_H_ */
