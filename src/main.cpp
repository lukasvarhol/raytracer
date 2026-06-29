#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

int main() {
  hittableList world;

  std::shared_ptr<material> materialGround = std::make_shared<lambertian>(color(0.8f, 0.8f, 0.0f));
  std::shared_ptr<material> materialCentreSphere =
      std::make_shared<lambertian>(color(0.1f, 0.2f, 0.5f));
  std::shared_ptr<material> materialLeftSphere =
      std::make_shared<metal>(color(0.8f, 0.8f, 0.8f));
  std::shared_ptr<material> materialRighteSphere =
      std::make_shared<metal>(color(0.8f, 0.6f, 0.2f));

  world.add(std::make_shared<sphere>(point3(0.0f, -100.5f, -1.0f), 100.0f,
                                     materialGround));
  world.add(std::make_shared<sphere>(point3(0.0f, 0.0f, -1.2f), 0.5f,
                                     materialCentreSphere));
  world.add(std::make_shared<sphere>(point3(-1.0f, 0.0f, -1.0f), 0.5f,
                                     materialLeftSphere));
    world.add(std::make_shared<sphere>(point3(1.0f, 0.0f, -1.0f), 0.5f, materialRighteSphere));

  camera cam;

  cam.aspectRatio = 16.0f / 9.0f;
  cam.imageWidth = 400;
  cam.samplesPerPixel = 100;
  cam.maxDepth = 50;
  
  cam.render(world);
}
