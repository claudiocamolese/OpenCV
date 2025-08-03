#include <opencv2/opencv.hpp>
#include <iostream>

/*
This code applies a Gaussian blur to an image using OpenCV.
It defines a function `blur` that takes an input image and applies a Gaussian blur with a specified kernel size.
The kernel size must be a positive odd integer. The main function reads an image from a file,
applies the blur function with different kernel sizes, and displays the results in separate windows.
*/

void blur(const cv::Mat& src, cv::Mat& out, int n) {
    /**
     * @brief Applies Gaussian blur to the input image.
     * @param src Input image.
     * @param out Output image.
     * @param n Kernel size (must be positive odd integer).
     */
    if (n < 1) n = 1;
    if (n % 2 == 0) n += 1;  // forza a valore dispari
    cv::GaussianBlur(src, out, cv::Size(n, n), 0);
}

int main(int argc, char** argv) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    // Fix path handling: usa argv[1]
    cv::Mat src = (argc < 2) ? cv::imread("..\\images\\texture.png") : cv::imread(argv[1]);

    if (src.empty()) {
        std::cerr << "Errore: immagine non caricata.\n";
        return -1;
    }

    for (int i = 1; i <= 5; i += 2) {
        cv::Mat out;
        blur(src, out, i);
        std::string winame = "Blurred with size " + std::to_string(i);
        cv::imshow(winame, out);
    }

    cv::waitKey(0);
    return 0;
}
