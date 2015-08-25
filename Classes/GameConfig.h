//Used for constants etc.
#pragma once

//Resolutions
static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size almostSmallResolutionSize = cocos2d::Size(1152, 648);
static cocos2d::Size smallResolutionSize = cocos2d::Size(1280, 720);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1536, 864);
static cocos2d::Size almostLargeResolutionSize = cocos2d::Size(1792, 1008);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1920, 1080);

//World constants
static float worldHeight = 2 * designResolutionSize.height;

//Catapult constants
static float catapultPullRadius = 160; //Area where catapult can be pulled
static float catapultShootVelocityMultiplier = 600; //The velocity projectile will have if catapult is pulled all the way back
static float catapultVelocityRandomness = 5.0f;
static unsigned int piecesOfGarbagePerCan = 10;

//Camera
static float camearaPaddingX = 300;
static float cameraMoveSpeedX = 280; //points/second
static float cameraResetTime = 1.0; //Time it takes camera to reset position

//Round ending constants
static float roundEndGarbageMinVelocity = 1.5f;
static float roundEndGarbageStopSafeTime = 3.0f; //seconds
static float roundEndMaxTime = 45.0; //seconds
static int roundEndMaxTimeActionTag = 1;

//level constants
static unsigned int shotsPerLevel = 3;

//Action animations
static float garbageCanResetPositionTime = 1.0;
static float garbageCanResetRotationTime = 1.5;

//Object awarded points
static int pointsAwardedNothing = 50;
static int pointsAwardedFence = 250;
static int pointsAwardedGarbageCan = 0;
static int pointsAwardedDaisy = 350;
static int pointsAwardedSunflower = 300;
static int pointsAwardedTulipGarden = 200;
static int pointsAwardedHouse = 250;
static int pointsAwardedTwoStoryHouse = 200;
static int pointsAwardedChimneyBonus = 500;
static int pointsAwardedGarage = 200;
static int pointsAwardedInsideGarageBonus = 150;

//Rendering order of the items in scenegraph
enum RenderOrder
{
	Background,
	Object,
	Truck,
	Garbage,
	Ground,
	GarbageCan,
	HUDBackground,
	HUDForeground,
	Splash,
	Debug
};

//The state of the current game
enum GameState
{
	PreLoading,
	Loading,
	BeforeShooting,
	Aiming,
	Shooting,
	AfterShooting,
	LevelDone
};