#include <iostream>
#include <cstdlib>
#include <ctime>

#include "camera.h"
#include "hitable.h"
#include "hitable_list.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"

vec3 color(const ray& r, hitable *world, int depth) {
  hit_record rec;
  /*
   * Ignore hits close to 0 to mitigate shadow acne.
   * Shadow acne is caused by the discrete nature of the shadow map.
   * One way of resolving this is using a bias
   */
  if (world->hit(r, 0.001, MAXFLOAT, rec)) {
    ray scattered;
    vec3 attenuation;

    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation * color(scattered, world, depth+1);
    } else {
      return vec3(0,0,0);
    }
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
  int ns = 15;

  // Define size and max color for image
  std::cout << "P3\n" << nx << " " << ny << "\n255\n";

  // initialize camera
  camera cam;

  // initialize world objects
  hitable *list[4];
  list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
  list[1] = new sphere(vec3(0,-100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
  list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.5, 0.2)));
  list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8, 0.8, 0.8)));
  hitable_list *world = new hitable_list(list, 4);

  for (int j = ny-1; j >= 0; j--) {
    for (int i = 0; i < nx; i++) {
      vec3 col(0.0, 0.0, 0.0);

      // add simple anti-aliasing
      for (int s=0; s < ns; s++) {
        float u = float(i + get_rand()) / float(nx);
        float v = float(j + get_rand()) / float(ny);

        ray r = cam.get_ray(u, v);
        col += color(r, world, 0);
      }
      col /= float(ns);

      /*
       * For a first approximation, use gamma 2 which
       * means raising the color to the power of 1/gamma
       */
      col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );

      int ir = int(255.99*col[0]);
      int ig = int(255.99*col[1]);
      int ib = int(255.99*col[2]);
      std::cout << ir << " " << ig << " " << ib << "\n";
      //std::cout << j << "," << i << "\n";
    }
  }
}
