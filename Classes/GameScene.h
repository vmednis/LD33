#pragma once
#include "cocos2d.h"
#include "Level.h"
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

	//Level
	Level * levelController = NULL; //TODO: delete this object somewhere

	//Camera control
	void cameraFollow();//Must be called every update
	void cameraReset();//Slides camera back to the begining of the world
	void cameraUpdateMove(float delta);
	void cameraForceBounds();//Don't let the camera exit world
	bool cameraMoveRight = false;
	bool cameraMoveLeft = false;
	bool cameraReseting = false;

	//Stuff to handle game flow
	bool hasGarbageStopedMoving();
	bool hasGarbageStopedOnce = false;
	unsigned int timesShot = 0;
	int gameState;
	
	//Score handling
	unsigned int score;
	void addScore(unsigned int score);
	void setScore(unsigned int score);
	unsigned int getScore() { return this->score; }

	//Event handlers
	void keyboardEventHandlerOnPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * e);
	void keyboardEventHandlerOnReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * e);
	void mouseEventHandlerOnDown(cocos2d::Event * e);
	void mouseEventHandlerOnUp(cocos2d::Event * e);
	void mouseEventHandlerOnMove(cocos2d::Event * e);

	//Shooting functions
	void moveGarbageCan(cocos2d::Vec2 mouseLocation);
	void shootGarbage();

	//Variables
	bool catapultPulling = false;
	bool catapultReady = true;

	//Objects in game world
	std::vector<cocos2d::Sprite *> garbageSprites;
	cocos2d::Sprite * truckSprite;
	cocos2d::Sprite * garbageCanSprite;
	cocos2d::Vec2 catapultLocation;
	cocos2d::DrawNode * debugDrawNode;

	//HUD
	cocos2d::Label * HUDScoreLabel;
};
