#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"
#include <memory>

int main() {
  hittableList world;

  std::shared_ptr<material> materialGround = std::make_shared<lambertian>(color(0.8f, 0.8f, 0.0f));
  std::shared_ptr<material> materialCentreSphere =
      std::make_shared<lambertian>(color(0.1f, 0.2f, 0.5f));
  std::shared_ptr<material> materialLeftSphere =
    std::make_shared<metal>(color(0.8f, 0.8f, 0.8f), 0.5f);
  std::shared_ptr<material> materialRightSphere =
      std::make_shared<dielectric>(color(0.5f, 0.7f, 1.0f), 1.5f);
  std::shared_ptr<material> materialBubble = std::make_shared<dielectric>(color(1.0f, 1.0f, 1.0f), 0.67f);

  
  world.add(std::make_shared<sphere>(point3(0.0f, -100.5f, -1.0f), 100.0f,
                                     materialGround));
  world.add(std::make_shared<sphere>(point3(0.0f, 0.0f, -1.5f), 0.5f,
                                     materialCentreSphere));
  world.add(std::make_shared<sphere>(point3(-1.2f, 0.3f, -1.0f), 0.7f,
                                     materialLeftSphere));
  world.add(std::make_shared<sphere>(point3(1.55f, 0.8f, -1.0f), 1.3f,
                                     materialRightSphere));
  world.add(std::make_shared<sphere>(point3(1.55f, 0.8f, -1.0f), 1.0f,
                                     materialBubble));

  camera cam;

  
  cam.aspectRatio = 16.0f / 9.0f;
  cam.imageWidth = 640;
  cam.samplesPerPixel = 100;
  cam.maxDepth = 50;
  
  cam.render(world);
}
