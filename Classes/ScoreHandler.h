#pragma once
#include "cocos2d.h"

class ScoreHandler
{
public:
	ScoreHandler(cocos2d::Node * scene);
	void setScore(unsigned int score);
	void addScore(unsigned int score);
	unsigned int getScore() { return this->score; }
private:
	cocos2d::Label * scoreLabel;
	unsigned int score = 0;
};