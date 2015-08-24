//Used for constants etc.
#pragma once

//Resolutions
static cocos2d::Size designResolutionSize = cocos2d::Size(1920, 1080);
static cocos2d::Size almostSmallResolutionSize = cocos2d::Size(1152, 648);
static cocos2d::Size smallResolutionSize = cocos2d::Size(1280, 720);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1536, 864);
static cocos2d::Size almostLargeResolutionSize = cocos2d::Size(1792, 1008);
static cocos2d::Size largeResolutionSize = cocos2d::Size(1920, 1080);

//Catapult constants
static float catapultPullRadius = 150; //Area where catapult can be pulled
static float catapultShootVelocityMultiplier = 600; //The velocity projectile will have if catapult is pulled all the way back

//Camera
static float camearaPaddingX = 300;
static float cameraMoveSpeedX = 250; //points/second
static float cameraResetTime = 3.0; //Time it takes camera to reset position

//Round ending constants
static float roundEndGarbageMinVelocity = 0.1f;
static float roundEndGarbageStopSafeTime = 3.0f;
static float roundEndMaxTime = 45.0; //seconds

//Action animations
static float garbageCanResetPositionTime = 1.0;
static float garbageCanResetRotationTime = 1.5;

//Rendering order of the items in scenegraph
enum RenderOrder
{
	Background,
	Object,
	Truck,
	Garbage,
	Ground,
	GarbageCan,
	HUD,
	Debug
};
