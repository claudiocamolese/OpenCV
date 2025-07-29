#include <iostream>
#include <opencv2/opencv.hpp>

/**
 * @brief This function applies a sequence of image transformations (color space conversion,
 *        image downscaling, and Canny edge detection), displaying each intermediate result.
 *
 * @param img - The input image (cv::Mat)
 */
void SequentialTransformations(const cv::Mat& img) {
    cv::Mat out, pyr, can;

    // Convert to HLS color space
    cv::cvtColor(img, out, cv::COLOR_BGR2HLS);
    cv::imshow("cvtColor (BGR2HLS)", out);

    // Downscale the image by half
    cv::pyrDown(out, pyr);
    cv::imshow("pyrDown (scaled down)", pyr);

    // Apply Canny edge detection
    cv::Canny(pyr, can, 10, 100, 3, true);
    cv::imshow("Canny Edges", can);

    cv::waitKey(0);
}

int main(int argc, char** argv) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path>\n";
        return 1;
    }

    cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "❌ Error: Could not load image from " << argv[1] << "\n";
        return 1;
    }

    cv::imshow("Original Image", img);
    cv::waitKey(0);

    SequentialTransformations(img);
    return 0;
}
