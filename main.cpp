#include "detect_green_light.h"


int main(int argc, char** argv) {
	string input = "input.avi";
	if (argc > 1) {
		input = argv[1];
	}

	VideoCapture cap;
	if (isdigit(input[0])) {
		cap.open(stoi(input));
	}
	else {
		cap.open(input);
	}

	if (!cap.isOpened()) {
		cerr << "Error" << endl;
		return -1;
	}
	Mat frame;
	namedWindow("Processed", WINDOW_NORMAL);
	while (true) {
		cap >> frame;
		if (frame.empty())
			break;
		////画中心十字线
		line(frame, Point(frame.size().width/2, 0), Point(frame.size().width/2, frame.size().height), Scalar(0, 0, 255));
		line(frame, Point(0, frame.size().height/2), Point(frame.size().width, frame.size().height/2), Scalar(0, 0, 255));
		detect_green_light(frame);
		imshow("Processed", frame);
		if (waitKey(30) == 27) { // 27 是Esc键的ASCII码
			break;
		}
	}
		cap.release();

		return 0;
	
}