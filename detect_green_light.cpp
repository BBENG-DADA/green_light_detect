#include"detect_green_light.h"
#include "rm_noise&small_parts.h"

void detect_green_light(Mat& frame) {
	Mat hsv, mask;
	cvtColor(frame, hsv, COLOR_BGR2HSV);

	//确定要识别的绿色的HSV范围（色调，饱和度，亮度）
	Scalar lower_green = Scalar(35, 100, 100);
	Scalar upper_green = Scalar(85, 255, 255);

	//选出符合要求的像素并将图像二值化
	inRange(hsv, lower_green, upper_green, mask);
	//降噪处理,最大忽略面积与开闭运算核大小
	int min = 500,kernelsize=5;
	rm_ns(mask,min,kernelsize);
	//存储轮廓点集和轮廓的容器
	vector<vector<Point>> contours;
	findContours(mask, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size(); i++) {
		////画中心十字线
		//line(frame, Point(0, mask.size().height / 2), Point(mask.size().width, mask.size().height / 2), Scalar(0, 0, 255));
		//line(frame, Point(mask.size().width/2, 0), Point(mask.size().width, mask.size().height ), Scalar(0, 0, 255));
		//根据存储的边缘信息画出最小矩形框
		Rect bounding_rect = boundingRect(contours[i]);
		//通过长宽判断识别的是否是圆形的绿灯
		double aspect_ratio = (double)bounding_rect.width/(double)bounding_rect.height;
		if (aspect_ratio > 0.5 && aspect_ratio < 1.5) {
			//显示中心点值，与瞄准中心的差值
			Point center((bounding_rect.x + bounding_rect.width)/2, (bounding_rect.y + bounding_rect.height)/2);
			rectangle(frame, bounding_rect, Scalar(0, 255, 0),2);
			string centerlocation = "Target--X:"+ to_string((bounding_rect.x + bounding_rect.width)/2)+"Y:"+ to_string((bounding_rect.y + bounding_rect.height) / 2)+
				                    "Destnation--X:" + to_string((mask.size().width / 2)-((bounding_rect.x + bounding_rect.width)/2)) + "Y:" + to_string((mask.size().height / 2)-((bounding_rect.y + bounding_rect.height)/2));
			Point org((bounding_rect.x + bounding_rect.width)/7, (bounding_rect.y + bounding_rect.height)/7);
			putText(frame,centerlocation,org,FONT_HERSHEY_SIMPLEX,0.75,(0,0,255),2);
			cout << "center is " << center << endl;
		}
	}
}

