/*
 * ViewPort.cpp
 *
 *  Created on: Jan 14, 2015
 *      Author: domahony
 */

#include "ViewPort.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace app {

ViewPort::ViewPort() : proj(glm::perspective(75.0f, 800.0f / 600.0f, 1.0f, 100.0f))
{

}

ViewPort::~ViewPort() {
	// TODO Auto-generated destructor stub
}

} /* namespace app */
