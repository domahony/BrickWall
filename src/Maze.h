/*
 * Maze.h
 *
 *  Created on: Jul 1, 2015
 *      Author: domahony
 */

#ifndef MAZE_H_
#define MAZE_H_

#include <memory>
#include <vector>

namespace app {
namespace gl {

class Segment;

class Maze {

public:
	Maze();
	void addStraight();
	void addLeftTurn();
	void addRightTurn();
	void addFork();
	void addLeftFork();
	void addRightFork();

private:

};

} /* namespace gl */
} /* namespace app */

#endif /* MAZE_H_ */
