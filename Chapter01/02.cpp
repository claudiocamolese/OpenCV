#include <opencv2/opencv.hpp>


/*
This code shows how to display a video given a path

*/

/**
 * @brief 
 * 
 * @param argc 
 * @param argv path of the video file  
 * @return int 
 */
int main(int argc, char const *argv[])
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    cv::namedWindow("Cam", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open(std::string(argv[1]));

    cv::Mat frame;
    for(;;){
        cap >> frame;
        if(frame.empty()) break;
        cv::imshow("Cam", frame);
        if(cv::waitKey(33)>=0) break;
    }
    
    return 0;
}

