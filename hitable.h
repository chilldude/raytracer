#ifndef HITABLEH
#define HITABLEH

#include"ray.h"

/*
 * material tells us how rays interact with the surface
 */
class material;

/*
 * hit_record is a way to group a bunch of relevant arguments
 * into a single struct so they can be passed as a group
 */
struct hit_record {
  float t;
  vec3 p;
  vec3 normal;
  material *mat_ptr;
};

class hitable {
  public:
    virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif
