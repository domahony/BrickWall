/*
 * MovableObject.h
 *
 *  Created on: Jul 29, 2015
 *      Author: domahony
 */

#ifndef MOVABLEOBJECT_H_
#define MOVABLEOBJECT_H_

#include "AppObject.h"

namespace app {
namespace gl {

class MovableObject: public AppObject {
public:
	MovableObject(std::shared_ptr<Mesh>, std::shared_ptr<btCollisionShape>, const btTransform& pos);

	virtual ~MovableObject();
};

} /* namespace gl */
} /* namespace app */

#endif /* MOVABLEOBJECT_H_ */
