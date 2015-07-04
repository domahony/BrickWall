/*
 * BodyFactory.h
 *
 *  Created on: Jan 15, 2015
 *      Author: domahony
 */

#ifndef BODYFACTORY_H_
#define BODYFACTORY_H_

#include <memory>
#include <btBulletDynamicsCommon.h>
#include "World.h"

class btRigidBody;

namespace app {

	namespace gl {
		class Mesh;
	};

namespace tmp {

class BodyFactory {

public:
	static btRigidBody* createBody(const btTransform&, std::shared_ptr<app::gl::Mesh>);
	static void createRoom(const btTransform&, std::shared_ptr<app::gl::Mesh>, app::WorldPtr, std::shared_ptr<btCollisionShape>);

private:
	BodyFactory() {
		// TODO Auto-generated constructor stub

	}
	~BodyFactory() {
		// TODO Auto-generated destructor stub
	}

};

} /* namespace tmp */
} /* namespace app */

#endif /* BODYFACTORY_H_ */
