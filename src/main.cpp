#include <iostream>
#include <fstream>

#include "color.h"

int main() {
  unsigned int imageWidth = 256;
  unsigned int imageHeight = 256;

  std::ofstream out("renders/image.ppm");

  out << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int h = 0; h < imageHeight; ++h) {
    std::clog << "\rScan lines remaining: " << imageHeight - h << " " << std::flush;
    for (int w = 0; w < imageWidth; ++w) {
      float r = float(w) / (imageWidth - 1);
      float g = float(h) / (imageWidth - 1);
      float b = 1.0f - (r+g)/2.0f;
      color pixelColor = color(r, g, b);
      writeColor(out, pixelColor);
    }
  }

  std::clog << "\rDone.                 \n";
  std::cout << "Render Completed" << std::endl;
}
