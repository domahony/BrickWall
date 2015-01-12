/*
 * Renderer.h
 *
 *  Created on: Dec 30, 2014
 *      Author: domahony
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <glm/glm.hpp>
#include "GroundGL.h"
#include "Body.h"
#include "RenderBody.h"

namespace app {
namespace gl {

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void render(GroundGL&);
	void render(Body*);
	void render(const app::RenderBody&);

private:
	glm::mat4 view;
	glm::mat4 proj;
};

} /* namespace gl */
} /* namespace app */

#endif /* RENDERER_H_ */
