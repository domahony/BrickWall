/*
 * World.h
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#ifndef WORLD_H_
#define WORLD_H_
#include <btBulletDynamicsCommon.h>
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

private:
    btBroadphaseInterface* broadphase;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* dispatcher;
    btSequentialImpulseConstraintSolver* solver;
    btDiscreteDynamicsWorld* dynamicsWorld;

};

} /* namespace app */

#endif /* WORLD_H_ */
