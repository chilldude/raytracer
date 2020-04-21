#include <iostream>
#include "ray.h"
#include "hitable.h"
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include <cstdlib>
#include <ctime>

vec3 color(const ray& r, hitable *world) {
  hit_record rec;
  if (world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5 * vec3(rec.normal.x()+1.0, rec.normal.y()+1.0, rec.normal.z()+1.0);
  } else {
    //vec3 unit_direction = r.direction().make_unit_vector();
    vec3 unit_direction = unit_vector(r.direction());

    // t depends on the up/downness of y
    float t = 0.5 * (unit_direction.y() + 1.0);

    // When t is 0, we want white
    // When t is 1, we want blue
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  srand(time(NULL));
  int nx = 800;
  int ny = 400;
  int ns = 100;

  // Define size and max color for image
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // initialize camera
  camera cam;

  // initialize world objects
  hitable *list[2];
  list[0] = new sphere(vec3(0,0,-1), 0.5);
  list[1] = new sphere(vec3(0,-100.5, -1), 100);
  hitable_list *world = new hitable_list(list, 2);

  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0.0, 0.0, 0.0);

      // add simple anti-aliasing
      for (int s=0; s < ns; s++) {
        float u = float(i + (((double) rand() / (RAND_MAX)) + 1)) / float(nx);
        float v = float(j + (((double) rand() / (RAND_MAX)) + 1)) / float(ny);

        ray r = cam.get_ray(u, v);
        col += color(r, world);
      }
      col /= float(ns);

      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}
