#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

/*
This code demonstrates how to read a video file and display it frame by frame.
Extracts from a video: numer of frames and their sizes.
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

void onTrackbarSlide(int pos, void* _){
    // If the slider is moved, set the position of the video capture
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
    if(!g_dontset){
        g_run =1;
    }
    g_dontset= 0;
    };

int main(int argc, char** argv)
{
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    
    // Create a window to display the video
    cv::namedWindow("Example", cv::WINDOW_AUTOSIZE);
    g_cap.open(std::string(argv[1])); // a string of the video path must be passed

    // define variables. Use of (int) to cast the double valure returned by .get() 
    //CAP_PROP_FRAME_COUNT returns the number of frames in the video
    //CAP_PROP_FRAME_WIDTH and CAP_PROP_FRAME_HEIGHT return the width and height of the frames
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT);
    int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    // Create a pair to hold the width and height of the video frames
    std::pair<int, int> size = std::make_pair(tmpw, tmph);

    // print values video
    std::cout << "Video has: " << frames<< "frames, and sizes: (" << size.first<< "," << size.second<<")"<< std::endl;

    // Create a trackbar to control the position of the video playback
    // The trackbar will be linked to the "Example" window, with a range from 0 to the number of frames in the video
    // The callback function onTrackbarSlide will be called when the slider is moved
    cv::createTrackbar("Position", "Example", &g_slider_position, frames, onTrackbarSlide);
    cv::Mat frame;

    // eternal loop
    for(;;) {
        if( g_run != 0) {
            g_cap >> frame; if(frame.empty()) break;
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
            g_dontset = 1;
            cv::setTrackbarPos("Position", "Example", current_pos);
            cv::imshow( "Example", frame );
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