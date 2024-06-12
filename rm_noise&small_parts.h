#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void rm_ns(Mat& image, int min_size, int kernelsize);