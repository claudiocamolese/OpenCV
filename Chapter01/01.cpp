#include <iostream>
#include <opencv2/opencv.hpp>

/* 
This program demonstrates how to read and display an image using OpenCV.
*/


/**
 * @brief 
 * 
 * @param argc name of the .exe 
 * @param argv image path
 * @return int 
 */


int main(int argc, const char** argv) {
    
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }
    cv::namedWindow("MyFirstWindow", cv::WINDOW_AUTOSIZE);
    cv::imshow("MyFirstWindow", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}