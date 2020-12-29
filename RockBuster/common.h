#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <ctime>
#include <direct.h> // _mkdir

#include "SFML-headers.h"

#define VERSION "v1.0" // Always 4 characters

void initCommon();

int randInRange(int a, int b);

bool rectCircleCollision(const sf::FloatRect rect, const sf::FloatRect circle);
