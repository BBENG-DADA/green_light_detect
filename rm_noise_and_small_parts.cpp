#include "rm_noise_and_small_parts.h"

void rm_ns(Mat& image, int min_size,int kernelsize) {
	//开闭运算降噪
    Mat element = getStructuringElement(MORPH_RECT, Size(kernelsize, kernelsize));
    morphologyEx(image, image, MORPH_OPEN, element);
    morphologyEx(image, image, MORPH_CLOSE, element);
    
    //根据面积大小进行降噪
    Mat labels, stats, centroids;
	int num_of_parts = connectedComponentsWithStats(image, labels, stats, centroids);
    //获取每一块的面积
    for (int i = 1; i < num_of_parts; ++i) {
        int size = stats.at<int>(i, CC_STAT_AREA);
        // 对于面积太小的就消去
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
