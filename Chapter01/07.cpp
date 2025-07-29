#include <opencv2/opencv.hpp>
#include <iostream>

/*
This code takes the frame from the principal camera and perform a Log_Polar algorithm and saves the file
*/


int main( int argc, char** argv) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);

    cv::namedWindow( "Camera window", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "Log_Polar", cv::WINDOW_AUTOSIZE );
    
    cv::VideoCapture capture(0);
    
    double fps = capture.get( cv::CAP_PROP_FPS );

    cv::Size size( (int)capture.get( cv::CAP_PROP_FRAME_WIDTH ), 
                    (int)capture.get( cv::CAP_PROP_FRAME_HEIGHT ) );

    cv::VideoWriter writer;
    writer.open("..\\videos\\output.avi", cv::VideoWriter::fourcc('M','J','P','G'), fps, size);
    
    cv::Mat logpolar_frame, bgr_frame;
   
    for(;;) {

        capture.read(bgr_frame);

        if( bgr_frame.empty() ) break; // end if done
        
        cv::imshow( "Camera window", bgr_frame );
        
        cv::logPolar(bgr_frame, // Input color frame
                    logpolar_frame, // Output log-polar frame
                    cv::Point2f( // Centerpoint for log-polar transformation
                        bgr_frame.cols/2, // x
                        bgr_frame.rows/2  // y
                    ),
                    40, // Magnitude (scale parameter)
                    cv::WARP_FILL_OUTLIERS // Fill outliers with 'zero'
                    );
        
                    cv::imshow( "Log_Polar", logpolar_frame );
        
                    writer << logpolar_frame;
        
                    char c = cv::waitKey(10);
        
                    if( c == 27 ) break; // allow the user to break out
            }
    capture.release();
}
