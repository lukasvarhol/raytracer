#pragma once
#include <cstdlib>
#include <limits>
#include <iostream>
#include <cmath>
#include <memory>

// Constants
const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.14159265f;

// Utility Functions
inline float degreesToRadians(float degrees) { return degrees * pi / 180.0f; }

inline float randomFloat() {
  return std::rand() / (RAND_MAX + 1.0f);
}

inline float randomFloat(float min, float max) {
  return min + (max - min) * randomFloat();
}

// Common Headers
#include "color.h"
#include "ray.h"
#include "linear_algebra.h"
#include "interval.h"
