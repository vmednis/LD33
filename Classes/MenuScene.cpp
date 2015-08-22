#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

bool MenuScene::init()
{
	//Init super class
	if (!Scene::init())
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
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(scene);
}