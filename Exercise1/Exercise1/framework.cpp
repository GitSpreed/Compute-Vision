#include "Exercise1.h"

int main() {
	Exercise1 ex;
	//����CImg���еĺ���������еĲ���
	/*CImg<unsigned char> SrcImg;
	SrcImg.load_bmp("Resource/1.bmp");
	SrcImg.display();
	ex.colorChange(SrcImg);
	ex.drawCircleInterface1(SrcImg);
	ex.drawCircleInterface2(SrcImg);
	ex.drawLineInterface(SrcImg);
	SrcImg.display();
	ex.saveImage(SrcImg);*/

	//�����Լ��ķ���������еĲ���
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