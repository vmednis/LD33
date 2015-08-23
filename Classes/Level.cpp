#include "Level.h"
#include "GameConfig.h"

USING_NS_CC;

Level::Level(cocos2d::Node * world, float size)
{
	this->world = world;
	this->size = size;
}

void Level::loadLevel(std::string filename)
{
	//Read object from file into the vector
	std::vector<LoadableObject> loadableObjects;
	std::string fileContents = FileUtils::getInstance()->getStringFromFile(filename);
	//Read world size
	std::string worldSizeString = fileContents.substr(0, fileContents.find("\n"));
	setSize(atof(worldSizeString.c_str()));
	fileContents = fileContents.substr(fileContents.find("\n") + 1);
	//Read object count
	std::string objectCountString = fileContents.substr(0, fileContents.find("\n"));
	unsigned int objectCount = atoi(objectCountString.c_str());
	fileContents = fileContents.substr(fileContents.find("\n") + 1);
	//Read object definitions
	for (unsigned int i = 0; i < objectCount; i++)
	{
		//Split of object definition from the remainging level data
		std::string objectDefinition = fileContents.substr(0, fileContents.find("\n"));
		fileContents = fileContents.substr(fileContents.find("\n") + 1);
		//Split up object data in indvidual variables
		std::string objectName = objectDefinition.substr(0, objectDefinition.find(","));
		objectDefinition = objectDefinition.substr(objectDefinition.find(",")+1);
		std::string objectCoordX = objectDefinition.substr(0, objectDefinition.find(","));
		objectDefinition = objectDefinition.substr(objectDefinition.find(",")+1);
		std::string objectCoordY = objectDefinition;//Only this is left

		//Fillup LoadableObject
		LoadableObject object;
		object.name = objectName;
		object.x = atof(objectCoordX.c_str());
		object.y = atof(objectCoordY.c_str());

		//Add the LoadableObject to the vector
		loadableObjects.push_back(object);
	}

	//Create the object that were read in the world
	for(LoadableObject object : loadableObjects)
	{ 
		CCLOG("Loading %s at coords %f %f", object.name.c_str(), object.x, object.y);
		/*
		*if(object.name == "Something")
		*{
		*	createSomething();
		*	loadedObjectNodes.push_back(somethingNode);
		*}
		*else if(object.name == "somethingelse")
		*{
		*	..
		*}
		*	...
		*/
		//!!! Always be sure to add the objects node to loadedObjectsNodes vector
	}
}

void Level::clearLevel()
{
	for (Node * node : loadedObjectNodes)
	{
		node->removeFromParentAndCleanup(true);
	}
}