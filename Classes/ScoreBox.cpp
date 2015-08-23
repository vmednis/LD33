#include "ScoreBox.h"

USING_NS_CC;

ScoreBox::ScoreBox(Vec2 location, Vec2 size, unsigned int pointsWorth)
{
	this->location = location;
	this->size = size;
	this->pointsWorth = pointsWorth;
}

ScoreBox::ScoreBox(float x, float y, float width, float height, unsigned int pointsWorth)
{
	this->location = {x, y};
	this->size = {width, height};
	this->pointsWorth = pointsWorth;
}

ScoreBox::ScoreBox()
{
	this->location = { 0, 0 };
	this->size = { 0, 0 };
	this->pointsWorth = 0;
}