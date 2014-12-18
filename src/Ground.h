/*
 * Ground.h
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#ifndef GROUND_H_
#define GROUND_H_

#include <btBulletDynamicsCommon.h>

namespace app {

class Ground {
public:
	Ground();
	virtual ~Ground();

	btRigidBody* getRigidBody() const {
		return groundRigidBody;
	}

private:
    btCollisionShape* groundShape;
    btDefaultMotionState* groundMotionState;
    btRigidBody* groundRigidBody;
};

} /* namespace app */

#endif /* GROUND_H_ */
