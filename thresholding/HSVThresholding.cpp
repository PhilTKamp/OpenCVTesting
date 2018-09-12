#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>

using namespace cv;
using namespace std;

void createWindows();

int H_MIN = 0;
int H_MAX = 255;
int S_MIN = 0;
int S_MAX = 255;
int V_MIN = 0;
int V_MAX = 255;



int main(int argc, char** argv) {
  int deviceIndex = 0;
  Mat frame;
  Mat HSVFrame;
  Mat threshFrame;
  char keyboard = 0;

  if(argc > 1) {
    deviceIndex = argv[1][0] - '0';
  }

  createWindows();

  VideoCapture video(deviceIndex);

  do {
    video >> frame;

    cvtColor(frame, HSVFrame, COLOR_BGR2HSV);

    inRange(HSVFrame,
        Scalar(H_MIN, S_MIN, V_MIN),
        Scalar(H_MAX, S_MAX, V_MAX),
        threshFrame);

    imshow("Original", frame);
    imshow("HSV", HSVFrame);
    imshow("Thresholded", threshFrame);

    keyboard = (char)waitKey(10);
  } while(keyboard != 27 && !frame.empty());

  video.release();

  destroyAllWindows();

  return 0;

}

void createWindows() {
  namedWindow("Original", WINDOW_NORMAL );
  namedWindow("HSV", WINDOW_NORMAL);
  namedWindow("Thresholded", WINDOW_NORMAL);
  namedWindow("Settings", WINDOW_AUTOSIZE);
  createTrackbar("H_MIN", "Settings", &H_MIN, 255);
  createTrackbar("H_MAX", "Settings", &H_MAX, 255);
  createTrackbar("S_MIN", "Settings", &S_MIN, 255);
  createTrackbar("S_MAX", "Settings", &S_MAX, 255);
  createTrackbar("V_MIN", "Settings", &V_MIN, 255);
  createTrackbar("V_MAX", "Settings", &V_MAX, 255);
}
