#include "camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"

int main() {
  hittableList world;

  world.add(std::make_shared<sphere>(point3(0.0f, 0.0f, -1.0f), 0.5f));
  world.add(std::make_shared<sphere>(point3(0.0f, -100.5f, -1.0f), 100.0f));

  camera cam;

  cam.aspectRatio = 16.0f / 9.0f;
  cam.imageWidth = 400;
  cam.samplesPerPixel = 100;
  cam.maxDepth = 50;
  
  cam.render(world);
}
