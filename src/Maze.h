/*
 * Maze.h
 *
 *  Created on: Jul 1, 2015
 *      Author: domahony
 */

#ifndef MAZE_H_
#define MAZE_H_

#include "World.h"
#include "ShaderBase.h"
#include <memory>
#include <vector>

namespace app {
namespace gl {

class Slab;

class Maze {

public:
	Maze(WorldPtr w, ShaderPtr s, const int& length, const int& width);
private:
	std::vector<std::shared_ptr<Slab>> slabs;
};

} /* namespace gl */
} /* namespace app */

#endif /* MAZE_H_ */
