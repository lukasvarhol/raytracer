#pragma once

#include "config.h"
#include "hittable.h"
#include "linear_algebra.h"

class material {
public:
  virtual ~material() = default;
  virtual bool scatter(const ray &rIn, const hitRecord &rec,
                       color &attentuation, ray &scattered) const {
    return false;
  }
};

class lambertian : public material {
public:
  lambertian(const color &albedo) : albedo(albedo) {}
  
  bool scatter(const ray &rIn, const hitRecord &rec, color &attenuation,
               ray &scattered) const override {
    vec3 scatterDirection = rec.normal + randomUnitVector();

    if (scatterDirection.nearZero())
      scatterDirection = rec.normal;

    scattered = ray(rec.p, scatterDirection, rIn.time());
    attenuation = albedo;
    return true;
  }
private:
  color albedo;
};

class metal : public material {
public:
  metal(const color &albedo, float fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

  bool scatter(const ray &rIn, const hitRecord &rec, color &attenuation, ray &scattered) const override {
    vec3 reflected = reflect(rIn.direction(), rec.normal);
    reflected = unitVector(reflected) + (fuzz * randomUnitVector());
    scattered = ray(rec.p, reflected, rIn.time());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

private:
  color albedo;
  float fuzz;
};

class dielectric : public material {
public:
  dielectric(const color& albedo, float refractionIndex ) : refractionIndex(refractionIndex), albedo(albedo) {}

  bool scatter(const ray &rIn, const hitRecord &rec, color &attenuation,
               ray &scattered) const override {
    attenuation = albedo;
    float ri = rec.frontFace ? (1.0f / refractionIndex) : refractionIndex;

    vec3 unitDirection = unitVector(rIn.direction());
    float cosTheta = std::fmin(dot(-unitDirection, rec.normal), 1.0f);
    float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

    bool cannotRefract = ri * sinTheta > 1.0f;
    vec3 direction =
        (cannotRefract || reflectance(cosTheta, ri) > randomFloat())
            ? reflect(unitDirection, rec.normal)
            : refract(unitDirection, rec.normal, ri);
    

    scattered = ray(rec.p, direction, rIn.time());
    
    return true;
  }

private:
  float refractionIndex;
  color albedo;

  static float reflectance(float cos, float refractionIndex) {
    float r0 =(1.0f - refractionIndex) / (1.0f + refractionIndex);
    r0 = r0 * r0;
    float c5 = (1-cos)*(1-cos)*(1-cos)*(1-cos)*(1-cos);
    return r0 + (1 - r0) * c5;
  }
};
