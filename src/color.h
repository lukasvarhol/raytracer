#pragma once

#include "linear_algebra.h"
#include <iostream>
#include <fstream>

using color = vec3;

void writeColor(std::ofstream &out, const color &pixelColor) {
  float r = pixelColor.x();
  float g = pixelColor.y();
  float b = pixelColor.z();

  unsigned int rByte = int(255.999 * r);
  unsigned int gByte = int(255.999 * g);
  unsigned int bByte = int(255.999 * b);

  out << rByte << ' ' << gByte << ' ' << bByte << '\n';
}
