#include "MenuScene.h"
#include "LevelSelectScene.h"
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
	menuResizeItem = MenuItemImage::create("menu_resize_almost_small.png", "menu_resize_almost_small_pressed.png", CC_CALLBACK_1(MenuScene::menuResize, this));
	menuResizeItem->setAnchorPoint({ 0.0, 0.0 });
	menuResizeItem->setPosition(180, 504); //180, 360
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
	auto scene = LevelSelectScene::create();
	Director::getInstance()->replaceScene(scene);
}

void MenuScene::menuResize(Ref* pSender)
{
	auto glview = Director::getInstance()->getOpenGLView();
	if (currentResolutionSizeID == 0)
	{
		glview->setFrameSize(smallResolutionSize.width, smallResolutionSize.height);
		menuResizeItem->setNormalImage(Sprite::create("menu_resize_small.png"));
		menuResizeItem->setSelectedImage(Sprite::create("menu_resize_small_pressed.png"));
	}
	else if (currentResolutionSizeID == 1)
	{
		glview->setFrameSize(mediumResolutionSize.width, mediumResolutionSize.height);
		menuResizeItem->setNormalImage(Sprite::create("menu_resize_medium.png"));
		menuResizeItem->setSelectedImage(Sprite::create("menu_resize_medium_pressed.png"));
	}
	else if (currentResolutionSizeID == 2)
	{
		glview->setFrameSize(almostLargeResolutionSize.width, almostLargeResolutionSize.height);
		menuResizeItem->setNormalImage(Sprite::create("menu_resize_almost_large.png"));
		menuResizeItem->setSelectedImage(Sprite::create("menu_resize_almost_large_pressed.png"));
	}
	else if (currentResolutionSizeID == 3)
	{
		glview->setFrameSize(largeResolutionSize.width, largeResolutionSize.height);
		menuResizeItem->setNormalImage(Sprite::create("menu_resize_large.png"));
		menuResizeItem->setSelectedImage(Sprite::create("menu_resize_large_pressed.png"));
	}
	else if (currentResolutionSizeID == 4)
	{
		glview->setFrameSize(almostSmallResolutionSize.width, almostSmallResolutionSize.height);
		menuResizeItem->setNormalImage(Sprite::create("menu_resize_almost_small.png"));
		menuResizeItem->setSelectedImage(Sprite::create("menu_resize_almost_small_pressed.png"));
	}
	if (currentResolutionSizeID == 4) currentResolutionSizeID = 0; else currentResolutionSizeID++;
	glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
}