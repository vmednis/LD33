#include "GameScene.h"
#include "GameConfig.h"

USING_NS_CC;

bool GameScene::init()
{
	//Init super class
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	//Enable physics debug
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//Truck
	auto truckPhysicsBody = PhysicsBody::createBox({ 156, 228 }, PhysicsMaterial(1.0, 0.0, 0.9));
	truckPhysicsBody->setDynamic(false);
	truckSprite = Sprite::create("uptown/sprites/truck.png");
	truckSprite->setAnchorPoint({ 0.0, 0.0 });
	truckSprite->setPhysicsBody(truckPhysicsBody);
	truckSprite->setPosition(240, 120);
	addChild(truckSprite);

	//Test house
	auto housePhysicsBody = PhysicsBody::createBox({ 240, 240 }, PhysicsMaterial(1.0, 0.0, 0.9), {120, 120});
	housePhysicsBody->setDynamic(false);
	Node * house;
	house = Node::create();
	house->setPhysicsBody(housePhysicsBody);
	house->setAnchorPoint({ 0.0, 0.0 });
	house->setPosition(Vec2(1080, 120));
	addChild(house);
	
	//Test garbage
	auto garbagePhysicsBody = PhysicsBody::createBox({ 20, 20 }, PhysicsMaterial(1.0, 0.3, 0.7));
	garbagePhysicsBody->setDynamic(true);
	garbagePhysicsBody->setVelocity({ 200, 200 });
	auto node = Node::create();
	node->setPhysicsBody(garbagePhysicsBody);
	node->setPosition({ 225 , 330 });
	addChild(node);

	//Ground
	for (unsigned int i = 0; i < 20; i++)
	{
		auto groundPhysicsBody = PhysicsBody::createBox({ 540, 120 }, PhysicsMaterial(1.0, 0.0, 0.9), { 0, -60 });
		groundPhysicsBody->setDynamic(false);
		Sprite * node;
		if (i == 0)
		{
			node = Sprite::create("uptown/sprites/street.png");
		}
		else
		{
			node = Sprite::create("uptown/sprites/grass.png");
		}
		node->setPhysicsBody(groundPhysicsBody);
		node->setAnchorPoint({ 0.0, 0.0 });
		node->setPosition(Vec2(i * 540, 0));
		addChild(node);
		groundSprites.push_back(node);
	}

	//Set catapult location
	catapultLocation.x = 225;
	catapultLocation.y = 330;

	//Create target sprite
	target = Sprite::create("placeholder.png");
	target->setPosition(catapultLocation);
	addChild(target);

	//Create event handlers
	//Keyboard
	auto keyboardEventListener = EventListenerKeyboard::create();
	keyboardEventListener->onKeyPressed = CC_CALLBACK_2(GameScene::keyboardEventHandlerOnPressed, this);
	keyboardEventListener->onKeyReleased = CC_CALLBACK_2(GameScene::keyboardEventHandlerOnReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(keyboardEventListener, 1);
	//Mouse
	auto mouseEventListener = EventListenerMouse::create();
	mouseEventListener->onMouseDown = CC_CALLBACK_1(GameScene::mouseEventHandlerOnDown, this);
	mouseEventListener->onMouseUp = CC_CALLBACK_1(GameScene::mouseEventHandlerOnUp, this);
	mouseEventListener->onMouseMove = CC_CALLBACK_1(GameScene::mouseEventHandlerOnMove, this);
	_eventDispatcher->addEventListenerWithFixedPriority(mouseEventListener, 1);

	//Enable update function
	scheduleUpdate();

	CCLOG("GameScene initialized successfully");
	return true;
}

void GameScene::update(float delta)
{

}

void GameScene::keyboardEventHandlerOnPressed(EventKeyboard::KeyCode keycode, Event * e)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		CCLOG("Spacebar was pressed");
	}
}

void GameScene::keyboardEventHandlerOnReleased(EventKeyboard::KeyCode keycode, Event * e)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		CCLOG("Spacebar was released");
	}
}

void GameScene::mouseEventHandlerOnDown(Event * e)
{
	auto mouseEvent = dynamic_cast<EventMouse *>(e);
}

void GameScene::mouseEventHandlerOnUp(Event * e)
{
	auto mouseEvent = dynamic_cast<EventMouse *>(e);
}

void GameScene::mouseEventHandlerOnMove(Event * e)
{
	auto mouseEvent = dynamic_cast<EventMouse *>(e);
}