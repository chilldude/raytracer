#ifndef MATERIALH
#define MATERIALH

#include "ray.h"

class material {
  public:
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

// Returns a float between 0 and 1
float get_rand() {
  return 0.5 * (((double) rand() / (RAND_MAX)) + 1);
}

vec3 random_point_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0*vec3(get_rand(), get_rand(), get_rand()) - vec3(1,1,1);
  } while (p.squared_length() >= 1.0);
  return p;
}

/*
 * For the Lambertian case, we always scatter and attenuate
 * by its reflectance
 */
class lambertian : public material {
  public:
    lambertian(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
      vec3 target = rec.p + rec.normal + random_point_in_unit_sphere();
      scattered = ray(rec.p, target - rec.p);
      attenuation = albedo;
      return true;
    }

    vec3 albedo;
};

class metal : public material {
  public:
    metal(const vec3& a) : albedo(a) {}
    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
      vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
      scattered = ray(rec.p, reflected);
      attenuation = albedo;

      // TODO: explain this
      return dot(scattered.direction(), rec.normal) > 0;
      //return dot(reflected, rec.normal) > 0;
    }

    vec3 albedo;
};

#endif
