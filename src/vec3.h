#pragma once

#include <cmath>
#include <iostream>

class vec3 {
public:
    double x, y, z;

public:
    vec3(double x, double y, double z) : x(x), y(y), z(z) {}
    vec3(double constant) : x(constant), y(constant), z(constant) {}
    vec3() {}

    double operator[](int i) const { return (double)(*this)[i]; }
    double& operator[](int i) { return (double&)(*this)[i];  }

    void operator+=(const vec3 &v) {
        x += v.x; y += v.y; z += v.z;
    }
    void operator-=(const vec3 &v) {
        x -= v.x; y -= v.y; z -= v.z;
    }    
    void operator+=(const double t) {
        x += t; y += t; z += t;
    }
    void operator-=(const double t) {
        x -= t; y -= t; z -= t;
    }
    void operator*=(const double t) {
        x *= t; y *= t; z *= t;
    }
    void operator/=(const double t) {
        x /= t; y /= t; z /= t;
    }
    vec3 operator-() const { 
        return vec3(-x, -y, -z); 
    }

    double len() const {
        return sqrt(x*x + y*y + z*z);
    }
    double len2() const {
        return x*x + y*y + z*z;
    }
};

// utlities for vec3

inline std::ostream& operator<<(std::ostream &out, const vec3 &v) {
    return out << v.x << ' ' << v.y << ' ' << v.z;
}

// vec-vec operations
inline vec3 operator+(const vec3 v, const vec3 w){
    return vec3(v.x + w.x, v.y + w.y, v.z + w.z);
}
inline vec3 operator-(const vec3 v, const vec3 w){
    return vec3(v.x - w.x, v.y - w.y, v.z - w.z);
}
inline vec3 operator*(const vec3 v, const vec3 w){
    return vec3(v.x * w.x, v.y * w.y, v.z * w.z);
}

//vec-double operations
inline vec3 operator*(const vec3 &v, double t) {
    return vec3(v.x * t, v.y * t, v.z * t);
}
inline vec3 operator*(double t, const vec3 &v) {
    return vec3(v.x * t, v.y * t, v.z * t);
}
inline vec3 operator/(const vec3 &v, double t) {
    return vec3(v.x / t, v.y / t, v.z / t);
}

// vector algebra
inline double dot(const vec3 &v, const vec3 &w) {
    return v.x*w.x + v.y*w.y + v.z*w.z;
}
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(
        u.y * v.z - u.z * v.y,
        u.z * v.x - u.x * v.z,
        u.x * v.y - u.y * v.x
    );
}
inline vec3 unit(const vec3 &v) {
    return v / v.len();
}
inline vec3 abs(const vec3 &v) {
    return vec3(abs(v.x), abs(v.y), abs(v.z));
}