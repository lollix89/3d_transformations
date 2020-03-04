
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include "Transformations.h"

cv::Mat Transformations::rotate3D(cv::Mat &input,
                                  double rotation_around_x,
                                  double rotation_around_y,
                                  double rotation_around_z,
                                  double dx,
                                  double dy,
                                  double dz,
                                  double focal_length){

    rotation_around_x = rotation_around_x *CV_PI/180.;
    rotation_around_y = rotation_around_y *CV_PI/180.;
    rotation_around_z = rotation_around_z *CV_PI/180.;

    auto w = (double)input.cols;
    auto h = (double)input.rows;

    // Projection 2D -> 3D matrix
    cv::Mat A1 =
            (cv::Mat_<double>(4,3) <<
                                1, 0, -w/2,
                                0, 1, -h/2,
                                0, 0,    0,
                                0, 0,    1);

    // Rotation matrices around the X, Y, and Z axis
    cv::Mat RX =
            (cv::Mat_<double>(4, 4) <<
                     1,          0,           0,                         0,
                     0, cos(rotation_around_x), -sin(rotation_around_x), 0,
                     0, sin(rotation_around_x),  cos(rotation_around_x), 0,
                     0,          0,           0,                         1);

    cv::Mat RY =
            (cv::Mat_<double>(4, 4) <<
                 cos(rotation_around_y), 0, -sin(rotation_around_y), 0,
                    0,                   1,          0,              0,
                sin(rotation_around_y),  0,  cos(rotation_around_y), 0,
                    0,                   0,          0,              1) ;

    cv::Mat RZ =
            (cv::Mat_<double>(4, 4) <<
                 cos(rotation_around_z), -sin(rotation_around_z), 0, 0,
                sin(rotation_around_z),  cos(rotation_around_z),  0, 0,
                    0,                           0,               1, 0,
                    0,                           0,               0, 1);

    // Composed rotation matrix with (RX, RY, RZ)
    cv::Mat R = RX * RY * RZ;

    // Translation matrix
    cv::Mat T = (cv::Mat_<double>(4, 4) <<
            1, 0, 0, dx,
            0, 1, 0, dy,
            0, 0, 1, dz,
            0, 0, 0, 1);

    // 3D -> 2D matrix
    cv::Mat A2 =
            (cv::Mat_<double>(3,4) <<
                                   focal_length, 0, w / 2, 0,
                0,          focal_length, h / 2, 0,
                0,              0,         1,  0);

    // Final transformation matrix
    cv::Mat trans = A2 * (T * (R * A1));

    // Apply matrix transformation
    cv::Mat output;
    warpPerspective(input, output, trans, input.size(), cv::INTER_LANCZOS4);
    return output;
}

