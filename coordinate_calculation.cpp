#include "coordinate_calculation.h"

double cd_cc(double dest_x){
	const double pi_value = acos(-1.0);
	const double internal_reference[3][4]{100,0,0,0,0,0,0,0,0,0,0,0};     /*����ڲξ���*/
	const double Pixel_size_X = 0.00345;
	const int f = 16;
	/*const double Zc=1;*///�������ϵZcֵ��������������ͷ����
/*	double Xc;
	double f;
	double dx;*///�������ϵ�л��ص�Xֵ�����������û��������λ��С
	/*Xc = (Zc * target_x - internal_reference[0][2] * Zc) / internal_reference[0][0];*/
	double angle = atan(f/(Pixel_size_X*dest_x));
	return angle;
};
