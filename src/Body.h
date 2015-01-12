/*
 * Body.h
 *
 *  Created on: Dec 17, 2014
 *      Author: domahony
 */

#ifndef BODY_H_
#define BODY_H_

#define GL_GLEXT_PROTOTYPES 1
#define GL3_PROTOTYPES 1
#include <GL/gl.h>
#include <glm/glm.hpp>

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

	void render(glm::mat4& view, glm::mat4& proj);

private:
    btCollisionShape* box;
    btScalar mass;
    btTransform transform;
    btRigidBody* fallRigidBody;
    GLuint shader;
    GLuint vao;
};

} /* namespace app */

#endif /* BODY_H_ */
