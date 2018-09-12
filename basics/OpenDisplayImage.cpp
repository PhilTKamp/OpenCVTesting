#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
  String imagePath = "./lena.jpg";
  if( argc > 1 ) {
    imagePath = argv[1];
  }

  Mat image;

  image = imread(imagePath, IMREAD_COLOR);

  if ( image.empty() ) {
    cout << "Unable to open or read image" << endl;
    return -1;
  }

  namedWindow("Display Window", WINDOW_AUTOSIZE);

  imshow("Display Window", image);

  waitKey(0);

  return 0;
}
