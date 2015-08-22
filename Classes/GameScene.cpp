#include <vector>
#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* GameScene::createScene()
{
	//Create and return scene with instance of this class attached as a child
	auto scene = Scene::createWithPhysics();
	//Enable physics debug
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	//Init super class
	if (!Layer::init())
	{
		return false;
	}

	//Ground
	std::vector<Node *> groundNodes;
	for (unsigned int i = 0; i < 10; i++)
	{
		auto groundPhysicsBody = PhysicsBody::createBox({ 128, 128 }, PhysicsMaterial(), { 64, 64 });
		groundPhysicsBody->setDynamic(false);
		auto node = Node::create();
		node->setPhysicsBody(groundPhysicsBody);
		node->setPosition(Vec2(i * 128, 0));
		addChild(node);
		groundNodes.push_back(node);
	}

	//Enable update function
	scheduleUpdate();

	CCLOG("Scene inited successfully");
	return true;
}

void GameScene::update(float delta)
{

}

