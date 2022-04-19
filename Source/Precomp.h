#pragma once

#include <cmath>
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

#include "Timer.h"
#include "CacheMath.h"
#include "Ray.h"

typedef unsigned int Pixel;

const int ScreenWidth = 1280;
const int ScreenHeight = 720;

const float Pi = 3.14159265359;
const float RadToDeg = 180.0f / Pi;
const float DegToRad = Pi / 180.0f;