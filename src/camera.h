#include "vec3.h"
#include "ray.h"
#include "utils.h"

class camera {
    public:
        camera() {
                // CAMERA
                double view_height = 2.0;
                double view_width = (double)(HEIGHT)/(double)(WIDTH) * view_height;
                double focal_length = 1.0;
                double aspect_ration = (double)(WIDTH)/(double)(HEIGHT);

                // https://raytracing.github.io/images/fig-1.03-cam-geom.jpg  
                // position in 3D space of the bottom left corner of the view frame
                // the focal length has to be subtracted because the z axes goes towards the camera
                
                origin = vec3(0);
                bottom_left = vec3(-view_width/2, -view_height/2, -focal_length);
                left_to_right = vec3(view_width, 0, 0);
                bottom_to_top = vec3(0, view_height, 0);
        }

        ray get_ray(double u, double v) const {
            return ray(origin, bottom_left + u*left_to_right + v*bottom_to_top - origin);
        }

    private:
        vec3 origin;
        vec3 bottom_left;
        vec3 left_to_right;
        vec3 bottom_to_top;
};