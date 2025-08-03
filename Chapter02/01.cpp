#include <opencv2/opencv.hpp>
#include <iostream>

/*
This code shows how to draw rectangles on an image using mouse events.
It allows the user to draw rectangles by clicking and dragging the mouse.
The user can also change the color of the rectangle by pressing keys 1, 2, or 3.
It uses OpenCV's mouse callback functionality to handle mouse events and draw rectangles interactively.
*/


/* 
Struct to pass more data to the callback.
callback functions in OpenCV can only take one parameter (void* param) , so we use a struct to encapsulate multiple parameters.
*/
struct CallbackData {
    cv::Mat* image;
    int* color_key;
};

// Variabili globali per il disegno
cv::Rect box;
bool drawing_box = false;

// function to draw a rectangle on the image
void draw_box(cv::Mat& img, cv::Rect box, int color_key = 1) {
    
    /**
     * @brief Draw a rectangle on the image.
     * 
     * @param img The image to draw on.
     * @param box The rectangle to draw.
     * @param color_key The color key (1: red, 2: green, 3: blue).
     */
    
    cv::Scalar color;
    switch (color_key) {
        case 1: color = cv::Scalar(0, 0, 255); break;   // rosso
        case 2: color = cv::Scalar(0, 255, 0); break;   // verde
        case 3: color = cv::Scalar(255, 0, 0); break;   // blu
        default: color = cv::Scalar(0, 0, 255); break;
    }
    cv::rectangle(img, box.tl(), box.br(), color, 2);
}

// Mouse callback
void my_mouse_callback(int event, int x, int y, int flags, void* param) {

    /**
     * @brief Mouse callback function to handle drawing rectangles.
     * 
     * @param event The mouse event.
     * @param x The x-coordinate of the mouse.
     * @param y The y-coordinate of the mouse.
     * @param flags Any relevant flags.
     * @param param User-defined parameter (CallbackData).
     */

    CallbackData* data = static_cast<CallbackData*>(param); // Cast the void pointer to CallbackData. From void* to CallbackData*
    cv::Mat& image = *(data->image); // Dereference the pointer to get the image
    int color = *(data->color_key); // Dereference the pointer to get the color key

    switch (event) {
        case cv::EVENT_MOUSEMOVE:
            if (drawing_box) {
                box.width = x - box.x;
                box.height = y - box.y;
            }
            break;

        case cv::EVENT_LBUTTONDOWN:
            drawing_box = true;
            box = cv::Rect(x, y, 0, 0);
            break;

        case cv::EVENT_LBUTTONUP:
            drawing_box = false;

            if (box.width < 0) {
                box.x += box.width;
                box.width *= -1;
            }
            if (box.height < 0) {
                box.y += box.height;
                box.height *= -1;
            }

            draw_box(image, box, color);  // rettangolo finale nel colore scelto
            break;
    }
}

void help() {
    std::cout << "Call: ./box_drawer\n"
              << "Draw rectangles with the mouse.\n"
              << "Press 1 (red), 2 (green), or 3 (blue) to change color.\n"
              << "ESC to exit.\n";
}

int main() {

    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    help();

    // Immagine nera di base
    cv::Mat image(400, 600, CV_8UC3, cv::Scalar::all(0));
    cv::Mat temp;

    int color_key = 1;  // colore iniziale = rosso

    // Prepare the struct for callback data
    CallbackData data;
    data.image = &image;
    data.color_key = &color_key;

    // Window setup
    cv::namedWindow("Box Example");
    cv::setMouseCallback("Box Example", my_mouse_callback, &data);

    // Main loop
    while (true) {
        image.copyTo(temp);

        if (drawing_box)
            draw_box(temp, box, color_key);  // anteprima dinamica

        cv::imshow("Box Example", temp);

        int key = cv::waitKey(15);
        if (key == 27) break;  // ESC per uscire

        if (key >= '1' && key <= '3')
            color_key = key - '0';  // cambia colore
    }

    return 0;
}
