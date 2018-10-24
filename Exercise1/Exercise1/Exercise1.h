#ifndef EXCERCISE1_HPP
#define EXCERSICE1_HPP

#include "CImg-library/CImg.h"
using namespace cimg_library;

class Exercise1 {
public:
	Exercise1();
	~Exercise1();
	//�������Ҫ�����ɫ�ı任
	CImg<unsigned char>& colorChange(CImg<unsigned char>& src);

	//���Լ��ķ������������е�Բ
	CImg<unsigned char>& drawCircleSelf1(CImg<unsigned char>& src);

	//���Լ��ķ������������е�Բ
	CImg<unsigned char>& drawCircleSelf2(CImg<unsigned char>& src);

	//���Լ��ķ�����ֱ��
	CImg<unsigned char>& drawLineSelf(CImg<unsigned char>& src);

	//���ú������������е�Բ
	CImg<unsigned char>& drawCircleInterface1(CImg<unsigned char>& src);

	//���ú������������ֵ�Բ
	CImg<unsigned char>& drawCircleInterface2(CImg<unsigned char>& src);

	//���ú�����ֱ��
	CImg<unsigned char>& drawLineInterface(CImg<unsigned char>& src);

	//�洢ͼ��
	void saveImage(CImg<unsigned char>& src);
};

#endif
