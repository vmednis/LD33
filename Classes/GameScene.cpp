#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* GameScene::createScene()
{
	//Create and return scene with instance of this class attached as a child
	auto scene = Scene::createWithPhysics();
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



	//Enable update function
	scheduleUpdate();

	CCLOG("Scene inited successfully");
	return true;
}

void GameScene::update(float delta)
{

}

