#include "Garbage.h"
#include "GameConfig.h"
#include "GlobalVariables.h"

USING_NS_CC;

void GarbageClass::createGarbage(Node * world, Vec2 garbageCanPosition, Vec2 velocity)
{
	velocity += {RandomHelper::random_real(0.0f, catapultVelocityRandomness), RandomHelper::random_real(0.0f, catapultVelocityRandomness)};
	int j = RandomHelper::random_int(0, 3);
	if (j == 0)
	{
		//Regular garbage
		auto garbagePhysicsBody = PhysicsBody::createBox({ 16.0f, 16.0f }, PhysicsMaterial(physicsDensityGarbage, physicsRestitutionGarbage, physicsFrictionGarbage));
		garbagePhysicsBody->setDynamic(true);
		garbagePhysicsBody->setVelocity(velocity);
		std::string garbageSpritePath = g_currentLevelPack;
		garbageSpritePath.append("/sprites/garbage.png");
		auto sprite = Sprite::create(garbageSpritePath);
		sprite->setAnchorPoint({ 0.5, 0.5 });
		sprite->setPhysicsBody(garbagePhysicsBody);
		sprite->setPosition(garbageCanPosition);
		world->addChild(sprite, RenderOrder::Garbage);
		this->sprite = sprite;
	}
	if (j == 1)
	{
		//Green soda
		auto garbagePhysicsBody = PhysicsBody::createBox({ 12.0f, 30.0f }, PhysicsMaterial(physicsDensityGarbage, physicsRestitutionGarbage, physicsFrictionGarbage));
		garbagePhysicsBody->setDynamic(true);
		garbagePhysicsBody->setVelocity(velocity);
		std::string garbageSpritePath = g_currentLevelPack;
		garbageSpritePath.append("/sprites/green_soda.png");
		auto sprite = Sprite::create(garbageSpritePath);
		sprite->setAnchorPoint({ 0.5, 0.5 });
		sprite->setPhysicsBody(garbagePhysicsBody);
		sprite->setPosition(garbageCanPosition);
		world->addChild(sprite, RenderOrder::Garbage);
		this->sprite = sprite;
	}
	if (j == 2)
	{
		//Red soda
		auto garbagePhysicsBody = PhysicsBody::createBox({ 12.0f, 30.0f }, PhysicsMaterial(physicsDensityGarbage, physicsRestitutionGarbage, physicsFrictionGarbage));
		garbagePhysicsBody->setDynamic(true);
		garbagePhysicsBody->setVelocity(velocity);
		std::string garbageSpritePath = g_currentLevelPack;
		garbageSpritePath.append("/sprites/red_soda.png");
		auto sprite = Sprite::create(garbageSpritePath);
		sprite->setAnchorPoint({ 0.5, 0.5 });
		sprite->setPhysicsBody(garbagePhysicsBody);
		sprite->setPosition(garbageCanPosition);
		world->addChild(sprite, RenderOrder::Garbage);
		this->sprite = sprite;
	}
	if (j == 3)
	{
		//Dead fish
		auto garbagePhysicsBody = PhysicsBody::createBox({ 28.0f, 14.0f }, PhysicsMaterial(physicsDensityGarbage, physicsRestitutionGarbage, physicsFrictionGarbage));
		garbagePhysicsBody->setDynamic(true);
		garbagePhysicsBody->setVelocity(velocity);
		std::string garbageSpritePath = g_currentLevelPack;
		garbageSpritePath.append("/sprites/fish.png");
		auto sprite = Sprite::create(garbageSpritePath);
		sprite->setAnchorPoint({ 0.5, 0.5 });
		sprite->setPhysicsBody(garbagePhysicsBody);
		sprite->setPosition(garbageCanPosition);
		world->addChild(sprite, RenderOrder::Garbage);
		this->sprite = sprite;
	}
}

bool GarbageClass::hasStopedMoving()
{
	if (notMoving)
	{
		return true;
	}
	if (!waitingForSafeTime)
	{
		if (sprite->getPhysicsBody()->getVelocity().length() < roundEndGarbageMinVelocity)
		{
			//Create the check that gets trigered in a bit to see if the piece of garbage just didn't hit a wall and has actually landed
			auto delay = DelayTime::create(roundEndGarbageStopSafeTime);
			auto function = CallFunc::create([this] ()
			{
				if (sprite->getPhysicsBody()->getVelocity().length() < roundEndGarbageMinVelocity)
				{
					notMoving = true;
					stopedMoving();
				}
				else
				{
					//If turns out that it actually didn't stop allow the initial check to be run again
					waitingForSafeTime = false;
				}
			});
			auto sequence = Sequence::createWithTwoActions(delay, function);
			waitingForSafeTime = true;
			//Run the check
			sprite->runAction(sequence);
		}
	}
	return false;
}

void GarbageClass::stopedMoving()
{
	//Give score
	unsigned int scoreGiven = 0;
	for (ScoreBox scoreBox : levelController->getScoreBoxes())
	{
		if (scoreBox.getLocation().x < sprite->getPosition().x && scoreBox.getLocation().x + scoreBox.getSize().x > sprite->getPosition().x
			&& scoreBox.getLocation().y < sprite->getPosition().y && scoreBox.getLocation().y + scoreBox.getSize().y > sprite->getPosition().y)
		{
			scoreGiven = scoreBox.getPointsWorth();
		}
	}
	if (scoreGiven == 0)
	{
		scoreGiven = pointsAwardedNothing;
	}
	scoreHandler->addScore(scoreGiven);
	//Todo: Display score given (Issue #4)
}