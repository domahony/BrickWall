/*
 * Body.cpp
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#include "Body.h"

namespace app {

Body::Body() :
    box(new btBoxShape(btVector3(1,1,1))),
    mass(1)
{
    btVector3 fallInertia(0, 0, 0);
    box->calculateLocalInertia(mass, fallInertia);
    fallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));

    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, box, fallInertia);
    fallRigidBody = new btRigidBody(fallRigidBodyCI);
}

void Body::
render()
{
	glUseProgram();
	glBindVertexArray();
	
	for (int i = 0; i < attribs.length; i++) {
		glEnableVertexAttribArray(i);
	}
	
	shader.bindViewMatrix();
	shader.bindModelMatrix(getWorldTransform());
	
	glDrawArrays();
}

Body::~Body() {
	// TODO Auto-generated destructor stub
}

} /* namespace app */
