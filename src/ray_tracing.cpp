#include <iostream>

#include "vec3.h" 
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "utils.h"

#define WIDTH 1024
#define HEIGHT 1024

vec3 ray_color(const ray& r, const hittable& world) {
    // check if we hit the sphere
    hit_res hit;
    if (world.hit(r, 0.01, 100, hit)){
        return hit.normal/2 + 0.5;
    }

    // we use the y component (up and down) to interpolate between two shades of blue
    double t = 0.5*(unit(r.dir).y + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

// https://raytracing.github.io/books/RayTracingInOneWeekend.html
int main() {

    // CAMERA
    double view_height = 2.0;
    double view_width = (double)(HEIGHT)/(double)(WIDTH) * view_height;
    double focal_length = 1.0;

    // https://raytracing.github.io/images/fig-1.03-cam-geom.jpg  
    // position in 3D space of the bottom left corner of the view frame
    // the focal length has to be subtracted because the z axes goes towards the camera
    vec3 origin(0);
    vec3 bottom_left = vec3(-view_width/2, -view_height/2, -focal_length);
    vec3 left_to_right = vec3(view_width, 0, 0);
    vec3 bottom_to_top = vec3(0, view_height, 0);

    // WORLD
    hittable_list world;
    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(vec3(0, 0.5, -1), 0.25));

    // RENDER
    std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
    // we need to calculate the pixels in this order because of the ppm file format
    for (int j = HEIGHT - 1; j >= 0; --j) {
        // this will be printed in console but won't end up inside the image file
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < WIDTH; ++i) {
            // uv coordinates
            double u = (double)(i) / (double)(WIDTH - 1); // from 0 to 1, from left to right
            double v = (double)(j) / (double)(HEIGHT - 1); // from 0 to 1, from bottom to top

            // ray from the origin toward the pixel (i, j)
            ray r(origin, bottom_left + u*left_to_right + v*bottom_to_top);

            // output color
            write_color(std::cout, ray_color(r, world));
        }
    }

    std::cerr << "\nDone.\n";
}