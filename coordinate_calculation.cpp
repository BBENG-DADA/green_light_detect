#include "coordinate_calculation.h"

double cd_cc(double dest_x){
	const double pi_value = acos(-1.0);
	const double internal_reference[3][4]{100,0,0,0,0,0,0,0,0,0,0,0};     /*相机内参矩阵*/
	const double Pixel_size_X = 0.00345;
	const int f = 16;
	/*const double Zc=1;*///相机坐标系Zc值，即基地至摄像头距离
/*	double Xc;
	double f;
	double dx;*///相机坐标系中基地的X值，相机焦距以没像素物理单位大小
	/*Xc = (Zc * target_x - internal_reference[0][2] * Zc) / internal_reference[0][0];*/
	double angle = atan(f/(Pixel_size_X*dest_x));
	return angle;
};
