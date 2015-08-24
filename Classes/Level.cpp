#include "Level.h"
#include "GameConfig.h"

USING_NS_CC;

Level::Level(cocos2d::Node * world)
{
	this->world = world;
}

void Level::loadLevel(std::string filename)
{
	//Read whole file contents
	std::vector<LoadableObject> loadableObjects;
	std::string fileContents = FileUtils::getInstance()->getStringFromFile(filename);
	//Read world size
	std::string worldSizeString = fileContents.substr(0, fileContents.find("\n"));
	float worldSize = atof(worldSizeString.c_str());
	if (worldSize < designResolutionSize.width) worldSize = designResolutionSize.width;
	setSize(worldSize);
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
		objectDefinition = objectDefinition.substr(objectDefinition.find(",") + 1);
		std::string objectCoordX = objectDefinition.substr(0, objectDefinition.find(","));
		objectDefinition = objectDefinition.substr(objectDefinition.find(",") + 1);
		std::string objectCoordY = objectDefinition; //Only this is left

		//Fillup LoadableObject
		LoadableObject object;
		object.name = objectName;
		object.x = atof(objectCoordX.c_str());
		object.y = atof(objectCoordY.c_str());

		//Add the LoadableObject to the vector
		loadableObjects.push_back(object);
	}

	//Background
	for (unsigned int i = 0; i < ((unsigned int)atof(worldSizeString.c_str()) / designResolutionSize.width) + 1; i++)
	{
		Sprite * node;
		node = Sprite::create("uptown/sprites/background.png");
		node->setAnchorPoint({ 0.0, 0.0 });
		node->setPosition({ i * designResolutionSize.width, 0 });
		world->addChild(node, RenderOrder::Background);
		backgroundSprites.push_back(node);
	}

	//Ground
	unsigned int groundBlocks = ((unsigned int)atof(worldSizeString.c_str()) / 528) + 1;
	if (groundBlocks < designResolutionSize.width / 528) groundBlocks = (designResolutionSize.width / 528) + 1;
	for (unsigned int i = 0; i < groundBlocks; i++)
	{
		Sprite * node;
		if (i == 0)
		{
			auto groundPhysicsBody = PhysicsBody::createBox({ 528.0f * groundBlocks, 120.0f }, PhysicsMaterial(1.0f, 0.0f, 0.9f), { (528.0f * (groundBlocks - 1))/2, -60.0f });
			groundPhysicsBody->setDynamic(false);
			node = Sprite::create("uptown/sprites/street.png");
			node->setPhysicsBody(groundPhysicsBody);
		}
		else
		{
			node = Sprite::create("uptown/sprites/grass.png");
		}
		node->setAnchorPoint({ 0.0, 0.0 });
		node->setPosition(Vec2(i * 528, 0));
		world->addChild(node, RenderOrder::Ground);
		groundSprites.push_back(node);
	}

	//World edge
	auto worldBorderPhysicsBody = PhysicsBody::createEdgeBox({ getSize(), worldHeight }, PHYSICSBODY_MATERIAL_DEFAULT, 1.0f, { getSize() / 2, worldHeight / 2 });
	worldBorderNode = Node::create();
	worldBorderNode->setPhysicsBody(worldBorderPhysicsBody);
	world->addChild(worldBorderNode);

	//Create the objects that were read in the world
	for (LoadableObject object : loadableObjects)
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
	//Remove background sprites
	for (Node * node : backgroundSprites)
	{
		node->removeFromParentAndCleanup(true);
	}
	//Remove ground sprites
	for (Node * node : groundSprites)
	{
		node->removeFromParentAndCleanup(true);
	}
	//Remove loaded objects
	for (Node * node : loadedObjectNodes)
	{
		node->removeFromParentAndCleanup(true);
	}
	//Remove world edge border
	worldBorderNode->removeFromParentAndCleanup(true);
}