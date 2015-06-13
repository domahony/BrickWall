/*
 * Axis.h
 *
 *  Created on: Jun 13, 2015
 *      Author: domahony
 */

#ifndef AXIS_H_
#define AXIS_H_

namespace app {
namespace gl {

class Axis {
public:
	Axis();

	~Axis() {
		// TODO Auto-generated destructor stub
	}

	void render();
private:
	GLuint vao;
};

} /* namespace gl */
} /* namespace app */

#endif /* AXIS_H_ */
