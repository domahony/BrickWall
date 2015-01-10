/*
 * Body.h
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#ifndef BODY_H_
#define BODY_H_

#include <btBulletDynamicsCommon.h>
#include <iostream>

namespace app {

class Body : public btMotionState {
public:
	Body();
	virtual ~Body();
	btRigidBody *getRigidBody() const {
		return fallRigidBody;
	}

	void getWorldTransform(btTransform& trans) const {
		trans = transform;
	}
	
	void setWorldTransform(const btTransform& trans) {
		transform = trans;
		std::cout << transform.getOrigin().getX() << ", " << transform.getOrigin().getY() << std::endl;
	}

	void render();
	
private:
    btCollisionShape* box;
    btScalar mass;
    btTransform transform;
    btRigidBody* fallRigidBody;
    /*
    glUint shader;
    glUint vao;
    */
};

} /* namespace app */

#endif /* BODY_H_ */
