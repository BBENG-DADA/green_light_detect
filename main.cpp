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

		detect_green_light(frame);
		imshow("Processed", frame);
		if (waitKey(30) == 27) { // 27 ÊÇEsc¼üµÄASCIIÂë
			break;
		}
	}
		cap.release();

		return 0;
	
}