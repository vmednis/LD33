#pragma once
#include "cocos2d.h"

class Garbage
{
public:
	cocos2d::Sprite * getSprite() { return this->sprite; }
	bool hasStopedMoving();
private:
	cocos2d::Sprite * sprite;
	bool notMoving;
};