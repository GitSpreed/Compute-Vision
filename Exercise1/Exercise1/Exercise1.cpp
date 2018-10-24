#include "Exercise1.h"
#define PI 3.1415926535

Exercise1::Exercise1() = default;

Exercise1::~Exercise1() = default;

CImg<unsigned char>& Exercise1::colorChange(CImg<unsigned char>& src)
{
	//在X、Y轴上遍历所有像素
	cimg_forXY(src, x, y) {
		//若像素的RGB为（255，255，255）（黑色），则将它的RGB改为（255, 0，0）（红色）
		if (src(x, y, 0) == 255 && src(x, y, 1) == 255 && src(x, y, 2) == 255)
		{
			src(x, y, 0) = 255;
			src(x, y, 1) = 0;
			src(x, y, 2) = 0;
		}

		//若像素的RGB为（0，0，0）（白色），则将它的RGB改为（0, 255，0）（绿色）
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
		//通过欧式几何中的距离公式判断该像素是否在圆形区域内
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
	//从X轴遍历整幅图片
	cimg_forX(src, x) {
		//根据相应的X坐标，利用三角函数计算Y坐标
		int y = (int)(x * tan(35 * PI / 180) + 0.5);
		//更改相应XY坐标像素的RGB值
		src(x, y, 0) = 0;
		src(x, y, 1) = 0;
		src(x, y, 2) = 255;
	}
	return src;
}

CImg<unsigned char>& Exercise1::drawCircleInterface1(CImg<unsigned char>& src) {
	//定义蓝色的RGB
	unsigned char blue[] = { 0, 0, 255 };
	//调用相应的函数，前两个参数为圆形的xy坐标，第三个参数为圆形的半径，第四个参数为填充颜色
	src.draw_circle(50, 50, 30, blue);
	return src;
}

CImg<unsigned char>& Exercise1::drawCircleInterface2(CImg<unsigned char>& src) {
	unsigned char yellow[] = { 255, 255, 0 };
	src.draw_circle(50, 50, 3, yellow);
	return src;
}

CImg<unsigned char>& Exercise1::drawLineInterface(CImg<unsigned char>& src) {
	//定义蓝色的RGB
	unsigned char blue[] = { 0, 0, 255 };
	//调用draw_line函数，前四个参数是起点和终点的XY坐标，最后一个参数是直线的颜色
	src.draw_line(0, 0, src._width, src._height * sin(35 * PI / 180), blue);
	return src;
}

void Exercise1::saveImage(CImg<unsigned char>& src) {
	src.save("Resource/2.bmp");
}