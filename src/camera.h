#pragma once

#include "config.h"
#include "hittable.h"
#include "linear_algebra.h"


class camera {
public:
  // super awesome code goes here
  float aspectRatio = 1.0f;
  int imageWidth = 100;
  int samplesPerPixel = 10; // how many times we sample a pixel's colour
  int maxDepth;

  void render(const hittable &world) {
    initialize();

    std::ofstream out ("renders/image.ppm");
    out << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int v{}; v < imageHeight; ++v) {
      std::clog << "\rScanlines remaining: " << (imageHeight - v) << ' '
                << std::flush;
      for (int h{}; h < imageWidth; ++h) {
        color pixelColor(0.0f, 0.0f, 0.0f);
        for (int sample{}; sample < samplesPerPixel; ++sample) {
          ray r = getRay(h, v);
          pixelColor = pixelColor + rayColor(r, maxDepth, world);
	}
        writeColor(out, pixelSamplesScale * pixelColor);
      }
    }

    std::clog << "\rDONE.                         \n";
  }

private:
// more super awesome code goes here
  int imageHeight;
  float pixelSamplesScale;
  point3 centre;
  point3 pixel00Location;
  vec3 pixelDeltaH;
  vec3 pixelDeltaV;

  void initialize() {
    imageHeight = int(imageWidth / aspectRatio);
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    pixelSamplesScale = 1.0f / samplesPerPixel;
    
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

  ray getRay(int h, int v) const {
    vec3 offset = sampleSquare();
    point3 pixelSample = pixel00Location + ((h + offset.x()) * pixelDeltaH) +
                         ((v + offset.y()) * pixelDeltaV);
    point3 rayOrigin = centre;
    vec3 rayDirection = pixelSample - rayOrigin;

    return ray(rayOrigin, rayDirection);
  }

  vec3 sampleSquare() const {
    return vec3(randomFloat() - 0.5f, randomFloat() - 0.5f, 0.0f);
  }

  color rayColor(const ray &r, int depth, const hittable &world) const {
    if (depth <= 0)
      return color(0.0f, 0.0f, 0.0f);
    
    hitRecord rec;

    if (world.hit(r, interval(0.001f, infinity), rec)) {
      vec3 direction = randomOnHemisphere(rec.normal);
      return 0.5f * rayColor(ray(rec.p, direction), depth-1, world);
    }

    vec3 unitDirection = unitVector(r.direction());
    float a = 0.5f * (unitDirection.y() + 1.0f);
    return (1.0f - a) * color(1.0f, 1.0f, 1.0f) + a * color(0.5f, 0.7f, 1.0f);
  }
};
