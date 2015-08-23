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
	//Node for use with camera
	cocos2d::Node * world;

	//Event handlers
	void keyboardEventHandlerOnPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * e);
	void keyboardEventHandlerOnReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * e);
	void mouseEventHandlerOnDown(cocos2d::Event * e);
	void mouseEventHandlerOnUp(cocos2d::Event * e);
	void mouseEventHandlerOnMove(cocos2d::Event * e);

	//Helper functions
	void moveTarget(cocos2d::Vec2 mouseLocation);

	//Variables
	bool catapultPulling = false;
	bool catapultReady = true;

	//Objects in game world
	std::vector<cocos2d::Sprite *> groundSprites;
	cocos2d::Sprite * truckSprite;
	cocos2d::Sprite * garbageCanSprite;
	cocos2d::Sprite * target;
	cocos2d::Vec2 catapultLocation;
};
