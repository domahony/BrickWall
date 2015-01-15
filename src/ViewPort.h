/*
 * ViewPort.h
 *
 *  Created on: Jan 14, 2015
 *      Author: domahony
 */

#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <glm/glm.hpp>

namespace app {

class ViewPort {
public:
	ViewPort();
	virtual ~ViewPort();
	glm::mat4 getProjMatrix() const {
		return proj;
	}
private:
	glm::mat4 proj;
};

} /* namespace app */

#endif /* VIEWPORT_H_ */
