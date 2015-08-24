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

	//Load level
	levelController = new Level(world);
	levelController->loadLevel("test.txt");

	//ScoreBox debug
	debugDrawNode = DrawNode::create();
	for (ScoreBox box : levelController->getScoreBoxes())
	{
		debugDrawNode->drawRect(box.getLocation(), box.getLocation() + box.getSize(), Color4F(0.12f, 0.56f, 1.0f, 0.3f));
	}
	world->addChild(debugDrawNode, RenderOrder::Debug);

	//Set physics engine world settings
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	getPhysicsWorld()->setGravity(Vec2(0, -150));

	//Truck
	truckSprite = Sprite::create("uptown/sprites/truck.png");
	truckSprite->setAnchorPoint({ 0.0, 0.0 });
	truckSprite->setPosition(204, 120);
	world->addChild(truckSprite, RenderOrder::Truck);

	//Set catapult location
	catapultLocation.x = 204;
	catapultLocation.y = 300;

	//Create garbageCanSprite
	garbageCanSprite = Sprite::create("uptown/sprites/garbage_can.png");
	garbageCanSprite->setAnchorPoint({ 0.5, 1.0 });
	garbageCanSprite->setPosition(catapultLocation);
	world->addChild(garbageCanSprite, RenderOrder::GarbageCan);

	//TODO: Change this
	gameState = GameState::BeforeShooting;

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
	if (gameState == GameState::PreLoading)
	{
		//Display the loading screen
		gameState = GameState::Loading;
	}
	else if (gameState == GameState::Loading)
	{
		//level.loadLevel("something.lvl");
		gameState = GameState::BeforeShooting;
	}
	else if (gameState == GameState::BeforeShooting)
	{
		cameraUpdateMove(delta);
		catapultReady = true;
		hasGarbageStopedOnce = false;
	}
	else if (gameState == GameState::Aiming)
	{
		if (!cameraReseting && world->getPosition().x != 0)
		{
			cameraReset();
		}
	}
	else if (gameState == GameState::Shooting)
	{
		cameraFollow();
		if (hasGarbageStopedMoving() && !hasGarbageStopedOnce)
		{
			hasGarbageStopedOnce = true;
			auto delay = DelayTime::create(roundEndGarbageStopSafeTime);
			auto callFunction = CallFunc::create([this]() {
				if (hasGarbageStopedMoving())
				{
					//Change gameState
					gameState = GameState::AfterShooting;
					world->stopActionByTag(roundEndMaxTimeActionTag);
				}
				else
				{
					hasGarbageStopedOnce = false;
				}
			});
			auto sequence = Sequence::createWithTwoActions(delay, callFunction);
			world->runAction(sequence);
		}
	}
	else if (gameState == GameState::AfterShooting)
	{
		//Calculate score earned
		for (Node * garbage : garbageSprites)
		{
			bool anyScoreAdded = false;
			for (ScoreBox scorebox : levelController->getScoreBoxes())
			{
				if (garbage->getPosition().x > scorebox.getLocation().x && garbage->getPosition().x < scorebox.getLocation().x + scorebox.getSize().x 
					&& garbage->getPosition().y > scorebox.getLocation().y && garbage->getPosition().y < scorebox.getLocation().y + scorebox.getSize().y )
				{
					addScore(scorebox.getPointsWorth());
					anyScoreAdded = true;
				}
			}
			if (!anyScoreAdded)
			{
				addScore(pointsAwardedNothing);
			}
		}
		//See if player has used up all his shots
		timesShot++;
		if (timesShot < shotsPerLevel)
		{
			gameState = GameState::BeforeShooting;
			//Remove the old garbage
			for (Node * garbage : garbageSprites)
			{
				//Maybe play some nice particle effects here or something?
				garbage->removeFromParentAndCleanup(true);
			}
			garbageSprites.clear();
			cameraReset();
		}
		else
		{
			//Player has already made all the shots allowed per level
			gameState = GameState::LevelDone;
		}
	}
	else if (gameState == GameState::LevelDone)
	{
		//Display level done splash and maybe start loading the next level or something
	}
	cameraForceBounds();
	hasGarbageStopedMoving();
}

void GameScene::cameraFollow()
{
	//Follow furthest piece of garbage with the camera
	float furthestX = 0.0;
	Node * furthestGarbage = NULL;
	for (Node * garbage : garbageSprites)
	{
		if (garbage->getPosition().x > furthestX)
		{
			furthestX = garbage->getPosition().x;
			furthestGarbage = garbage;
		}
	}
	if (furthestGarbage != NULL)
	{
		if (world->convertToWorldSpace(furthestGarbage->getPosition()).x > designResolutionSize.width - camearaPaddingX)
		{
			world->setPosition({ -1 * (furthestGarbage->getPosition().x - (designResolutionSize.width - camearaPaddingX)) , 0 });
		}
	}
}

void GameScene::cameraReset()
{
	cameraReseting = true;
	auto moveAction = MoveTo::create(cameraResetTime, { 0.0, 0.0 });
	auto moveActionEased = EaseOut::create(moveAction->clone(), 1.0);
	//set cameraReseting var when camera is back to it's suppoused place
	auto callFunc = CallFunc::create([this]() {cameraReseting = false;});
	auto sequence = Sequence::createWithTwoActions(moveActionEased, callFunc);
	world->runAction(sequence);
}

