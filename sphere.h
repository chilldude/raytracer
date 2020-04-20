#ifndef SPHEREH
#define SPHEREH

#include"hitable.h"

class sphere: public hitable {
  public:
    sphere() {}
    sphere(vec3 c, float r) : center(c), radius(r) {};
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    vec3 center;
    float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  vec3 oc = r.origin() - center;

  // If the discriminant is positive, then it means
  // there is at least 1 real solution and therefore
  // the ray hits the sphere.
  float a = dot(r.direction(), r.direction());
  float b = dot(r.direction(), oc);
  float c = dot(oc, oc) - radius*radius;
  float discriminant = b*b - a*c;

  if (discriminant > 0) {
    float temp = (-b - sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);

      // shortcut to make unit normal vector
      rec.normal = (rec.p - center) / radius;
      return true;
    }
    temp = (-b + sqrt(discriminant)) / a;
    if (temp < t_max && temp > t_min) {
      rec.t = temp;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      return true;
    }
  }
  return false;
}

#endif