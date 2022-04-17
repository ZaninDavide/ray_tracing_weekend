#pragma once

#include "ray.h"

struct hit_res {
    vec3 point;
    vec3 normal;
    double t;
    bool front;
    
    inline void set_face_normal(const ray& r, const vec3& outward_normal) {
        front = dot(r.dir, outward_normal) < 0;
        normal = front ? outward_normal :-outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(const ray& r, double t_min, double t_max, hit_res& res) const = 0;
    virtual ~hittable() = default;
};

class sphere : public hittable {
public:
    vec3 center;
    double radius;
public:
    sphere() {}
    sphere(vec3 center, double radius) : center(center), radius(radius) {}  
    ~sphere() = default;
    
    bool hit(const ray& r, double t_min, double t_max, hit_res& res) const override {
        vec3 oc = r.origin - center;
        double a = r.dir.len2();
        double half_b = dot(oc, r.dir);
        double c = oc.len2() - radius*radius;
        double discriminant = half_b*half_b - a*c;

        if (discriminant < 0) return false;

        double sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        double root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        res.t = root;
        res.point = r.at(res.t);
        vec3 out_normal = (res.point - center) / radius;
        res.set_face_normal(r, out_normal);
        
        return true;
    }
};