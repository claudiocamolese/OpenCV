#include <iostream>
#include <opencv2/opencv.hpp>

/* 
This code applies a serie of sequental operation on a given image. 
*/


void SequentialTransformations(cv::Mat& img) {

    /**
 * @brief This function applies a sequence of image transformations (color space conversion,
 *        image downscaling, and Canny edge detection), displaying each intermediate result.
 *
 * @param img - The input image (cv::Mat)
 */

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

    // Extract the color of the central pixel
    int centerY = img.rows / 2;  // Y = riga
    int centerX = img.cols / 2;  // X = colonna
    cv::Vec3b center_pixel = img.at<cv::Vec3b>(centerY, centerX);  // corretto ordine (riga, colonna)

    std::cout << "At pixel: (" << centerX << "," << centerY << ")"
            << ", the values of pixels are: "
            << (int)center_pixel[0] << ","
            << (int)center_pixel[1] << ","
            << (int)center_pixel[2] << std::endl;

    // Change the color of the central pixel
    img.at<cv::Vec3b>(centerY, centerX) = cv::Vec3b(0, 0, 0);

    cv::imshow("Changed Pixel", img);
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
        std::cerr << " Error: Could not load image from " << argv[1] << "\n";
        return 1;
    }

    cv::imshow("Original Image", img);
    cv::waitKey(0);

    SequentialTransformations(img);
    return 0;
}
