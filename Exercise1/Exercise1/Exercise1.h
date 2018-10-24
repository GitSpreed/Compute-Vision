#ifndef EXCERCISE1_HPP
#define EXCERSICE1_HPP

#include "CImg-library/CImg.h"
using namespace cimg_library;

class Exercise1 {
public:
	Exercise1();
	~Exercise1();
	//步骤二中要求的颜色的变换
	CImg<unsigned char>& colorChange(CImg<unsigned char>& src);

	//用自己的方法画步骤三中的圆
	CImg<unsigned char>& drawCircleSelf1(CImg<unsigned char>& src);

	//用自己的方法画步骤四中的圆
	CImg<unsigned char>& drawCircleSelf2(CImg<unsigned char>& src);

	//用自己的方法画直线
	CImg<unsigned char>& drawLineSelf(CImg<unsigned char>& src);

	//调用函数画步骤三中的圆
	CImg<unsigned char>& drawCircleInterface1(CImg<unsigned char>& src);

	//调用函数画步骤四种的圆
	CImg<unsigned char>& drawCircleInterface2(CImg<unsigned char>& src);

	//调用函数画直线
	CImg<unsigned char>& drawLineInterface(CImg<unsigned char>& src);

	//存储图像
	void saveImage(CImg<unsigned char>& src);
};

#endif
