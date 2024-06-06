#include"detect_green_light.h"

void detect_green_light(Mat& frame) {
	Mat hsv, mask;
	cvtColor(frame, hsv, COLOR_BGR2HSV);

	//确定要识别的绿色的HSV范围（色调，饱和度，亮度）
	Scalar lower_green = Scalar(35, 100, 100);
	Scalar upper_green = Scalar(85, 255, 255);

	//选出符合要求的像素并将图像二值化
	inRange(hsv, lower_green, upper_green, mask);

	//存储轮廓点集和轮廓的容器
	vector<vector<Point>> contours;
	findContours(mask, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size(); i++) {
		Rect bounding_rect = boundingRect(contours[i]);

		double aspect_ratio = (double)bounding_rect.width / (double)bounding_rect.height;
		if (aspect_ratio > 0.5 && aspect_ratio < 1.5) {
			Point center((bounding_rect.x + bounding_rect.width) / 2, (bounding_rect.y + bounding_rect.height) / 2);
			rectangle(frame, bounding_rect, Scalar(0, 255, 0), 2);
			cout << "center is " << center << endl;
		}
	}
}

