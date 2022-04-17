#pragma once

#include <memory>
#include <vector>

#include "hittable.h"

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    std::vector<shared_ptr<hittable>> objects; 
public:
    hittable_list() {}
    
    void clear() { objects.clear(); }
    void add(shared_ptr<hittable> obj) { objects.push_back(obj); }

    bool hit(const ray& r, double t_min, double t_max, hit_res& res) const override {
        hit_res temp;
        bool did_hit = false;
        res.t = t_max;      
        // check against all objects and hit the closest one
        for(const shared_ptr<hittable>& object : objects) {
            if(object->hit(r, t_min, t_max, temp)) {
                did_hit = true;
                if(temp.t < res.t) {
                    res = temp;
                }
            }
        }

        return did_hit;
    }
};