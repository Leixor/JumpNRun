#pragma once

#include <iostream>
#include <mutex>
#include <stdio.h>
#include <tchar.h>

#include <SFML\Graphics.hpp>

#include <Windows.h>

#include <thread>
#include <chrono>

using namespace std;
using namespace sf;

//Helferklassen
#include "UnorderdMap.h"
#include "Timer.h"
#include "DrawableObject.h"
#include "DrawableShape.h"

//Grundbausteine der Subklassen
#include "ObjectBase.h"
#include "Scene.h"
#include "SceneHandler.h"

//Subklassen
#include "SceneOption.h"
#include "SceneStartMenu.h"
#include "Button.h"
#include "CheckBox.h"


