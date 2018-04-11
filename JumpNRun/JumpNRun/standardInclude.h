#pragma once

#define _USE_MATH_DEFINES
#define MS_PER_UPDATE 10

#include <iostream>
#include <mutex>
#include <stdio.h>
#include <tchar.h>
#include <thread>
#include <chrono>
#include <random>
#include <math.h>

#include <SFML\Graphics.hpp>

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

//ExtraClasses
#include "GlobalVariables.h"
#include "UnorderdMap.h"
#include "Timer.h"

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
#include "Animation.h"
#include "AnimationHandler.h"

//Objects
#include "ObjectBase.h"

//Scene
#include "Scene.h"
#include "SceneHandler.h"

#include "Button.h"
#include "CheckBox.h"
#include "SceneOption.h"
#include "SceneStartMenu.h"
#include "SceneGameSelection.h"
#include "SceneSnakeGame.h"
#include "SceneGOL.h"






