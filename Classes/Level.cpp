#include "Level.h"
#include "GameConfig.h"

USING_NS_CC;

Level::Level(cocos2d::Node * world, cocos2d::Vec2 size)
{

}

void Level::loadLevel(std::string filename)
{
	std::string fileContents = FileUtils::getInstance()->getStringFromFile(filename);
	std::string entityType = fileContents.substr(0, fileContents.find(","));
	std::string entityCoords = fileContents.substr(fileContents.find(",") + 1);
	std::string entityX = entityCoords.substr(0, entityCoords.find(","));
	std::string entityY = entityCoords.substr(entityCoords.find(",") + 1);
}

void Level::clearLevel()
{

}