#include "camera.h"
#include "config.h"
#include "hittable.h"
#include "hittable_list.h"
#include "linear_algebra.h"
#include "sphere.h"
#include "material.h"
#include <memory>

int main() {
  hittableList world;

  std::shared_ptr<material> groundMaterial =
      std::make_shared<lambertian>(color(0.3f, 0.3f, 0.3f));
  world.add(std::make_shared<sphere>(point3(0.0f, -1000.0f, 0.0f), 1000.0f,
                                     groundMaterial));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      float chooseMaterial = randomFloat();
      point3 centre(a + 0.9f * randomFloat(), 0.2f, b + 0.9f * randomFloat());

      if ((centre - point3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
        std::shared_ptr<material> sphereMaterial;
        if (chooseMaterial < 0.8f) {
          // diffuse
          color albedo = color::random() * color::random();
          sphereMaterial = std::make_shared<lambertian>(albedo);
	  point3 centre2 = centre + vec3(0.0f, randomFloat(0.0f, 0.5f), 0.0f);
          world.add(std::make_shared<sphere>(centre, centre2, 0.2f, sphereMaterial));
        } else if (chooseMaterial < 0.95f) {
          // metal
          color albedo = color::random(0.5f, 1.0f);
          float fuzz = randomFloat(0.0f, 0.5f);
          sphereMaterial = std::make_shared<metal>(albedo, fuzz);
          world.add(std::make_shared<sphere>(centre, 0.2f, sphereMaterial));
        } else {
          // glass
          color albedo = color::random(0.85f, 1.0f);
          sphereMaterial = std::make_shared<dielectric>(albedo, 1.5f);
          world.add(std::make_shared<sphere>(centre, 0.2f, sphereMaterial));
        }
      }
    }
  }

  std::shared_ptr<material> material1 =
      std::make_shared<dielectric>(color(1.0f, 1.0f, 1.0f), 1.5f);
  world.add(std::make_shared<sphere>(point3(0.0f, 1.0f, 0.0f), 1.0f, material1));
  world.add(std::make_shared<sphere>(point3(-4.0f, 1.0f, 0.0f), 1.0f, material1));
  world.add(std::make_shared<sphere>(point3(4.0f, 1.0f, 0.0f), 1.0f, material1));

  camera cam;
  
  cam.aspectRatio = 16.0f / 9.0f;
  cam.imageWidth = 400;
  cam.samplesPerPixel = 50;
  cam.maxDepth = 50;

  cam.vFoV = 20.0f;
  cam.lookFrom = point3(13.0f, 2.0f, 3.0f);
  cam.lookAt = point3(0.0f, 0.0f, 0.0f);
  cam.upDir = vec3(0.0f, 1.0f, 0.0f);

  cam.defocusAngle = 0.6f;
  cam.focusDist = 10.0f;
  
  cam.render(world);
}
