#pragma once

#include <iostream>
#include <mutex>
#include <stdio.h>
#include <tchar.h>


#include <SFML\Graphics.hpp>
#include "AnimatedSprite.hpp"

#include <Windows.h>

#include <thread>
#include <chrono>

using namespace std;
using namespace sf;


enum visibilityFlags {
	NONE = 0,
	VISIBLE = 1,
	UPDATABLE = 2,
	INPUTABLE = 4,
	ALL = 7
};

enum orientation {
	MIDDLE = 0,
	LEFT = 1,
	RIGHT = 2,
	TOP = 4,
	BOTTOM = 8
};

//Helferklassen
#include "UnorderdMap.h"
#include "Timer.h"
#include "DrawableObject.h"
#include "DrawableShape.h"
#include "AlignHelper.h"
using namespace AlignHelper;
//Grundbausteine der Subklassen
#include "ObjectBase.h"
#include "Scene.h"
#include "SceneHandler.h"

//Subklassen
#include "Button.h"
#include "CheckBox.h"
#include "SceneOption.h"
#include "SceneStartMenu.h"



