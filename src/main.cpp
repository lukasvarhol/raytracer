#include <iostream>
#include <fstream>

int main() {
  unsigned int imageWidth = 256;
  unsigned int imageHeight = 256;

  std::ofstream out("renders/image.ppm");

  out << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int h = 0; h < imageHeight; ++h) {
    std::clog << "\rScan lines remaining: " << imageHeight - h << " " << std::flush;
    for (int w = 0; w < imageWidth; ++w) {
      unsigned int r = h;
      unsigned int g = w;
      unsigned int b = 0;
      out << r << " " << g << " " << b << "\n";
    }
  }

  std::clog << "\rDone.                 \n";
  std::cout << "Render Completed" << std::endl;
}
