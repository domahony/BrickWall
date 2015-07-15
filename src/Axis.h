/*
 * Axis.h
 *
 *  Created on: Jun 13, 2015
 *      Author: domahony
 */

#ifndef AXIS_H_
#define AXIS_H_

#include <memory>
#include "types.h"
#include "Camera.h"

namespace app {
namespace gl {

class ShaderBase;

class Axis {
public:
	Axis();

	~Axis() {
		// TODO Auto-generated destructor stub
	}

	void render(const app::CameraPtr) const;
private:
	std::shared_ptr<ShaderBase> shader;
	GLuint vao;
};

} /* namespace gl */
} /* namespace app */

#endif /* AXIS_H_ */
