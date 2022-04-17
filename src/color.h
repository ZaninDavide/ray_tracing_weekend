#pragma once

#include <iostream>

void write_color(std::ostream &out, const vec3 &color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * color.x) << ' '
        << static_cast<int>(255.999 * color.y) << ' '
        << static_cast<int>(255.999 * color.z) << '\n';
}