#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

/*
This code demonstrates how to apply different types of blurring filters to an image.
It allows the user to specify the type of blur filter to apply via command line arguments.
The user can run the program with the image path and the desired filter type as arguments.
Usage: ./blur_image <image_path> <filter_type>
Where <filter_type> can be:
1. Gaussian Blur
2. Average Blur
3. Median Blur
*/


void SmoothBlur(const cv::Mat& img, int value){
    /**
     * @brief Apply to the img the selected blur filter 
     * 
     * @param img is the original img
     * @param value is the int number corresponding to the blur filter  
     */
    std::string windowName = "Blurred img - Filter " + std::to_string(value);
    cv::namedWindow(windowName, cv::WINDOW_AUTOSIZE);
    cv::Mat out;

    switch (value)
    {
    case 1:
        cv::GaussianBlur(img, out, cv::Size(5,5), 3,3);
        break;
    
    case 2:
        cv::blur(img, out, cv::Size(3,3), cv::Point(-1,-1));
        break;
    
    case 3:
        cv::medianBlur(img, out, 3);
        break;
    default:
        std::cerr << "Filter not recognized " << value << ". Used GaussianBlur as defualt." << std::endl;
        cv::GaussianBlur(img, out, cv::Size(5,5), 3,3);
        break;
    }

    cv::imshow(windowName, out);
}

int main(int argc, char** argv)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <image_path> <filter1> [filter2] [filter3] ..." << std::endl;
        return -1;
    }

    cv::Mat img = cv::imread(argv[1], -1);
    
    if (img.empty()) {
        std::cerr << "Image not found" << std::endl;
        return -1;
    }

    cv::namedWindow("Original image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Original image", img);

    for (int i = 2; i < argc; ++i) {
        int filterType = std::stoi(argv[i]);
        SmoothBlur(img, filterType);
    }

    cv::waitKey(0);
    return 0;
}
