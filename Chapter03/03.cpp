#include <opencv2/opencv.hpp>


/*
This code applies a sky filter to an image using OpenCV.
It defines a function `sky_filter` that detects blue regions in the image (representing the sky)
and applies a Gaussian blur to those regions. The main function reads an image from a file,
applies the sky filter, and displays the results.
*/

void sky_filter(const cv::Mat& src, cv::Mat& dst) {

    /**
     * @brief Applies a sky filter to the input image.
     * @param src Input image.
     * @param dst Output image with sky regions blurred.
     */
    cv::Mat hsv, mask;

    // Change color space to HSV. THis helps in better color detection.
    // HSV is more suitable for color-based segmentation.
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
    cv::imshow("Original Image", src);
    cv::imshow("HSV Image", hsv);

    // Create a mask for blue regions in the image
    // Hue for blu is in range ≈ [100, 130]
    cv::inRange(hsv, cv::Scalar(100, 50, 50), cv::Scalar(130, 255, 255), mask);

    // 3. Smoothing: create a blurred version of the original image
    cv::Mat blurred;
    cv::GaussianBlur(src, blurred, cv::Size(15, 15), 0);

    // 4. Combine the original image and the blurred image using the mask
    // The mask will determine where to apply the blur
    dst = src.clone();
    blurred.copyTo(dst, mask);  // Copy the blur where the mask is active
}


int main(int argc, char** argv) {

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    cv::Mat img = (argc >= 2) ? cv::imread(argv[1]) : cv::imread("..\\images\\lake.jpg");
    if (img.empty()) return -1;

    cv::Mat result;
    sky_filter(img, result);

    cv::imshow("Original", img);
    cv::imshow("Sky Filtered", result);
    cv::waitKey(0);
    return 0;
}
