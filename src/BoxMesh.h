/*
 * RenderBody.h
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#ifndef BOXMESH_H_
#define BOXMESH_H_

#include "types.h"
#include <iostream>
#include <bullet/LinearMath/btMotionState.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include <vector>
#include "Mesh.h"

namespace app {

class BoxMesh : public app::gl::Mesh {
public:
	BoxMesh();
	virtual ~BoxMesh();

};

} /* namespace app */

#endif /* BOXMESH_H_ */
