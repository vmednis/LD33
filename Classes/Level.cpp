#include "GlobalVariables.h"
#include "Level.h"
#include "GameConfig.h"

USING_NS_CC;

Level::Level(cocos2d::Node * world)
{
	this->world = world;
	this->size = 0;
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
		std::string backgroundSpritePath = g_currentLevelPack;
		backgroundSpritePath.append("/sprites/background.png");
		node = Sprite::create(backgroundSpritePath);
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
			auto groundPhysicsBody = PhysicsBody::createBox({ 528.0f * groundBlocks, 120.0f }, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { (528.0f * (groundBlocks - 1))/2, -60.0f });
			groundPhysicsBody->setDynamic(false);
			std::string streetSpritePath = g_currentLevelPack;
			streetSpritePath.append("/sprites/street.png");
			node = Sprite::create(streetSpritePath);
			node->setPhysicsBody(groundPhysicsBody);
		}
		else
		{
			std::string grassSpritePath = g_currentLevelPack;
			grassSpritePath.append("/sprites/grass.png");
			node = Sprite::create(grassSpritePath);
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
		CCLOG("Loading %s at coords %f, %f", object.name.c_str(), object.x, object.y);
		if (object.name == "fence")
		{
			//Create sprite with physics box
			auto physicsBody = PhysicsBody::createBox({ 24, 96 }, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { 0, -12 });
			physicsBody->setDynamic(false);
			std::string fenceSpritePath = g_currentLevelPack;
			fenceSpritePath.append("/sprites/fence.png");
			auto sprite = Sprite::create(fenceSpritePath);
			sprite->setPhysicsBody(physicsBody);
			sprite->setAnchorPoint({ 0.0, 0.0 });
			sprite->setPosition({ object.x, object.y });
			world->addChild(sprite, RenderOrder::Object);
			loadedObjectNodes.push_back(sprite);
			//Create score box
			addScoreBox(ScoreBox(object.x - 48, object.y, 120, 120, pointsAwardedFence));
		}
		else if (object.name == "daisy")
		{
			std::string spritePath = g_currentLevelPack;
			spritePath.append("/sprites/daisy.png");
			auto sprite = Sprite::create(spritePath);
			sprite->setAnchorPoint({ 0.0, 0.0 });
			sprite->setPosition({ object.x, object.y });
			world->addChild(sprite, RenderOrder::Object);
			loadedObjectNodes.push_back(sprite);
			//Create score box
			addScoreBox(ScoreBox(object.x - 24, object.y, 62, 26, pointsAwardedDaisy));
		}
		else if (object.name == "sunflower")
		{
			std::string spritePath = g_currentLevelPack;
			spritePath.append("/sprites/sunflower.png");
			auto sprite = Sprite::create(spritePath);
			sprite->setAnchorPoint({ 0.0, 0.0 });
			sprite->setPosition({ object.x, object.y });
			world->addChild(sprite, RenderOrder::Object);
			loadedObjectNodes.push_back(sprite);
			//Create score box
			addScoreBox(ScoreBox(object.x - 16, object.y, 86, 165, pointsAwardedSunflower));
		}
		else if (object.name == "tulip_garden")
		{
			std::string spritePath = g_currentLevelPack;
			spritePath.append("/sprites/tulip_garden.png");
			auto sprite = Sprite::create(spritePath);
			sprite->setAnchorPoint({ 0.0, 0.0 });
			sprite->setPosition({ object.x, object.y });
			world->addChild(sprite, RenderOrder::Object);
			loadedObjectNodes.push_back(sprite);
			//Create score box
			addScoreBox(ScoreBox(object.x, object.y, 200, 34, pointsAwardedTulipGarden));
		}
		else if (object.name == "garbage_can")
		{
			//Create sprite with physics box
			auto physicsBody = PhysicsBody::createBox({ 60, 120 }, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { -6, 0 });
			physicsBody->setDynamic(false);
			std::string spritePath = g_currentLevelPack;
			spritePath.append("/sprites/garbage_can.png");
			auto sprite = Sprite::create(spritePath);
			sprite->setPhysicsBody(physicsBody);
			sprite->setAnchorPoint({ 0.0, 0.0 });
			sprite->setPosition({ object.x, object.y });
			world->addChild(sprite, RenderOrder::Object);
			loadedObjectNodes.push_back(sprite);
			//Create score box
			addScoreBox(ScoreBox(object.x - 32, object.y, 136, 152, pointsAwardedGarbageCan));
		}
		else if (object.name == "house")
		{
			//Create sprite with physics box
			auto physicsBody = PhysicsBody::createBox({ 300, 180 }, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { 0, -45 });
			Vec2 points[] = { {0, 0}, {30, 90}, {330, 90}, {360, 0} };
			physicsBody->addShape(PhysicsShapePolygon::create(points, 4, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { -180, 45 }));
			physicsBody->setDynamic(false);
			std::string spritePath = g_currentLevelPack;
			spritePath.append("/sprites/house.png");
			auto sprite = Sprite::create(spritePath);
			sprite->setPhysicsBody(physicsBody);
			sprite->setAnchorPoint({ 0.0, 0.0 });
			sprite->setPosition({ object.x, object.y });
			world->addChild(sprite, RenderOrder::Object);
			loadedObjectNodes.push_back(sprite);
			//Create score box
			addScoreBox(ScoreBox(object.x - 32, object.y, 424, 302, pointsAwardedHouse));
		}
		else if (object.name == "two_story_house")
		{
			//Create sprite with physics box
			auto physicsBody = PhysicsBody::createBox({ 300, 240 }, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { 0, -70 });
			Vec2 points[] = { { 0, 0 },{ 30, 90 },{ 330, 90 },{ 360, 0 } };
			physicsBody->addShape(PhysicsShapePolygon::create(points, 4, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { -180, 50 }));
			physicsBody->addShape(PhysicsShapeBox::create({ 60, 108 }, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), {-84, 135}));
			physicsBody->setDynamic(false);
			std::string spritePath = g_currentLevelPack;
			spritePath.append("/sprites/two_story_house.png");
			auto sprite = Sprite::create(spritePath);
			sprite->setPhysicsBody(physicsBody);
			sprite->setAnchorPoint({ 0.0, 0.0 });
			sprite->setPosition({ object.x, object.y });
			world->addChild(sprite, RenderOrder::Object);
			loadedObjectNodes.push_back(sprite);
			//Create score box
			addScoreBox(ScoreBox(object.x - 32, object.y, 424, 412, pointsAwardedTwoStoryHouse));
			addScoreBox(ScoreBox(object.x + 66, object.y + 380, 60, 32, pointsAwardedChimneyBonus));
		}
		else if (object.name == "garage")
		{
			//Create sprite with physics box
			auto physicsBody = PhysicsBody::createBox({ 240, 156 }, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { 60, -18 });
			physicsBody->addShape(PhysicsShapeBox::create({ 360, 36 }, PhysicsMaterial(physicsDensityObjects, physicsRestitutionObjects, physicsFrictionObjects), { 0, 78 }));
			physicsBody->setDynamic(false);
			std::string spritePath = g_currentLevelPack;
			spritePath.append("/sprites/garage.png");
			auto sprite = Sprite::create(spritePath);
			sprite->setPhysicsBody(physicsBody);
			sprite->setAnchorPoint({ 0.0, 0.0 });
			sprite->setPosition({ object.x, object.y });
			world->addChild(sprite, RenderOrder::Object);
			loadedObjectNodes.push_back(sprite);
			//Create score box
			addScoreBox(ScoreBox(object.x - 32, object.y, 424, 224, pointsAwardedGarage));
			addScoreBox(ScoreBox(object.x, object.y, 120, 156, pointsAwardedInsideGarageBonus));
		}
		else
		{
			CCLOG("Failed to create object %s! Object doesn't exist!", object.name.c_str());
		}
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
	backgroundSprites.clear();
	//Remove ground sprites
	for (Node * node : groundSprites)
	{
		node->removeFromParentAndCleanup(true);
	}
	groundSprites.clear();
	//Remove loaded objects
	for (Node * node : loadedObjectNodes)
	{
		node->removeFromParentAndCleanup(true);
	}
	loadedObjectNodes.clear();
	//Remove world edge border
	if (worldBorderNode != NULL)
	{
		worldBorderNode->removeFromParentAndCleanup(true);
	}
	//Remove scoreboxes
	scoreBoxes.clear();
}