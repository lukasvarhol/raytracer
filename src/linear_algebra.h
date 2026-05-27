#pragma once

#include <cmath>
#include <iostream>

struct vec3 {
  float e[3];

  vec3(float a, float b, float c) : e{a, b, c} {}
  vec3() : e{0.0f, 0.0f, 0.0f} {}

  float x() const { return e[0]; }
  float y() const { return e[1]; }
  float z() const { return e[2]; }

  float length_squared() const {
    return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
  }
  float length() const { return std::sqrt(length_squared()); }
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
  return a.e[0]*a.e[0] + a.e[1]*a.e[1] + a.e[2]*a.e[2];
}

inline vec3 cross(const vec3 &a, const vec3 &b) {
  return vec3(a.e[1] * b.e[2] - a.e[2] * b.e[1],
              a.e[2] * b.e[0] - a.e[0] * b.e[2],
	      a.e[0] * b.e[1] - a.e[1] * b.e[0]);
}

inline vec3 unitVector(const vec3 &v) {
  return v / v.length();
}

