#include "ScoreHandler.h"
#include "GameConfig.h"

USING_NS_CC;

ScoreHandler::ScoreHandler(Node * scene)
{
	this->score = 0;
	//Create HUD label
	scoreLabel = Label::createWithBMFont("fonts/OpenSans-Bold.fnt", "0");
	scoreLabel->setAnchorPoint({ 0.0, 1.0 });
	scoreLabel->setPosition({ 0.0, designResolutionSize.height });
	scene->addChild(scoreLabel, RenderOrder::HUDForeground);
}

void ScoreHandler::setScore(unsigned int score)
{
	this->score = score;
	//Update HUD
	scoreLabel->setString(std::to_string(score));
}

void ScoreHandler::addScore(unsigned int score)
{
	setScore(getScore() + score);
}