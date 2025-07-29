#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

/*This code demonstrates how to read a video file and display it frame by frame.
It also includes a trackbar to control the position of the video playback.
*/

/**
 * @brief Callback function for trackbar slider
 * 
 * @param pos New position of the slider
 * @param userdata User data (not used)
 * @return void
 */

// Define variables for sliders
int g_slider_position = 0;
int g_run = 1;
int g_dontset = 0;

cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void*){
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
    if(!g_dontset){
        g_run =1;
    }
    g_dontset= 0;
    };

int main(int argc, char** argv)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    
    cv::namedWindow("Example2_4", cv::WINDOW_AUTOSIZE);
    g_cap.open(std::string(argv[1])); // a string must be passed

    // define variables. Use of (int) to cast the double valure returned by .get() 
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    std::pair<int, int> size = std::make_pair(tmpw, tmph);

    // print values video
    std::cout << "Video has: " << frames<< "frames, and sizes: (" << size.first<< "," << size.second<<")"<< std::endl;

    cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames, onTrackbarSlide);
    cv::Mat frame;

    //eternal loop
    for(;;) {
        if( g_run != 0) {
            g_cap >> frame; if(frame.empty()) break;
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            cv::setTrackbarPos("Position", "Example2_4", current_pos);
            cv::imshow( "Example2_4", frame );
            g_run-=1;
    }

    char c = (char) cv::waitKey(10);
    
    if( c == 's' ){ // single step
        g_run = 1; 
        std::cout << "Single step, run = " << g_run << std::endl;
    }

    if( c == 'r' ){ // run mode
    g_run = -1; std::cout << "Run mode, run = " << g_run <<std::endl;
    }
    
    if( c == 27 )
    break;
    }

    return(0);
}