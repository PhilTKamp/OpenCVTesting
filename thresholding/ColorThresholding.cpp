#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>

using namespace cv;
using namespace std;

Mat srcFrame;
Mat modFrame;
int redOffset=0;
int greenOffset=0;
int blueOffset=0;
int baseValue;
double base[3] = {0};
double top[3] = {0};

void createWindows();
void updateScalars(int, void*);

int main(int argc, char** argv) {
  int deviceIndex = 0;
  char keyboard = 0;

  if(argc > 1) {
    deviceIndex = (int)(argv[1][0] - '0');
  }

  createWindows();

  VideoCapture video(deviceIndex);

  while(keyboard != 27) {
    video >> srcFrame;

    inRange(srcFrame, Scalar(base[0], base[1], base[2]),
            Scalar(top[0], top[1], top[2]), modFrame);

    imshow("Original", srcFrame);
    imshow("Modified", modFrame);

    keyboard = waitKey(10);
  }
  video.release();

  destroyAllWindows();
  return 0;
}

void createWindows() {
  namedWindow("Original", WINDOW_AUTOSIZE);
  namedWindow("Modified", WINDOW_AUTOSIZE);
  namedWindow("Settings", WINDOW_AUTOSIZE);
  createTrackbar("Minimum Color Value", "Settings", &baseValue, 255, updateScalars);
  createTrackbar("R-Offset", "Settings", &redOffset, 255, updateScalars);
  createTrackbar("G-Offset", "Settings", &greenOffset, 255, updateScalars);
  createTrackbar("B-Offset", "Settings", &blueOffset, 255, updateScalars);
}

void updateScalars(int,void*) {
  base[0] = baseValue;
  base[1] = baseValue;
  base[2] = baseValue;

  top[0] = baseValue + blueOffset;
  top[1] = baseValue + greenOffset;
  top[2] = baseValue + redOffset;
}
