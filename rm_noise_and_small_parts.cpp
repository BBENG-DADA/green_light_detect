#include "rm_noise_and_small_parts.h"

void rm_ns(Mat& image, int min_size,int kernelsize) {
	//�������㽵��
    Mat element = getStructuringElement(MORPH_RECT, Size(kernelsize, kernelsize));
    morphologyEx(image, image, MORPH_OPEN, element);
    morphologyEx(image, image, MORPH_CLOSE, element);
    
    //���������С���н���
    Mat labels, stats, centroids;
	int num_of_parts = connectedComponentsWithStats(image, labels, stats, centroids);
    //��ȡÿһ������
    for (int i = 1; i < num_of_parts; ++i) {
        int size = stats.at<int>(i, CC_STAT_AREA);
        // �������̫С�ľ���ȥ
        if (size < min_size) {
            for (int y = 0; y < image.rows; ++y) {
                for (int x = 0; x < image.cols; ++x) {
                    if (labels.at<int>(y, x) == i) {
                        image.at<uchar>(y, x) = 0;
                    }
                }
            }
        }
    }
}
