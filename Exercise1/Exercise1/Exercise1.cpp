#include "Exercise1.h"
#define PI 3.1415926535

Exercise1::Exercise1() = default;

Exercise1::~Exercise1() = default;

CImg<unsigned char>& Exercise1::colorChange(CImg<unsigned char>& src)
{
	//��X��Y���ϱ�����������
	cimg_forXY(src, x, y) {
		//�����ص�RGBΪ��255��255��255������ɫ����������RGB��Ϊ��255, 0��0������ɫ��
		if (src(x, y, 0) == 255 && src(x, y, 1) == 255 && src(x, y, 2) == 255)
		{
			src(x, y, 0) = 255;
			src(x, y, 1) = 0;
			src(x, y, 2) = 0;
		}

		//�����ص�RGBΪ��0��0��0������ɫ����������RGB��Ϊ��0, 255��0������ɫ��
		if (src(x, y, 0) == 0 && src(x, y, 1) == 0 && src(x, y, 2) == 0)
		{
			src(x, y, 0) = 0;
			src(x, y, 1) = 255;
			src(x, y, 2) = 0;
		}
	}
	return src;
}

CImg<unsigned char>& Exercise1::drawCircleSelf1(CImg<unsigned char>& src) {
	cimg_forXY(src, x, y) {
		//ͨ��ŷʽ�����еľ��빫ʽ�жϸ������Ƿ���Բ��������
		if ((x - 50) * (x - 50) + (y - 50) * (y - 50) <= 900) {
			src(x, y, 0) = 0;
			src(x, y, 1) = 0;
			src(x, y, 2) = 255;
		}
	}
	return src;
}

CImg<unsigned char>& Exercise1::drawCircleSelf2(CImg<unsigned char>& src) {
	cimg_forXY(src, x, y) {
		if ((x - 50) * (x - 50) + (y - 50) * (y - 50) <= 9) {
			src(x, y, 0) = 255;
			src(x, y, 1) = 255;
			src(x, y, 2) = 0;
		}
	}
	return src;
}

CImg<unsigned char>& Exercise1::drawLineSelf(CImg<unsigned char>& src) {
	//��X���������ͼƬ
	cimg_forX(src, x) {
		//������Ӧ��X���꣬�������Ǻ�������Y����
		int y = (int)(x * tan(35 * PI / 180) + 0.5);
		//������ӦXY�������ص�RGBֵ
		src(x, y, 0) = 0;
		src(x, y, 1) = 0;
		src(x, y, 2) = 255;
	}
	return src;
}

CImg<unsigned char>& Exercise1::drawCircleInterface1(CImg<unsigned char>& src) {
	//������ɫ��RGB
	unsigned char blue[] = { 0, 0, 255 };
	//������Ӧ�ĺ�����ǰ��������ΪԲ�ε�xy���꣬����������ΪԲ�εİ뾶�����ĸ�����Ϊ�����ɫ
	src.draw_circle(50, 50, 30, blue);
	return src;
}

CImg<unsigned char>& Exercise1::drawCircleInterface2(CImg<unsigned char>& src) {
	unsigned char yellow[] = { 255, 255, 0 };
	src.draw_circle(50, 50, 3, yellow);
	return src;
}

CImg<unsigned char>& Exercise1::drawLineInterface(CImg<unsigned char>& src) {
	//������ɫ��RGB
	unsigned char blue[] = { 0, 0, 255 };
	//����draw_line������ǰ�ĸ������������յ��XY���꣬���һ��������ֱ�ߵ���ɫ
	src.draw_line(0, 0, src._width, src._height * sin(35 * PI / 180), blue);
	return src;
}

void Exercise1::saveImage(CImg<unsigned char>& src) {
	src.save("Resource/2.bmp");
}