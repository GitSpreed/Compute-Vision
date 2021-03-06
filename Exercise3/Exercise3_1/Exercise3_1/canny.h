//
//  canny.h
//  Canny Edge Detector
//
//  Created by spreed on 2018/10/24.
//  Copyright (c) 2018 spreed. All rights reserved.
//

#ifndef _CANNY_
#define _CANNY_
#include <vector>
#include <string>
#include "CImg-library/CImg.h"

using namespace std;
using namespace cimg_library;

class canny {
private:
    CImg<unsigned char> img; //Original Image
    CImg<unsigned char> grayscaled; // Grayscale
    CImg<unsigned char> gFiltered; // Gradient
    CImg<unsigned char> sFiltered; //Sobel Filtered
    CImg<float> angles; //Angle Map
    CImg<unsigned char> non; // Non-maxima supp.
    CImg<unsigned char> thres; //Double threshold and final
	CImg<unsigned char> follow; //link the edge

	void link(CImg<unsigned char>, int , int , float);

public: 

    canny(string); //Constructor
	CImg<unsigned char> toGrayScale();
	vector<vector<double>> createFilter(int, int, double); //Creates a gaussian filter
	CImg<unsigned char> useFilter(CImg<unsigned char>, vector<vector<double>>); //Use some filter
    CImg<unsigned char> sobel(); //Sobel filtering
    CImg<unsigned char> nonMaxSupp(); //Non-maxima supp.
    CImg<unsigned char> threshold(CImg<unsigned char>, int, int); //Double threshold and finalize picture
	CImg<unsigned char> edgeLink(CImg<unsigned char>, float);
};

#endif