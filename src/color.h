#pragma once
#include "config.h"
#include "interval.h"
#include "linear_algebra.h"
#include <fstream>

using color = vec3;

void writeColor(std::ofstream &out, const color &pixelColor) {
  float r = pixelColor.x();
  float g = pixelColor.y();
  float b = pixelColor.z();

  static const interval intensity(0.000f, 0.999f);
  int rByte = int(256 * intensity.clamp(r));
  int gByte = int(256 * intensity.clamp(g));
  int bByte = int(256 * intensity.clamp(b));

  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}
