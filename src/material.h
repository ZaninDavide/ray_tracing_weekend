#pragma once

#include "vec3.h"
#include "ray.h"
#include "hittable.h"

// Every material is defined by how it scatters and absorbs rays
class material {
public:
    virtual bool scatter(const ray& rin, const hit_res& hit, vec3& attenuation, ray& scattered) const = 0;
};


// basic diffuse material
class lambertian : public material {
public:
    vec3 albedo;
public:
    lambertian() {}
    lambertian(const vec3& color) : albedo(color) {}

    bool scatter(const ray& rin, const hit_res& hit, vec3& attenuation, ray& scattered) const override {
        scattered = ray(hit.point, hit.normal + random_on_unit_sphere());
        if(scattered.dir.is_small()) scattered.dir = hit.normal;
        attenuation = albedo;
        return true;
    }
};

// basic metallic material
class metal : public material {
public:
    vec3 albedo;
public:
    metal() {}
    metal(const vec3& color) : albedo(color) {}

    bool scatter(const ray& rin, const hit_res& hit, vec3& attenuation, ray& scattered) const override {
        scattered = ray(hit.point, reflect(unit(rin.dir), hit.normal));
        attenuation = albedo;
        // avoid scattering towards the inside of the object
        return dot(scattered.dir, hit.normal) > 0;
    }
};