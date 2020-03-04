#ifndef INC_3D_TRANSFORM_TRANSFORMATIONS_H
#define INC_3D_TRANSFORM_TRANSFORMATIONS_H

namespace Transformations {

    cv::Mat rotate3D(cv::Mat &input,
                     double rotation_around_x,
                     double rotation_around_y,
                     double rotation_around_z,
                     double dx,
                     double dy,
                     double dz,
                     double focal_length);
};

#endif //INC_3D_TRANSFORM_TRANSFORMATIONS_H
