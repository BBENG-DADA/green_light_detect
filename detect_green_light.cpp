#include "detect_green_light.h"
#include "rm_noise_and_small_parts.h"
#include "coordinate_calculation.h"
void detect_green_light(Mat& frame) {
	Mat hsv, mask;
	cvtColor(frame, hsv, COLOR_BGR2HSV);

	//确定要识别的绿色的HSV范围（色调，饱和度，亮度）
	Scalar lower_green = Scalar(35, 100, 10);
	Scalar upper_green = Scalar(75, 200, 80);

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
		if (aspect_ratio > 0.8 && aspect_ratio < 1.2) {
			//显示中心点值，与瞄准中心的差值
			Point center(bounding_rect.x + bounding_rect.width/2,bounding_rect.y + bounding_rect.height/2);
			rectangle(frame, bounding_rect, Scalar(0, 255, 0),2);
			/*string centerlocation = "Target--X:"+ to_string((bounding_rect.x + bounding_rect.width)/2)+"Y:"+ to_string((bounding_rect.y + bounding_rect.height) / 2)+
				                    "Destnation--X:" + to_string((mask.size().width / 2)-((bounding_rect.x + bounding_rect.width)/2)) + "Y:" + to_string((mask.size().height / 2)-((bounding_rect.y + bounding_rect.height)/2));*/
			// 计算Target中心点坐标
			double target_x = bounding_rect.x + bounding_rect.width/2 ;
			double target_y = bounding_rect.y + bounding_rect.height/2 ;
			// 计算图像中心点坐标
			double image_center_x = mask.size().width / 2;
			double image_center_y = mask.size().height / 2;
			// 计算Destination
			double dest_x = image_center_x - target_x;
			double dest_y = image_center_y - target_y;
            double unsigned_Deviation_angle = cd_cc(dest_x);
			//显示模块，可以用vector来存点和字符串，但是还要写配套结构体懒得写了 ：<
			string centerlocationTx = "Target--X:" + to_string(target_x);
			string centerlocationTy = "Y:" + to_string(target_y);
			string centerlocationDx = "Destination--X:" + to_string(dest_x);
			string centerlocationDy = "Y:" + to_string(dest_y);
            string centerlocationAg = "Angle:"+to_string(cd_cc(dest_x));
			Point org1(50, 50);
			Point org2(50, 100);
			Point org3(50, 150);
			Point org4(50, 200);
			Point org5(50, 250);
			putText(frame, centerlocationTx,org1, FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 2);
			putText(frame, centerlocationTy,org2, FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 2);
			putText(frame, centerlocationDx,org3, FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 2);
			putText(frame, centerlocationDy,org4, FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 2);
			putText(frame, centerlocationAg,org5, FONT_HERSHEY_SIMPLEX, 0.75, (0, 0, 255), 2);
			//cout << "center is " << center << endl;
            //cout << "Angle is " << Deviation_angle << endl;
		}
	}
}

