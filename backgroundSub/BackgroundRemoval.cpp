#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/video.hpp>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>

using namespace cv;
using namespace std;



int main(int argc, char** argv) {

  int deviceIndex = 0;
  char keyboard = 0;
  int dilation_size;
  Mat frame;
  Mat foregroundMask;
  Ptr<BackgroundSubtractor> pMOG;

  pMOG = createBackgroundSubtractorMOG2();

  if(argc > 1) {
    deviceIndex = argv[1][0] - '0';
  }

  namedWindow("Settings", WINDOW_AUTOSIZE);

  VideoCapture video(deviceIndex);

  if(!video.isOpened()) {
    cout << "Error reading from video stream" << endl;
    return -1;
  }

  do {
    video >> frame;

    pMOG->apply(frame, foregroundMask, 0.25);

    imshow("Original", frame);
    imshow("Foreground", foregroundMask);

    keyboard = (char)waitKey(30);

  } while(keyboard != 27 && !frame.empty());

  destroyAllWindows();

  video.release();

  return 0;
}
