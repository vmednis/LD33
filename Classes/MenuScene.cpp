#include "MenuScene.h"
#include "GameScene.h"
#include "GameConfig.h"

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

	currentResolutionSizeID = 0;

	//Menu
	Vector<MenuItem*> menuItems;
	auto menuStartItem = MenuItemImage::create("menu_start.png", "menu_start_pressed.png", CC_CALLBACK_1(MenuScene::menuStart, this));
	menuStartItem->setAnchorPoint({ 0.0, 0.0 });
	menuStartItem->setPosition(180, 720);
	menuItems.pushBack(menuStartItem);
	menuResizeItem = MenuItemImage::create("menu_start.png", "menu_start_pressed.png", CC_CALLBACK_1(MenuScene::menuResize, this));
	menuResizeItem->setAnchorPoint({ 0.0, 0.0 });
	menuResizeItem->setPosition(180, 360);
	menuItems.pushBack(menuResizeItem);
	auto menu = Menu::createWithArray(menuItems);
	menu->setAnchorPoint({ 0.0, 0.0 });
	menu->setPosition(0, 0);
	addChild(menu);

	CCLOG("MenuScene initialized successfully");
	return true;
}

void MenuScene::menuStart(Ref* pSender)
{
	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::menuResize(Ref* pSender)
{
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	auto scene = MenuScene::create();
	if (currentResolutionSizeID == 4) currentResolutionSizeID = 0; else currentResolutionSizeID++;

	if (currentResolutionSizeID == 1)
	{
		glview->setFrameSize(smallResolutionSize.width, smallResolutionSize.height);
	}
	else if (currentResolutionSizeID == 2)
	{
		glview->setFrameSize(mediumResolutionSize.width, mediumResolutionSize.height);
	}
	else if (currentResolutionSizeID == 3)
	{
		glview->setFrameSize(almostLargeResolutionSize.width, almostLargeResolutionSize.height);
	}
	else if (currentResolutionSizeID == 4)
	{
		glview->setFrameSize(largeResolutionSize.width, largeResolutionSize.height);
	}
	else if (currentResolutionSizeID == 0)
	{
		glview->setFrameSize(almostSmallResolutionSize.width, almostSmallResolutionSize.height);
	}

	scene->setCurrentResolutionSizeID(currentResolutionSizeID);
	director->replaceScene(scene);
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
}

void MenuScene::setCurrentResolutionSizeID(char newID)
{
	currentResolutionSizeID = newID;
	//menuResizeItem->setNormalImage(Sprite::create("menu_start.png"));
	//menuResizeItem->setSelectedImage(Sprite::create("menu_start_pressed.png"));
}