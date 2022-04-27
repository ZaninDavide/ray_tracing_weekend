#include <iostream>

#include "vec3.h" 
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "hittable_list.h"
#include "utils.h"
#include "camera.h"
#include "material.h"

#define SAMPLES 10
#define DIFFUSE_BOUNCES 25

vec3 ray_color(const ray& r, const hittable& world, uint depth = 0) {
    // stop recursion
    if(depth >= DIFFUSE_BOUNCES) return vec3(0);

    // check if we hit the sphere
    hit_res hit;
    if (world.hit(r, 0.001, infinity, hit)){
        // if we hit something keep bouncing the light
        // to bounce the light we have to choose a rondom direction
        // we use the tangent unit sphere technique to make more probable
        // to bounce the light perpendicular to the surface
        // rather than at a shallow angle
        // vec3 target = hit.point + hit.normal + random_in_unit_sphere();
        // ray new_ray = ray(hit.point, target - hit.point);
        // Different diffuse distributions: random_in_unit_sphere, random_on_unit_sphere, random_in_hemisphere
        ray new_ray;
        vec3 attenuation;
        // use the material of the hit object to scatter the light rays
        if(hit.mat->scatter(r, hit, attenuation, new_ray)) {
            // light was scatterd
            return attenuation * ray_color(new_ray, world, depth + 1);
        }
        return vec3(0); // the light was absorbed
    }

    // we use the y component (up and down) to interpolate between two shades of blue
    double t = 0.5*(unit(r.dir).y + 1.0);
    return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}

// https://raytracing.github.io/books/RayTracingInOneWeekend.html
int main() {

    // WORLD
    hittable_list world;
    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5, make_shared<metal>(vec3(0,1,0))));
    world.add(make_shared<sphere>(vec3(0, -1000.5, -1), 1000, make_shared<lambertian>(vec3(1,1,1))));
    world.add(make_shared<sphere>(vec3(0.9, 0, -1), 0.2, make_shared<lambertian>(vec3(0.4,0.2,0.8))));

    camera cam;

    // RENDER
    std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
    // we need to calculate the pixels in this order because of the ppm file format
    for (int j = HEIGHT - 1; j >= 0; --j) {
        // this will be printed in console but won't end up inside the image file
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < WIDTH; ++i) {
            vec3 pixel = vec3(0);
            // MULTI-SAMPLING
            for(int s = 0; s < SAMPLES; s++) {
                // uv coordinates
                double u = ((double)(i) + random_double()) / (double)(WIDTH - 1); // from 0 to 1, from left to right
                double v = ((double)(j) + random_double()) / (double)(HEIGHT - 1); // from 0 to 1, from bottom to top
                pixel += ray_color(cam.get_ray(u, v), world);
            }
            pixel /= (double)SAMPLES;
            // gamma correction
            pixel = vec3(sqrt(pixel.x), sqrt(pixel.y), sqrt(pixel.z));
            // output color
            write_color(std::cout, pixel);
        }
    }

    std::cerr << "\nDone.\n";
}