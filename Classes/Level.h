#pragma once
#include "cocos2d.h"
#include "ScoreBox.h"
#include <vector>

class Level
{
public:
	Level(cocos2d::Node * world, float size);

	//Loads level from a file into levelbuilder class
	void loadLevel(const std::string filename);

	//Clears the level
	void clearLevel();

	//Set or get size of the level
	void setSize(float size) { this->size = size; }
	float getSize() { return size; }

	//Set or get the world
	void setWorld(cocos2d::Node * world) { this->world = world; }
	cocos2d::Node * getWorld() { return world; }

	//Add or get scoreboxes
	void addScoreBox(ScoreBox box) { scoreBoxes.push_back(box); }
	std::vector<ScoreBox> getScoreBoxes() { return scoreBoxes; }
private:
	std::vector<cocos2d::Node *> loadedObjectNodes;
	std::vector<ScoreBox> scoreBoxes;
	float size;
	cocos2d::Node * world;
};

struct LoadableObject
{
	std::string name;
	float x;
	float y;
};