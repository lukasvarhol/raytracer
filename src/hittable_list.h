#pragma once

#include "config.h"
#include "hittable.h"
#include <vector>

class hittableList : public hittable {
public:
  std::vector<std::shared_ptr<hittable>> objects;

  hittableList() {}
  hittableList(std::shared_ptr<hittable> object) { add(object); }

  void clear() { objects.clear(); }

  void add(std::shared_ptr<hittable> object) { objects.push_back(object); }

  bool hit(const ray &r, interval ray_t, hitRecord &rec) const override {
    hitRecord tempRec;
    bool hitAnything = false;
    float closestYet = ray_t.max;

    for (const auto &object : objects) {
      if (object->hit(r, interval(ray_t.min, closestYet), tempRec)) {
        hitAnything = true;
        closestYet = tempRec.t;
        rec = tempRec;
      }
    }

    return hitAnything;
  }
};

