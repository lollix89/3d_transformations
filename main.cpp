#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "Transformations.h"

struct Rotation3D {
    int x_axe{0};
    int y_axe{0};
    int z_axe{0};
};

struct DataBundle {
    Rotation3D rotation_3d;
    cv::Mat original_image;
};

auto window_title = "trackbar_test";

void on_trackbar_event(int position, void* args )
{
    auto data_bundle = (DataBundle*)args;

    auto transformed_img = Transformations::rotate3D(data_bundle->original_image,
            data_bundle->rotation_3d.x_axe,
            data_bundle->rotation_3d.y_axe,
            data_bundle->rotation_3d.z_axe,
            0, 0, 10, 10);
    cv::imshow(window_title, transformed_img);
}


int main() {

    cv::namedWindow(window_title, CV_WINDOW_NORMAL);

    DataBundle data_bundle;
    data_bundle.original_image = cv::imread("../cat.jpg");
    cv::resize(data_bundle.original_image, data_bundle.original_image, cv::Size(), .5, .5);

    // Create track bar
    auto x_rotation_value = 0;
    auto x_rotation_value_max = 360;
    cv::createTrackbar("rotation x axe", window_title,
                       &data_bundle.rotation_3d.x_axe, x_rotation_value_max, on_trackbar_event, &data_bundle);

    // Create track bar
    auto y_rotation_value = 0;
    int y_rotation_value_max = 360;
    cv::createTrackbar("rotation y axe", window_title,
                       &data_bundle.rotation_3d.y_axe, y_rotation_value_max, on_trackbar_event, &data_bundle);

    // Create track bar
    auto z_rotation_value = 0;
    int z_rotation_value_max = 360;
    cv::createTrackbar("rotation z axe", window_title,
                       &data_bundle.rotation_3d.z_axe, z_rotation_value_max, on_trackbar_event, &data_bundle);

    cv::imshow(window_title, data_bundle.original_image);
    cv::waitKey(0);

    return 0;
}
