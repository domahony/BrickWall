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

class Ground : public btMotionState{
public:
	Ground();
	virtual ~Ground();

	btRigidBody* getRigidBody() const {
		return groundRigidBody;
	}

	void getWorldTransform(btTransform& t) const {
		t = transform;
	}

	void setWorldTransform(const btTransform& t) {
		transform = t;
	}

private:
	void initOpenGL();

private:
	btTransform transform;
    btCollisionShape* groundShape;
    btRigidBody* groundRigidBody;
};

} /* namespace app */

#endif /* GROUND_H_ */
