#include "coordinate calculation.h"

double cd_cc(double target_x,double target_y){
	const double internal_reference[3][4]{2124.9777,0,0,0,0,0,0,0,0,0,0,0};     /*����ڲξ���*/
	/*const double Zc=1;*///�������ϵZcֵ��������������ͷ����
	double Xc;
	double f;
	double dx;//�������ϵ�л��ص�Xֵ�����������û��������λ��С
	/*Xc = (Zc * target_x - internal_reference[0][2] * Zc) / internal_reference[0][0];*/
	double angle = acos(internal_reference[0][0] / target_x);
	return angle;
};