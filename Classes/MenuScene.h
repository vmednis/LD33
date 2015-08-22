#pragma once
#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
	//Returns a scene with this layer as a child
	static cocos2d::Scene* createScene();

	//Get called on creation
	virtual bool init();

	//A selector callback
	void menuStart(cocos2d::Ref* pSender);

	//Generates create function
	CREATE_FUNC(MenuScene);
private:
	cocos2d::Sprite * menuBackgroundSprite;
};