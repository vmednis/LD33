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

//Rendering order of the items in scenegraph
enum RenderOrder
{
	Background,
	Truck,
	Garbage,
	Ground,
	GarbageCan,
	Debug
};
