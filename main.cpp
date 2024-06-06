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
	int i = 1;
	cin >> i;
	if (i == 0);
	while(true){
	cap >> frame;
	if (frame.empty()) break;

	detect_green_light(frame);

	
	}
	cap.release();

	return 0;
}