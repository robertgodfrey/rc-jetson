#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int, char**) {
    Mat frame;
    VideoCapture cap("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=3280, height=2464, format=(string)NV12, framerate=21/1 ! nvvidconv flip-method=0 ! video/x-raw, width=960, height=616, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink wait-on-eos=false max-buffers=1 drop=True");
    
    if (!cap.isOpened()) {
        cerr << "ERROR! Unable to open camera" << endl;
        return -1;
    }
    cout << "Starting camera" << endl
         << "Press any key to terminate" << endl;
    while (true) {
        cap.read(frame);
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed" << endl;
            break;
        }
        imshow("Live", frame);
        if (waitKey(5) >= 0)
            break;
    }
    cout << "Stopping" << endl;
    return 0;
}
