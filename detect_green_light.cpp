#include"detect_green_light.h"
#include "rm_noise&small_parts.h"

void detect_green_light(Mat& frame) {
	Mat hsv, mask;
	cvtColor(frame, hsv, COLOR_BGR2HSV);

	//ȷ��Ҫʶ�����ɫ��HSV��Χ��ɫ�������Ͷȣ����ȣ�
	Scalar lower_green = Scalar(35, 100, 100);
	Scalar upper_green = Scalar(85, 255, 255);

	//ѡ������Ҫ������ز���ͼ���ֵ��
	inRange(hsv, lower_green, upper_green, mask);
	//���봦��,����������뿪������˴�С
	int min = 500,kernelsize=5;
	rm_ns(mask,min,kernelsize);
	//�洢�����㼯������������
	vector<vector<Point>> contours;
	findContours(mask, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
	for (size_t i = 0; i < contours.size(); i++) {
		////������ʮ����
		//line(frame, Point(0, mask.size().height / 2), Point(mask.size().width, mask.size().height / 2), Scalar(0, 0, 255));
		//line(frame, Point(mask.size().width/2, 0), Point(mask.size().width, mask.size().height ), Scalar(0, 0, 255));
		//���ݴ洢�ı�Ե��Ϣ������С���ο�
		Rect bounding_rect = boundingRect(contours[i]);
		//ͨ�������ж�ʶ����Ƿ���Բ�ε��̵�
		double aspect_ratio = (double)bounding_rect.width/(double)bounding_rect.height;
		if (aspect_ratio > 0.5 && aspect_ratio < 1.5) {
			//��ʾ���ĵ�ֵ������׼���ĵĲ�ֵ
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

