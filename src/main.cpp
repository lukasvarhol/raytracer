#include <iostream>
#include <fstream>

#include "color.h"
#include "ray.h"

bool hitSphere(const point3 &center, const float radius, const ray &r) {
  vec3 rayOriginToCenter = center - r.origin();
  // qyadratic formula varaibles:
  float a = dot(r.direction(), r.direction());
  float b = -2.0f * dot(r.direction(), rayOriginToCenter);
  float c = dot(rayOriginToCenter, rayOriginToCenter) - (radius * radius);
  float discriminant = (b * b) - (4 * a * c);
  return (discriminant >= 0);
}

color rayColor(const ray &r) {
  if (hitSphere(point3(0.0f, 0.0f, -1.0f), 0.5f, r)) return color(0.3f, 0.3f, 0.3f);
  vec3 unitDirection = unitVector(r.direction());
  auto a = 0.5*(unitDirection.y() + 1.0);
  return (1.0f-a)*color(1.0f, 1.0f, 1.0f) + a*color(0.5f, 0.7f, 1.0f);
}

int main() {
  constexpr float aspectRatio = 16.0f/ 9.0f;
  constexpr int imageWidth = 640;
  constexpr int imageHeight =
      int(imageWidth / aspectRatio) < 1 ? 1 : int(imageWidth / aspectRatio);

  constexpr float focalLength = 1.0f;
  constexpr float viewportHeight = 2.0f;
  constexpr float viewportWidth =
      viewportHeight * (float(imageWidth) / imageHeight);

  point3 cameraCenter = point3(0.0f, 0.0f, 0.0f);

  vec3 viewportHVec = vec3(viewportWidth, 0.0f, 0.0f); 
  vec3 viewportVVec = vec3(0.0f, -viewportHeight, 0.0f); 
  vec3 pixelDeltaH = viewportHVec / (float)imageWidth; 
  vec3 pixelDeltaV = viewportVVec / (float)imageHeight; 
  

  point3 viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) -
                             viewportHVec / 2 - viewportVVec / 2;
  point3 pixel00Location =
      viewportUpperLeft + 0.5 * (pixelDeltaH + pixelDeltaV);

  std::ofstream out("renders/image.ppm");

  out << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

  for (int v = 0; v < imageHeight; ++v) {
    std::clog << "\rScan lines remaining: " << imageHeight - v << " " << std::flush;
    for (int h = 0; h < imageWidth; ++h) {
      point3 pixelCenter =
          pixel00Location + (h * pixelDeltaH) + (v * pixelDeltaV);
      vec3 rayDirection = pixelCenter - cameraCenter;
      ray r(cameraCenter, rayDirection);
      color pixelColor = rayColor(r);
      writeColor(out, pixelColor);
    }
  }

  std::clog << "\rDone.                 \n";
  std::cout << "Render Completed" << std::endl;
}
