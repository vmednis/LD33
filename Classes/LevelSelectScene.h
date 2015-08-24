#pragma once
#include "cocos2d.h"

class LevelSelectScene : public cocos2d::Scene
{
public:
	//Get called on creation
	virtual bool init();

	//A selector callback
	void levelSelectBack(cocos2d::Ref* pSender);
	void levelSelectPlay(Ref* pSender, std::string levelPackID, int levelID);

	//Generates create function
	CREATE_FUNC(LevelSelectScene);
private:
	cocos2d::Sprite * levelSelectBackgroundSprite;
	cocos2d::MenuItemImage * levelSelectBackItem;
	cocos2d::Vector<cocos2d::MenuItem *> levelSelectItems;
};