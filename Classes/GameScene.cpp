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

	//Create world node
	world = Node::create();
	addChild(world);

	//Set physics engine world settings
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	getPhysicsWorld()->setGravity(Vec2(0, -150));

	//Background
	auto backgroundSprite = Sprite::create("uptown/sprites/background.png");
	backgroundSprite->setAnchorPoint({ 0.0, 0.0 });
	backgroundSprite->setPosition(0, 0);
	world->addChild(backgroundSprite, RenderOrder::Background);

	//Truck
	auto truckPhysicsBody = PhysicsBody::createBox({ 72.0f, 96.0f }, PhysicsMaterial(1.0f, 0.0f, 0.9f), { 102, -18 });
	truckPhysicsBody->addShape(PhysicsShapeBox::create({ 276.0f, 24.0f }, PhysicsMaterial(1.0f, 0.0f, 0.9f), { 0, -78 }));
	truckPhysicsBody->setDynamic(false);
	truckSprite = Sprite::create("uptown/sprites/truck.png");
	truckSprite->setAnchorPoint({ 0.0, 0.0 });
	truckSprite->setPhysicsBody(truckPhysicsBody);
	truckSprite->setPosition(204, 120);
	world->addChild(truckSprite, RenderOrder::Truck);

	//Test house
	auto housePhysicsBody = PhysicsBody::createBox({ 240.0f, 240.0f }, PhysicsMaterial(1.0f, 0.0f, 0.9f), { 120.0f, 120.0f });
	housePhysicsBody->setDynamic(false);
	Node * house;
	house = Node::create();
	house->setPhysicsBody(housePhysicsBody);
	house->setAnchorPoint({ 0.0, 0.0 });
	house->setPosition(Vec2(1080, 120));
	world->addChild(house);

	//Ground
	for (unsigned int i = 0; i < 20; i++)
	{
		auto groundPhysicsBody = PhysicsBody::createBox({ 540.0f, 120.0f }, PhysicsMaterial(1.0f, 0.0f, 0.9f), { 0.0f, -60.0f });
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
		world->addChild(node, RenderOrder::Ground);
		groundSprites.push_back(node);
	}

	//Set catapult location
	catapultLocation.x = 204;
	catapultLocation.y = 300;

	//Create garbageCanSprite
	garbageCanSprite = Sprite::create("uptown/sprites/garbage_can.png");
	garbageCanSprite->setAnchorPoint({ 0.5, 0.75 });
	garbageCanSprite->setPosition(catapultLocation);
	world->addChild(garbageCanSprite, RenderOrder::GarbageCan);

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
	if (catapultReady)
	{
		//Start moving the garbage can
		catapultPulling = true;
		catapultReady = false;
		moveGarbageCan({ mouseEvent->getCursorX(), mouseEvent->getCursorY() });
	}
}

void GameScene::mouseEventHandlerOnUp(Event * e)
{
	auto mouseEvent = dynamic_cast<EventMouse *>(e);
	if (catapultPulling)
	{
		//Shoot
		catapultPulling = false;
		//Calculate projectile velocity
		Vec2 shootingVelocity = (garbageCanSprite->getPosition() - catapultLocation) * -1;
		shootingVelocity.x = pow(sqrt(shootingVelocity.x / catapultPullRadius) * sqrt(catapultShootVelocityMultiplier), 2);
		shootingVelocity.y = pow(sqrt(shootingVelocity.y / catapultPullRadius) * sqrt(catapultShootVelocityMultiplier), 2);

		//Test garbage
		auto garbagePhysicsBody = PhysicsBody::createBox({ 20.0f, 20.0f }, PhysicsMaterial(1.0f, 0.3f, 0.7f));
		garbagePhysicsBody->setDynamic(true);
		garbagePhysicsBody->setVelocity(shootingVelocity);
		auto node = Node::create();
		node->setPhysicsBody(garbagePhysicsBody);
		node->setPosition(garbageCanSprite->getPosition());
		world->addChild(node, RenderOrder::Garbage);

		//Start moving garbage can back to it's initial position
		auto moveAction = MoveTo::create(1.0, catapultLocation);
		auto moveActionEased = EaseElasticOut::create(moveAction->clone());
		auto rotateAction = RotateTo::create(1.5, 0);
		auto rotateActionEased = EaseBackInOut::create(rotateAction->clone());
		CCLOG("test");
		auto actionSpawn = Spawn::createWithTwoActions(moveActionEased, rotateActionEased);
		CCLOG("test");
		garbageCanSprite->runAction(actionSpawn);

		CCLOG("Shooting!");
	}
}

void GameScene::mouseEventHandlerOnMove(Event * e)
{
	auto mouseEvent = dynamic_cast<EventMouse *>(e);
	if (catapultPulling)
	{
		//Move garbage can to the new positions
		moveGarbageCan({ mouseEvent->getCursorX(), mouseEvent->getCursorY() });
	}
}

void GameScene::moveGarbageCan(Vec2 mouseLocation)
{
	if (catapultPulling) //Catapult is beeing pulled on
	{
		//Apply changes in location
		if (mouseLocation.distance(catapultLocation) < catapultPullRadius)
		{
			//Mouse is within pull radius
			garbageCanSprite->setPosition(mouseLocation);
		}
		else
		{
			//Mouse is outside the radius
			//Find where line from mouse to catapultlocation intersects with a cirlce with radius of catapultPullRadius
			//Get absolute size of Garbage cans relative vector edges
			Vec2 relativeMouseLocation = mouseLocation - catapultLocation;
			float sinalpha = abs(relativeMouseLocation.y) / abs(relativeMouseLocation.getLength());
			float GarbageCanX, GarbageCanY;
			GarbageCanY = sinalpha * catapultPullRadius;
			GarbageCanX = sqrt(catapultPullRadius*catapultPullRadius - GarbageCanY*GarbageCanY);

			//transform absolute location in real location
			Vec2 newGarbageCanRelativeLocation(GarbageCanX, GarbageCanY);
			if (relativeMouseLocation.x < 0)
			{
				newGarbageCanRelativeLocation.x *= -1;
			}
			if (relativeMouseLocation.y < 0)
			{
				newGarbageCanRelativeLocation.y *= -1;
			}

			//apply the new location5
			garbageCanSprite->setPosition(catapultLocation + newGarbageCanRelativeLocation);
		}
		Vec2 relativeLocation = garbageCanSprite->getPosition() - catapultLocation;
		garbageCanSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(relativeLocation.getAngle()) - 90);
	}
}
