#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include "view.h"
#include "level.h"
#include "classEntity.h"
#include "classPlayer.h"
#include "classEnemy.h"
#include "classObjects.h"
#include "menu.h"

void checkGamePlay();
void runningGame(void(*cb)(void));