void GameScene::cameraUpdateMove(float delta)
{
	if (cameraMoveRight)
	{
		world->setPosition(world->getPosition() - Vec2(cameraMoveSpeedX * delta, 0));
	}
	if (cameraMoveLeft)
	{
		world->setPosition(world->getPosition() + Vec2(cameraMoveSpeedX * delta, 0));
	}
}

void GameScene::cameraForceBounds()
{
	//too far to the left
	if (world->getPosition().x > 0)
	{
		world->setPosition({0, world->getPosition().y});
	}
	//too far to the right
	if ((world->getPosition().x - designResolutionSize.width)*-1.0 > levelController->getSize())
	{
		if (levelController->getSize() > designResolutionSize.width)
		{
			world->setPosition({ (levelController->getSize() - designResolutionSize.width) * -1, world->getPosition().y });
		}
		else//The level is smaller than the screen itself
		{
			world->setPosition({ 0, world->getPosition().y });
		}
	}
}

bool GameScene::hasGarbageStopedMoving()
{
	if (garbageSprites.size() > 0)
	{
		float biggestVelocity = 0.0;
		for (Node * garbage : garbageSprites)
		{
			if (garbage->getPhysicsBody()->getVelocity().length() > biggestVelocity)
			{
				biggestVelocity = garbage->getPhysicsBody()->getVelocity().length();
			}
		}
		if (biggestVelocity < roundEndGarbageMinVelocity)
		{
			return true;
		}
	}
	return false;
}

void GameScene::addScore(unsigned int score)
{
	this->score += score;
	CCLOG("Added %i score, current score = %i", score, this->score);
}

void GameScene::keyboardEventHandlerOnPressed(EventKeyboard::KeyCode keycode, Event * e)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		cameraMoveRight = true;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		cameraMoveLeft = true;
		break;
	case EventKeyboard::KeyCode::KEY_F5:
		cameraReset();
		break;
	}
}

void GameScene::keyboardEventHandlerOnReleased(EventKeyboard::KeyCode keycode, Event * e)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		cameraMoveRight = false;
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		cameraMoveLeft = false;
		break;
	}
}

void GameScene::mouseEventHandlerOnDown(Event * e)
{
	auto mouseEvent = dynamic_cast<EventMouse *>(e);
	if (catapultReady)
	{
		//Enter aiming gameState
		gameState = GameState::Aiming;

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
		shootGarbage();
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
	mouseLocation = world->convertToNodeSpace(mouseLocation);
	if (catapultPulling) //Catapult is beeing pulled on
	{
		//if (mouseLocation.x > 204) mouseLocation.x = 204;
		//if (mouseLocation.y > 300) mouseLocation.y = 300;
		//if (mouseLocation.x == 204 && mouseLocation.y == 300) mouseLocation.x = 203;
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

void GameScene::shootGarbage()
{
	catapultPulling = false;
	//Calculate projectile velocity
	Vec2 relativeGarbageCanPosition = (garbageCanSprite->getPosition() - catapultLocation);
	Vec2 shootingVelocity = relativeGarbageCanPosition * -1;
	shootingVelocity.x = pow(sqrt(abs(shootingVelocity.x) / catapultPullRadius) * sqrt(catapultShootVelocityMultiplier), 2);
	shootingVelocity.y = pow(sqrt(abs(shootingVelocity.y) / catapultPullRadius) * sqrt(catapultShootVelocityMultiplier), 2);
	//Make sure it shoots in the right direction
	if (relativeGarbageCanPosition.x > 0)
	{
		shootingVelocity.x *= -1;
	}
	if (relativeGarbageCanPosition.y > 0)
	{
		shootingVelocity.y *= -1;
	}

	//Spawn garbage
	auto garbagePhysicsBody = PhysicsBody::createBox({ 16.0f, 16.0f }, PhysicsMaterial(1.0f, 0.3f, 0.7f));
	garbagePhysicsBody->setDynamic(true);
	garbagePhysicsBody->setVelocity(shootingVelocity);
	auto sprite = Sprite::create("uptown/sprites/garbage.png");
	sprite->setAnchorPoint({ 0.5, 0.5 });
	sprite->setPhysicsBody(garbagePhysicsBody);
	sprite->setPosition(garbageCanSprite->getPosition());
	world->addChild(sprite, RenderOrder::Garbage);
	garbageSprites.push_back(sprite);

	//Start moving garbage can back to it's initial position
	auto moveAction = MoveTo::create(garbageCanResetPositionTime, catapultLocation);
	auto moveActionEased = EaseElasticOut::create(moveAction->clone());
	auto rotateAction = RotateTo::create(garbageCanResetRotationTime, 0);
	auto rotateActionEased = EaseBackInOut::create(rotateAction->clone());
	auto actionSpawn = Spawn::createWithTwoActions(moveActionEased, rotateActionEased);
	garbageCanSprite->runAction(actionSpawn);

	//Start max round time timer
	auto delayAction = DelayTime::create(roundEndMaxTime);
	auto callAction = CallFunc::create([this]() {
		gameState = GameState::AfterShooting;
	});
	auto sequence = Sequence::createWithTwoActions(delayAction, callAction);
	sequence->setTag(roundEndMaxTimeActionTag);
	world->runAction(sequence);

	//Change the gamestate
	gameState = GameState::Shooting;
}