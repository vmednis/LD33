#pragma once
#include "cocos2d.h"

class Level
{
public:
	Level(cocos2d::Node * world, cocos2d::Vec2 size);

	//Loads level from a file into levelbuilder class
	void loadLevel(const std::string filename);
	
	//Build the level, adds everything as children to world
	void buildLevel();
	
	//Clears the level
	void clearLevel();

	//Set or get size of the level
	void setSize(cocos2d::Vec2 size) { this->size = size; }
	cocos2d::Vec2 getSize() { return size; }
	
	//Set or get the world
	void setWorld(cocos2d::Node * world) { this->world = world; }
	cocos2d::Node * getWorld() { return world; }
private:
	cocos2d::Vec2 size;
	cocos2d::Node * world;
};