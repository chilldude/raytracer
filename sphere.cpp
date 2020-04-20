#include <iostream>
#include "ray.h"

float hit_sphere(const vec3& center, float radius, const ray& r) {
  // to check if a ray hits
  vec3 oc = r.origin() - center;

  // If the discriminant is positive, then it means
  // there is at least 1 real solution and therefore
  // the ray hits the sphere.
  float a = dot(r.direction(), r.direction());
  float b = 2.0 * dot(r.direction(), oc);
  float c = dot(oc, oc) - radius*radius;

  float discriminant = b*b - 4*a*c;

  if (discriminant < 0) {
    return -1.0;
  }
  else {
    return (-b - sqrt(discriminant)) / (2.0 * a);
  }
}

vec3 color(const ray& r) {
  vec3 sphere_center(0.0, 0.0, -1.0);
  float radius = 0.5;

  float t = hit_sphere(sphere_center, radius, r);

  if (t > 0) {
    // unit  vectors have components between -1 and 1
    vec3 N = unit_vector(r.point_at_parameter(t) - sphere_center);

    // map each component to the interval between 0 and 1
    return 0.5 * vec3(N.x() + 1.0, N.y() + 1.0, N.z() + 1.0);
  }

  //vec3 unit_direction = r.direction().make_unit_vector();
  vec3 unit_direction = unit_vector(r.direction());

  // t depends on the up/downness of y
  t = 0.5 * (unit_direction.y() + 1.0);

  // When t is 0, we want white
  // When t is 1, we want blue
  return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main() {
  int nx = 800;
  int ny = 400;

  // Define size and max color for image
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  vec3 lower_left_corner(-2.0, -1.0, -1.0);
  vec3 horizontal(4.0, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);

      ray r(origin, lower_left_corner + u*horizontal + v*vertical);
      vec3 col = color(r);

      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
