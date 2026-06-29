#pragma once

#include "config.h"
#include "hittable.h"

class sphere : public hittable {
public:
  sphere(const point3 &centre, float radius)
      : centre(centre), radius(std::fmax(0.0f, radius)) {}

  bool hit(const ray &r, float ray_tmin, float ray_tmax,
           hitRecord &rec) const override {
    vec3 rayOriginToCentre = centre - r.origin();
    float a = r.direction().length_squared();
    float h = dot(r.direction(), rayOriginToCentre);
    float c = rayOriginToCentre.length_squared() - radius * radius;

    float discriminant = h * h - a * c;
    if (discriminant < 0)
      return false;

    float sqrtDisc = std::sqrt(discriminant);

    // find nearest root within defined range
    float root = (h - sqrtDisc) / a;
    if (root <= ray_tmin || ray_tmax <= root) {
      root = (h + sqrtDisc) / a;
      if (root <= ray_tmin || ray_tmax <= root)
        return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outwardNormal = (rec.p - centre) / radius;
    rec.setFaceNormal(r, outwardNormal);

    return true;
  }

private:
  point3 centre;
  float radius;
};
