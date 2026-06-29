#pragma once
#include <limits>
#include <iostream>
#include <cmath>
#include <memory>

// Constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.14159265f;

// Utility Functions
inline float degreesToRadians(float degrees) { return degrees * pi / 180.0f; }

// Common Headers
#include "color.h"
#include "ray.h"
#include "linear_algebra.h"
#include "interval.h"
