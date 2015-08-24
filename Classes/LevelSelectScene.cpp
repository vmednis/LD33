#include "GlobalVariables.h"
#include "LevelSelectScene.h"
#include "MenuScene.h"
#include "GameScene.h"

USING_NS_CC;

bool LevelSelectScene::init()
{
	//Init super class
	if (!Scene::init())
	{
		return false;
	}

	//Background
	levelSelectBackgroundSprite = Sprite::create("level_select_background.png");
	levelSelectBackgroundSprite->setAnchorPoint({ 0.0, 0.0 });
	levelSelectBackgroundSprite->setPosition(0, 0);
	addChild(levelSelectBackgroundSprite);
	
	//Back button
	levelSelectBackItem = MenuItemImage::create("back_button.png", "back_button_pressed.png", CC_CALLBACK_1(LevelSelectScene::levelSelectBack, this));
	levelSelectBackItem->setAnchorPoint({ 0.0, 0.0 });
	levelSelectBackItem->setPosition(120, 936);
	auto topMenu = Menu::create(levelSelectBackItem, NULL);
	topMenu->setAnchorPoint({ 0.0, 0.0 });
	topMenu->setPosition(0, 0);
	addChild(topMenu);

	//Levels
	for (unsigned int i = 0; i < 40; i++)
	{
		unsigned int iRel = i % 10;
		MenuItemImage * node;
		if (i < 10)
		{
			std::string filename = "uptown_";
			filename.append(std::to_string(iRel));
			std::string filenameNormal = filename;
			std::string filenameSelected = filename;
			filenameNormal.append(".png");
			filenameSelected.append("_pressed.png");
			node = MenuItemImage::create(filenameNormal, filenameSelected, CC_CALLBACK_1(LevelSelectScene::levelSelectPlay, this, "uptown", iRel));
			node->setPosition(Vec2(150 + (iRel % 5) * 150, 672 - (iRel / 5) * 150));
		}
		else if (i < 20)
		{
			std::string filename = "countryside_";
			filename.append(std::to_string(iRel));
			std::string filenameNormal = filename;
			std::string filenameSelected = filename;
			filenameNormal.append(".png");
			filenameSelected.append("_pressed.png");
			node = MenuItemImage::create(filenameNormal, filenameSelected, CC_CALLBACK_1(LevelSelectScene::levelSelectPlay, this, "countryside", iRel));
			node->setPosition(Vec2(1050 + (iRel % 5) * 150, 672 - (iRel / 5) * 150));
		}
		else if (i < 30)
		{
			std::string filename = "factory_";
			filename.append(std::to_string(iRel));
			std::string filenameNormal = filename;
			std::string filenameSelected = filename;
			filenameNormal.append(".png");
			filenameSelected.append("_pressed.png");
			node = MenuItemImage::create(filenameNormal, filenameSelected, CC_CALLBACK_1(LevelSelectScene::levelSelectPlay, this, "factory", iRel));
			node->setPosition(Vec2(150 + (iRel % 5) * 150, 204 - (iRel / 5) * 150));
		}
		else
		{
			std::string filename = "downtown_";
			filename.append(std::to_string(iRel));
			std::string filenameNormal = filename;
			std::string filenameSelected = filename;
			filenameNormal.append(".png");
			filenameSelected.append("_pressed.png");
			node = MenuItemImage::create(filenameNormal, filenameSelected, CC_CALLBACK_1(LevelSelectScene::levelSelectPlay, this, "downtown", iRel));
			node->setPosition(Vec2(1050 + (iRel % 5) * 150, 204 - (iRel / 5) * 150));
		}
		node->setAnchorPoint({ 0.0, 0.0 });
		levelSelectItems.pushBack(node);
	}
	auto levelSelectMenu = Menu::createWithArray(levelSelectItems);
	levelSelectMenu->setAnchorPoint({ 0.0, 0.0 });
	levelSelectMenu->setPosition(0, 0);
	addChild(levelSelectMenu);

	CCLOG("LevelSelectScene initialized successfully");
	return true;
}

void LevelSelectScene::levelSelectBack(Ref* pSender)
{
	auto scene = MenuScene::create();
	Director::getInstance()->replaceScene(scene);
}

void LevelSelectScene::levelSelectPlay(Ref* pSender, std::string levelPackID, int levelID)
{
	g_currentLevelPack = levelPackID;
	g_currentLevel = levelID;

	auto scene = GameScene::create();
	Director::getInstance()->replaceScene(scene);
}