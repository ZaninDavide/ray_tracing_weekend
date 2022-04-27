#pragma once

#include <iostream>
#include "utils.h"

void write_color(std::ostream &out, const vec3 &color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(color.x, 0, 0.999999)) << ' '
        << static_cast<int>(256 * clamp(color.y, 0, 0.999999)) << ' '
        << static_cast<int>(256 * clamp(color.z, 0, 0.999999)) << '\n';
}