#pragma once

#include "linear_algebra.h"

struct ray {
  ray() {}
  ray(const point3 &o, const vec3 &d) : origin_(o), direction_(d) {}

  const point3 &origin() const { return origin_; }
  const vec3& direction() const { return direction_; }

  point3 at(float t) { return origin_ + (t * direction_); }

private:
  point3 origin_;
  vec3 direction_;
};

