/*
 * Slab.cpp
 *
 *  Created on: Jul 13, 2015
 *      Author: domahony
 */

#include "Slab.h"
#include "Shader2.h"
#include "Mesh.h"
#include <BulletDynamics/btBulletDynamicsCommon.h>

namespace app {
namespace gl {

std::shared_ptr<app::gl::ShaderBase> Slab::shader(new app::gl::Shader2());
app::ObjMesh Slab::floor("./media/plane.dat", shader, 1);
std::shared_ptr<app::gl::Mesh> Slab::mesh(floor.getMesh());
std::shared_ptr<btCollisionShape> Slab::shape(floor.getShape<btBvhTriangleMeshShape>());

Slab::
Slab(const btTransform& pos) : AppObject(mesh, shape, pos), width(0), height(0)
{

}

Slab::
~Slab()
{

}

} /* namespace gl */
} /* namespace app */
