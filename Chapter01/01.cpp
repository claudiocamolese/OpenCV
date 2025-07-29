#include <iostream>
#include <opencv2/opencv.hpp>


int main(int argc, const char** argv) {
    
    cv::Mat img = cv::imread("./images/image.png", cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Could not open or find the image!" << std::endl;
        return -1;
    }
    return 0;
}