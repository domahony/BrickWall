/*
 * Body.h
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#ifndef BODY_H_
#define BODY_H_

#include <btBulletDynamicsCommon.h>

namespace app {

class Body {
public:
	Body();
	virtual ~Body();
	btRigidBody *getRigidBody() const {
		return fallRigidBody;
	}

	void getWorldTransform(btTransform& trans) const {
		fallMotionState->getWorldTransform(trans);
	}
	
	void render();
	
private:
    btCollisionShape* box;
    btScalar mass;
    btDefaultMotionState* fallMotionState;
    btRigidBody* fallRigidBody;
    glUint shader;
    glUint vao;
};

} /* namespace app */

#endif /* BODY_H_ */
