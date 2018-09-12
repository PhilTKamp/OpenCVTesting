#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <iomanip>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    int deviceIndex = 0; //Uses default camera
    char c;

    if(argc > 1) {
      deviceIndex = (int)argv[1][0] - '0';
    }

    VideoCapture video;

    video.open(CV_CAP_OPENNI);

    if(!video.isOpened()) {
      cout << "Error opening or reading video stream" << endl;
      return -1;
    }

    Mat frame;

    do {
      video >> frame;

      imshow("Frame", frame);

      c = (char)waitKey(25);
    }while(!frame.empty() && c != 27);

    video.release();

    destroyAllWindows();

    return 0;
}
