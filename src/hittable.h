#pragma once

#include "config.h"

class material;

class hitRecord {
public:
  point3 p;
  vec3 normal;
  std::shared_ptr<material> mat;
  float t;
  bool frontFace;

  void setFaceNormal(const ray &r, const vec3 &outwardNormal) {
    frontFace = dot(r.direction(), outwardNormal) < 0;
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(const ray &r, interval ray_t, hitRecord &rec) const = 0;
};
