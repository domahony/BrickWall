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
#include "ObjMesh.h"
#include <btBulletDynamicsCommon.h>

class btCollisionShape;

namespace app {
class World;

namespace gl {
class AppObject;
class ShaderBase;
class Mesh;

class Maze {

public:
	Maze(std::shared_ptr<app::World>);
	void addStraight();
	void addLeftTurn();
	void addRightTurn();
	void addFork();
	void addLeftFork();
	void addRightFork();

private:

	static btQuaternion ZP90;
	static btQuaternion ZN90;
	static btQuaternion XN90;
	static btQuaternion XP90;

	std::shared_ptr<app::gl::ShaderBase> shader;
	app::ObjMesh floor;
	std::shared_ptr<app::gl::Mesh> mesh;
	std::shared_ptr<btCollisionShape> shape;
	std::shared_ptr<app::World> world;
	std::vector<std::shared_ptr<app::gl::AppObject>> slabs;
	btTransform pos;
	btQuaternion dir;
	float width;
	float length;
	btVector3 halfX;
	btVector3 halfY;
	btVector3 halfZ;
	btRigidBody::btRigidBodyConstructionInfo info;
};

} /* namespace gl */
} /* namespace app */

#endif /* MAZE_H_ */
