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
		//���ݴ洢�ı�Ե��Ϣ������С���ο�
		Rect bounding_rect = boundingRect(contours[i]);
		//ͨ�������ж�ʶ����Ƿ���Բ�ε��̵�
		double aspect_ratio = (double)bounding_rect.width / (double)bounding_rect.height;
		if (aspect_ratio > 0.5 && aspect_ratio < 1.5) {
			Point center((bounding_rect.x + bounding_rect.width) / 2, (bounding_rect.y + bounding_rect.height) / 2);
			rectangle(frame, bounding_rect, Scalar(0, 255, 0), 2);
			cout << "center is " << center << endl;
		}
	}
}

