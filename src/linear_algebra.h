#pragma once

#include "config.h"
#include <cmath>

struct vec3 {
  float e[3];

  vec3(float a, float b, float c) : e{a, b, c} {}
  vec3() : e{0.0f, 0.0f, 0.0f} {}

  float x() const { return e[0]; }
  float y() const { return e[1]; }
  float z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  float operator[](int i) const { return e[i]; }
  float& operator[](int i ) {return e[i]; }

  float length_squared() const {
    return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
  }

  bool nearZero() const {
    float s = 1e-8f;
    return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
           (std::fabs(e[2]) < s);
  }
    
  float length() const { return std::sqrt(length_squared()); }

  static vec3 random() {
    return vec3(randomFloat(), randomFloat(), randomFloat());
  }

  static vec3 random(float min, float max) {
    return vec3(randomFloat(min, max), randomFloat(min, max),
                randomFloat(min, max));
  }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &a, const vec3 &b) {
  return vec3((a.e[0] + b.e[0]), (a.e[1] + b.e[1]), (a.e[2] + b.e[2]));
}

inline vec3 operator-(const vec3 &a, const vec3 &b) {
  return vec3((a.e[0] - b.e[0]), (a.e[1] - b.e[1]), (a.e[2] - b.e[2]));
}

inline vec3 operator*(const vec3 &a, const vec3 &b) {
  return vec3((a.e[0] * b.e[0]), (a.e[1] * b.e[1]), (a.e[2] * b.e[2]));
}

inline vec3 operator/(const vec3 &a, const vec3 &b) {
  return vec3((a.e[0] / b.e[0]), (a.e[1] / b.e[1]), (a.e[2] / b.e[2]));
}

inline vec3 operator*(const float s, const vec3& v) {
  return vec3(s*v.e[0], s*v.e[1], s*v.e[2]);
}

inline vec3 operator/(const vec3 &v, const float s) {
  return vec3(v.e[0]/s, v.e[1]/s, v.e[2]/s);
}

inline vec3 operator*(const vec3 &v, const float s) {
    return vec3(s*v.e[0], s*v.e[1], s*v.e[2]);
}

inline float dot(const vec3 &a, const vec3 &b) {
  return a.e[0]*b.e[0] + a.e[1]*b.e[1] + a.e[2]*b.e[2];
}

inline vec3 cross(const vec3 &a, const vec3 &b) {
  return vec3(a.e[1] * b.e[2] - a.e[2] * b.e[1],
              a.e[2] * b.e[0] - a.e[0] * b.e[2],
	      a.e[0] * b.e[1] - a.e[1] * b.e[0]);
}

inline vec3 unitVector(const vec3 &v) { return v / v.length(); }

inline vec3 randomUnitVector() {
  while (true) {
    vec3 p = vec3::random(-1.0f, 1.0f);
    float lengthSquared = p.length_squared();
    if (1e-160 < lengthSquared && lengthSquared <= 1)
      return p / sqrt(lengthSquared);
  }
}

inline vec3 randomOnHemisphere(const vec3 &normal) {
  vec3 onUnitSphere = randomUnitVector();
  if (dot(onUnitSphere, normal) > 0.0f)
    return onUnitSphere;
  else
    return -onUnitSphere;
}

inline vec3 reflect(const vec3 &v, const vec3 &n) {
  return v - 2 * dot(v, n) * n;
}
