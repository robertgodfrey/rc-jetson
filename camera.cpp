#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    std::cout << "START" << std::endl;
    
    Mat image;
    namedWindow("Display window");
    VideoCapture cap(0);

    if (!cap.isOpened()) {
        std::cout << "Can't open camera :(" << std::endl;
        exit(1);
    }

    while (true) {
        cap >> image;
        imshow("Display window", image);
        waitKey(25);
    }

    return 0;
}
