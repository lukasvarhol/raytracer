#pragma once

#include "config.h"
#include "hittable.h"


class camera {
public:
  // super awesome code goes here
  float aspectRatio = 1.0f;
  int imageWidth = 100;

  void render(const hittable &world) {
    initialize();

    std::ofstream out ("renders/image.ppm");
    out << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int v{}; v < imageHeight; ++v) {
      std::clog << "\rScanlines remaining: " << (imageHeight - v) << ' '
                << std::flush;
      for (int h{}; h < imageWidth; ++h) {
        point3 pixelCentre =
	  pixel00Location + (float(h) * pixelDeltaH) + (float(v) * pixelDeltaV);
        vec3 rayDirection = pixelCentre - centre;
        ray r(centre, rayDirection);

        color pixelColor = rayColor(r, world);
        writeColor(out, pixelColor);
      }
    }

    std::clog << "\rDONE.                         \n";
  }

private:
// more super awesome code goes here
  int imageHeight;
  point3 centre;
  point3 pixel00Location;
  vec3 pixelDeltaH;
  vec3 pixelDeltaV;

  void initialize() {
    imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;
    centre = point3(0.0f, 0.0f, 0.0f);

    // viewport dimensions
    float focalLength = 1.0f;
    float viewportHeight = 2.0f;
    float viewportWidth = viewportHeight * (float(imageWidth)/imageHeight);

    // veritical & horizontal vectors
    vec3 viewportH = vec3(viewportWidth, 0.0f, 0.0f);
    vec3 viewportV = vec3(0.0f, -viewportHeight, 0.0f);

    // vertical & horizonatl deltas
    pixelDeltaH = viewportH / float(imageWidth);
    pixelDeltaV = viewportV / float(imageHeight);

    // where is the upper-left pixel?
    point3 viewportUpperLeft = centre - vec3(0.0f, 0.0f, focalLength) - viewportH/2 - viewportV/2;
    pixel00Location = viewportUpperLeft + 0.5f * (pixelDeltaH + pixelDeltaV);
  }

  color rayColor(const ray &r, const hittable &world) const {
    hitRecord rec;

    if (world.hit(r, interval(0.0f, infinity), rec)) {
      return 0.5f * (rec.normal + color(1.0f, 1.0f, 1.0f));
    }

    vec3 unitDirection = unitVector(r.direction());
    float a = 0.5f * (unitDirection.y() + 1.0f);
    return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
  }
};
