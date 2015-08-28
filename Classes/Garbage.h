#pragma once
#include "cocos2d.h"
#include "ScoreHandler.h"
#include "Level.h"

class GarbageClass
{
public:
	//Creates the piece of garbage
	void createGarbage(cocos2d::Node * world, cocos2d::Vec2 garbageCanPosition, cocos2d::Vec2 velocity);
	//Returns a pointer to the sprite
	cocos2d::Sprite * getSprite() { return this->sprite; }
	//Checks if garbage has stoped moving
	bool hasStopedMoving();
	//Set the score handler
	void setScoreHandler(ScoreHandler * scoreHandler) { this->scoreHandler = scoreHandler; }
	void setLevelController(Level * levelController) { this->levelController = levelController; }
private:
	//Some handlers and controllers
	ScoreHandler * scoreHandler;
	Level * levelController;
	//Gets called when garbagestops moving used to display shiny graphic or something
	void stopedMoving();
	//Sprite of the piece of garbage
	cocos2d::Sprite * sprite;
	//Some vars for hasStopedMoving()
	bool notMoving = false;
	bool waitingForSafeTime = false;
};