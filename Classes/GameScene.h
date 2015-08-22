#pragma once
#include "cocos2d.h"
#include <vector>

class GameScene : public cocos2d::Layer
{
public:
	//Returns a scene with this layer as a child
	static cocos2d::Scene* createScene();
	
	//Get called on creation
	virtual bool init();

	//Gets called eery update
	void update(float delta);

	//Generates create function
	CREATE_FUNC(GameScene);
private:
	std::vector<cocos2d::Sprite *> groundNodes;
};