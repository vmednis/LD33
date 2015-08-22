#pragma once
#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
	//Get called on creation
	virtual bool init();

	//A selector callback
	void menuStart(cocos2d::Ref* pSender);
	void menuResize(cocos2d::Ref* pSender);

	//Generates create function
	CREATE_FUNC(MenuScene);
private:
	cocos2d::Sprite * menuBackgroundSprite;
	cocos2d::MenuItemImage * menuResizeItem;
	char currentResolutionSizeID;
};