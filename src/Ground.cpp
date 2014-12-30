/*
 * Ground.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#include "Ground.h"

namespace app {

Ground::Ground() :
    groundShape(new btStaticPlaneShape(btVector3(0, 1, 0), 1)),
    groundMotionState(new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)))),
    groundRigidBody(0)
{
    btRigidBody::btRigidBodyConstructionInfo
                    groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));

    groundRigidBody = new btRigidBody(groundRigidBodyCI);
}

Ground::~Ground() {
	// TODO Auto-generated destructor stub
}

} /* namespace app */
