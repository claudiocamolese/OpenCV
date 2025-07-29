#include <opencv2/opencv.hpp>
#include <iostream>


/*
This code read from the principal camera of the device and shows the output.
Based on the keyboard input, different filters are applied on the frame image.
This are the effects (keyboard input, effect):
1. Normale
2. Grayscale
3. Canny
4. Blur
5. Heatmap
6. Inversione di colori
7. Scala di grigi + Sobel
8. Sogliatura binaria
9. Effetto seppia
10. Mappa termica
*/


int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Errore: impossibile aprire la webcam.\n";
        return -1;
    }

    int mode = 0;
    std::string windowName = "Webcam - Modalità Effetto";

    cv::Mat frame, out;

    std::cout << "Premi un numero per cambiare effetto:" << std::endl;
    std::cout << "0: Normale | 1: Grayscale | 2: Canny | 3: Blur | 4: Heatmap" << std::endl;

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Errore: frame vuoto.\n";
            break;
        }

                switch (mode) {
            case 0: // Normale
                out = frame.clone();
                break;
            case 1: // Grayscale
                cv::cvtColor(frame, out, cv::COLOR_BGR2GRAY);
                cv::cvtColor(out, out, cv::COLOR_GRAY2BGR);
                break;
            case 2: // Canny edge
                cv::Canny(frame, out, 100, 200);
                cv::cvtColor(out, out, cv::COLOR_GRAY2BGR);
                break;
            case 3: // Blur
                cv::GaussianBlur(frame, out, cv::Size(15, 15), 0);
                break;
            case 4: // Heatmap - COLORMAP_JET
                cv::applyColorMap(frame, out, cv::COLORMAP_JET);
                break;
            case 5: // Inversione di colori
                cv::bitwise_not(frame, out);
                break;
            case 6: // Scala di grigi + Sobel
            {
                cv::Mat gray, grad_x, grad_y;
                cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                cv::Sobel(gray, grad_x, CV_16S, 1, 0);
                cv::Sobel(gray, grad_y, CV_16S, 0, 1);
                cv::Mat abs_grad_x, abs_grad_y;
                cv::convertScaleAbs(grad_x, abs_grad_x);
                cv::convertScaleAbs(grad_y, abs_grad_y);
                cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, out);
                cv::cvtColor(out, out, cv::COLOR_GRAY2BGR);
                break;
            }
            case 7: // Sogliatura binaria
            {
                cv::Mat gray, binary;
                cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
                cv::threshold(gray, binary, 128, 255, cv::THRESH_BINARY);
                cv::cvtColor(binary, out, cv::COLOR_GRAY2BGR);
                break;
            }
            case 8: // Effetto seppia
            {
                cv::Mat kernel = (cv::Mat_<float>(3,3) <<
                    0.272, 0.534, 0.131,
                    0.349, 0.686, 0.168,
                    0.393, 0.769, 0.189);
                cv::transform(frame, out, kernel);
                break;
            }
            case 9: // Mappa termica - COLORMAP_INFERNO
                cv::applyColorMap(frame, out, cv::COLORMAP_INFERNO);
                break;
            default:
                out = frame.clone();
                break;
        }


        cv::imshow(windowName, out);

        char key = (char)cv::waitKey(1);
        if (key == 'q') break;
        if (key >= '0' && key <= '9') {
            mode = key - '0';
            std::cout << "Changed filter mode: " << mode << std::endl;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
