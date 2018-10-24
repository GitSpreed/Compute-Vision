#include "Exercise1.h"

int main() {
	Exercise1 ex;
	//运用CImg库中的函数完成所有的步骤
	/*CImg<unsigned char> SrcImg;
	SrcImg.load_bmp("Resource/1.bmp");
	SrcImg.display();
	ex.colorChange(SrcImg);
	ex.drawCircleInterface1(SrcImg);
	ex.drawCircleInterface2(SrcImg);
	ex.drawLineInterface(SrcImg);
	SrcImg.display();
	ex.saveImage(SrcImg);*/

	//运用自己的方法完成所有的步骤
	CImg<unsigned char> SrcImg;
	SrcImg.load_bmp("Resource/1.bmp");
	SrcImg.display();
	ex.colorChange(SrcImg);
	ex.drawCircleSelf1(SrcImg);
	ex.drawCircleSelf2(SrcImg);
	ex.drawLineSelf(SrcImg);
	SrcImg.display();
	ex.saveImage(SrcImg);
	return 0;
}