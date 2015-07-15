/*
 * Maze.cpp
 *
 *  Created on: Jul 1, 2015
 *      Author: domahony
 */

#include "Maze.h"
#include "Slab.h"
#include "ShaderBase.h"

namespace app {
namespace gl {

Maze::
Maze(WorldPtr world, ShaderPtr shader, const int& length, const int& width)
{

	std::shared_ptr<Slab> floor(std::make_shared<Slab>(50.f, shader));
	world->addRigidBody(floor->getRigidBody().get());
	slabs.push_back(floor);
}

} /* namespace gl */
} /* namespace app */
