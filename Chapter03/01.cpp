#include <opencv2/opencv.hpp>
#include <iostream>


/*
This function takes an input image, splits it  into its RGB channels, computes a weighted average of the R and G channels,
and then adds the B channel to this average. Finally, it applies a threshold to the resulting image.
*/

void adaptive_thr(const cv::Mat& src, cv::Mat& gauss, cv::Mat& mean){

    // 	cv.adaptiveThreshold(src, maxValue, adaptiveMethod, thresholdType, blockSize, C[, dst]) ->	dst
    cv::adaptiveThreshold(src, gauss, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
    cv::adaptiveThreshold(src, mean, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 11, 2);
}



void sum_rgb(const cv::Mat& src, cv::Mat& dst) {

    /**
     * @brief Splits the input image into its RGB channels and computes a weighted sum.
     * @param src Input image in BGR format.
     * @param dst Output image after processing.
     * 
     */
    std::vector<cv::Mat> planes;

    // Split the source image into 3 separate channels: B, G, R
    cv::split(src, planes);

    // Assign each channel to a named variable
    cv::Mat b = planes[0], g = planes[1], r = planes[2], s;

    // Compute weighted average of R and G channels (each with 1/3 weight). The result is stored in 's'.
    // For each pixel, the formula is: s(i) = r(i) * alpha * g(i) * beta + gamma.
    // cv::addWeighted(src1, alpha, src2, beta, gamma, dst);
    // src1 first image, alpha weight for src1, src2 second image, beta weight for src2, gamma scalar added to the sum
    cv::addWeighted(r, 1.0 / 3.0, g, 1.0 / 3.0, 0.0, s);

    // Add the B channel with 1/3 weight to the result
    cv::addWeighted(s, 1.0, b, 1.0 / 3.0, 0.0, s);

    // Apply threshold: values above 100 are truncated to 100.
    // cv::threshold(src, dst, thresh, maxval, type);
    // src input array, dst output array, thresh threshold value, maxval maximum value to use with the THRESH_TRUNC type
    cv::threshold(s, dst, 100, 100, cv::THRESH_TRUNC);
}

int main(int argc, char** argv) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    cv::Mat src_color = cv::imread(std::string(argv[1]), cv::IMREAD_UNCHANGED), dst;
    if (src_color.empty()) {
        std::cout << "image not loaded" << std::endl;
        return -1;
    }

    // Converti in scala di grigi per thresholding
    cv::Mat src_gray;
    if (src_color.channels() == 3) {
        cv::cvtColor(src_color, src_gray, cv::COLOR_BGR2GRAY);
    } else if (src_color.channels() == 4) {
        cv::cvtColor(src_color, src_gray, cv::COLOR_BGRA2GRAY);
    } else {
        src_gray = src_color;  // già in scala di grigi
    }

    // Somma RGB sull'immagine originale
    sum_rgb(src_color, dst);
    cv::imshow("sum_rgb", dst);

    // Applica adaptive threshold sull'immagine in scala di grigi
    cv::Mat gauss, mean;
    adaptive_thr(src_gray, gauss, mean);
    cv::imshow("Gaussian method", gauss);
    cv::imshow("Mean method", mean);

    cv::waitKey(0);
    return 0;
}
