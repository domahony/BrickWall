/*
 * BodyFactory.h
 *
 *  Created on: Jan 15, 2015
 *      Author: domahony
 */

#ifndef BODYFACTORY_H_
#define BODYFACTORY_H_

class btRigidBody;

namespace app {
namespace tmp {

class BodyFactory {

public:
	static btRigidBody* createBody();

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
