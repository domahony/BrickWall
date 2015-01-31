/*
 * RenderBody.h
 *
 *  Created on: Jan 12, 2015
 *      Author: domahony
 */

#ifndef OBJMESH_H_
#define OBJMESH_H_

/*
#include "types.h"
#include <iostream>
#include <bullet/LinearMath/btMotionState.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include <vector>
*/
#include <memory>
#include "Mesh.h"

namespace app {

class ObjMesh : public app::gl::Mesh {

public:
	ObjMesh(const std::string& fname, std::shared_ptr<app::gl::Shader>);
	virtual ~ObjMesh();

};

} /* namespace app */

#endif /* OBJMESH_H_ */
