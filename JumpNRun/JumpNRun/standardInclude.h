#pragma once

#define _USE_MATH_DEFINES
#define MS_PER_UPDATE 10

#include <iostream>
#include <sstream>
#include <mutex>
#include <stdio.h>
#include <tchar.h>
#include <thread>
#include <chrono>
#include <random>
#include <math.h>

#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

#include <Windows.h>

using namespace std;
using namespace sf;

enum eVisibilityFlags {
	NONE = 0,
	VISIBLE = 1,
	UPDATABLE = 2,
	INPUTABLE = 4,
	ALL = 7
};

enum eOrientation {
	MIDDLE = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 4,
	BOTTOM = 8
};

enum aniType {
	ROTATE = 1,
	SCALE = 2,
	MOVE = 4
};

struct BezierHandles
{
	Vector2f handleOne;
	Vector2f handleTwo;
	BezierHandles(float x1, float y1, float x2, float y2) : handleOne(x1, y2), handleTwo(x2, y2) {}
};

//ExtraClasses
#include "GlobalVariables.h"
#include "UnorderdMap.h"

//DrawableShapes
#include "DrawableObject.h"
#include "DrawableShape.h"
#include "ShapeRectangle.h"
#include "ShapeCircle.h"
#include "ShapeSprite.h"

//Helferklassen
#include "ConfigHelper.h"
#include "SavefileHelper.h"
#include "AlignHelper.h"
using namespace AlignHelper;



//Animation
#include "subAnimation.h"
#include "Animation.h"
#include "AnimationHandler.h"
#include "aniRotate.h"
//Objects
#include "ObjectBase.h"

//Scene
#include "Scene.h"
#include "SceneHandler.h"

#include "Button.h"
#include "Slider.h"
#include "DropdownList.h"
#include "CheckBox.h"
#include "SceneOption.h"
#include "SceneStartMenu.h"
#include "SceneGameSelection.h"
#include "SceneSnakeGame.h"
#include "SceneGOL.h"






