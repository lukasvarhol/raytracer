#pragma once

#include "linear_algebra.h"

struct ray {
  ray() {}
  ray(const point3 &origin, const vec3 &direction, float time)
      : origin_(origin), direction_(direction), time_(time) {}

  ray(const point3 &origin, const vec3 &direction)
      : ray(origin, direction, 0.0f) {}

  const point3 &origin() const { return origin_; }
  const vec3& direction() const { return direction_; }

  float time() const { return time_; }

  point3 at(float t) const { return origin_ + (t * direction_); }

private:
  point3 origin_;
  vec3 direction_;
  float time_;
};

