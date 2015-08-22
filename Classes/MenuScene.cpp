#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

cocos2d::Scene* MenuScene::createScene()
{
	//Create and return scene with instance of this class attached as a child
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	//Init super class
	if (!Layer::init())
	{
		return false;
	}

	//Background
	menuBackgroundSprite = Sprite::create("menu_background.png");
	menuBackgroundSprite->setAnchorPoint({ 0.0, 0.0 });
	menuBackgroundSprite->setPosition(0, 0);
	addChild(menuBackgroundSprite);

	//Menu
	auto menuStartItem = MenuItemImage::create("menu_start.png", "menu_start_pressed.png", CC_CALLBACK_1(MenuScene::menuStart, this));
	menuStartItem->setAnchorPoint({ 0.0, 0.0 });
	auto menu = Menu::create(menuStartItem, NULL);
	menu->setAnchorPoint({ 0.0, 0.0 });
	menu->setPosition(180, 720);
	addChild(menu);

	CCLOG("MenuScene initialized successfully");
	return true;
}

void MenuScene::menuStart(Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}