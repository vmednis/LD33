#include "GameScene.h"

USING_NS_CC;

void keyboardEventHandlerOnPressed(EventKeyboard::KeyCode keycode, Event * e);
void keyboardEventHandlerOnReleased(EventKeyboard::KeyCode keycode, Event * e);

bool GameScene::init()
{
	//Init super class
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	//Enable physics debug
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//Ground
	for (unsigned int i = 0; i < 20; i++)
	{
		auto groundPhysicsBody = PhysicsBody::createBox({ 540, 120 }, PhysicsMaterial(), {0, -60});
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
	
	//Add truck
	auto truckPhysicsBody = PhysicsBody::createBox({ 156, 228 }, PhysicsMaterial());
	truckPhysicsBody->setDynamic(false);
	truckSprite = Sprite::create("uptown/sprites/truck.png");
	truckSprite->setAnchorPoint({ 0.0, 0.0 });
	truckSprite->setPhysicsBody(truckPhysicsBody);
	truckSprite->setPosition(240, 120);
	addChild(truckSprite);

	//Add garbage can and the hand
	auto garbageCanPhysicsBody = PhysicsBody::createBox({ 24, 126 }, PhysicsMaterial(), {36, 3});
	garbageCanPhysicsBody->addShape(PhysicsShapeBox::create({ 2, 114 }, PhysicsMaterial(), { 23, -3 }));
	garbageCanPhysicsBody->addShape(PhysicsShapeBox::create({ 2, 114 }, PhysicsMaterial(), { -47, -3 }));
	garbageCanPhysicsBody->addShape(PhysicsShapeBox::create({ 72, 2 }, PhysicsMaterial(), { -10, -60 }));
	garbageCanPhysicsBody->setDynamic(true);
	garbageCanSprite = Sprite::create("uptown/sprites/garbage_can.png");
	garbageCanSprite->setPhysicsBody(garbageCanPhysicsBody);
	garbageCanSprite->setAnchorPoint({ 1.0, 1.0 });
	garbageCanSprite->setPosition(252, 324);
	addChild(garbageCanSprite);

	//Add garbage can joint
	auto garbageCanJoint = PhysicsJointPin::construct(garbageCanPhysicsBody, truckPhysicsBody, { 252, 324 });
	getPhysicsWorld()->addJoint(garbageCanJoint);
	auto garbageCanLimiter = PhysicsJointRotaryLimit::construct(truckPhysicsBody, garbageCanPhysicsBody, 0.0, (float) M_PI_2);
	getPhysicsWorld()->addJoint(garbageCanLimiter);
	garbageCanPhysicsBody->setAngularVelocity(0.5);
	//auto garbageCanMotor = PhysicsJointMotor::construct(garbageCanPhysicsBody, truckPhysicsBody, -2);
	//getPhysicsWorld()->addJoint(garbageCanMotor);

	//Test garbage
	auto garbagePhysicsBody = PhysicsBody::createBox({ 20, 20 }, PhysicsMaterial());
	garbagePhysicsBody->setDynamic(true);
	auto node = Node::create();
	node->setPhysicsBody(garbagePhysicsBody);
	node->setPosition({ 225 , 330 });
	addChild(node);

	//Create event handlers
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = keyboardEventHandlerOnPressed;
	eventListener->onKeyReleased = keyboardEventHandlerOnReleased;
	_eventDispatcher->addEventListenerWithFixedPriority(eventListener, 1);

	//Enable update function
	scheduleUpdate();

	CCLOG("GameScene initialized successfully");
	return true;
}

void GameScene::update(float delta)
{

}

void keyboardEventHandlerOnPressed(EventKeyboard::KeyCode keycode, Event * e)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		CCLOG("Spacebar was pressed");
	}
}

void keyboardEventHandlerOnReleased(EventKeyboard::KeyCode keycode, Event * e)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
		CCLOG("Spacebar was released");
	}
}