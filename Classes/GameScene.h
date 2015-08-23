#pragma once
#include "cocos2d.h"
#include <vector>

class GameScene : public cocos2d::Scene
{
public:
	//Get called on creation
	virtual bool init();

	//Gets called eery update
	void update(float delta);

	//Generates create function
	CREATE_FUNC(GameScene);
private:
	std::vector<cocos2d::Sprite *> groundSprites;
	cocos2d::Sprite * truckSprite;
	cocos2d::Sprite * garbageCanSprite;
	cocos2d::Sprite * target;
	cocos2d::Vec2 catapultLocation;
};