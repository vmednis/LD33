#pragma once
#include "cocos2d.h"

class ScoreBox
{
public:
	//Constructos
	ScoreBox(cocos2d::Vec2 location, cocos2d::Vec2 size, unsigned int pointsWorth);
	ScoreBox(float x, float y, float width, float height, unsigned int pointsWorth);
	ScoreBox();

	//setters and getters
	void setLocation(cocos2d::Vec2 location) { this->location = location; }
	cocos2d::Vec2 getLocation() { return this->location; }
	void setSize(cocos2d::Vec2 size) { this->size = size; }
	cocos2d::Vec2 getSize() { return this->size; }
	void setPointsWorth(unsigned int pointsWorth) { this->pointsWorth = pointsWorth; }
	unsigned int getPointsWorth() { return this->pointsWorth; }

private:
	cocos2d::Vec2 location;
	cocos2d::Vec2 size;
	unsigned int pointsWorth;
};