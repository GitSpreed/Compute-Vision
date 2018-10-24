//
//  canny.cpp
//  Canny Edge Detector
//
//  Created by spreed on 2018/10/24.
//  Copyright (c) 2018 spreed. All rights reserved.
//

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <queue>
#include "canny.h"

canny::canny(string filename)
{
	img.load_bmp(filename.c_str());
	
	if (!img._data) // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;

	}
	else
	{

	vector<vector<double>> filter = createFilter(3, 3, 1);

    //Print filter
    for (int i = 0; i<filter.size(); i++) 
    {
        for (int j = 0; j<filter[i].size(); j++) 
        {
            cout << filter[i][j] << " ";
        }
    }

	grayscaled.assign(toGrayScale()); //Grayscale the image
    gFiltered.assign(useFilter(grayscaled, filter)); //Gaussian Filter
    sFiltered.assign(sobel()); //Sobel Filter
	

    non = CImg<unsigned char>(nonMaxSupp()); //Non-Maxima Suppression
    thres = CImg<unsigned char>(threshold(non, 20, 40)); //Double Threshold and Finalize
	follow.assign(edgeLink(sFiltered, 100));

    CImgDisplay original_disp(img, "Original");                  
	CImgDisplay gray_disp(grayscaled, "GrayScaled");
	CImgDisplay gf_disp(gFiltered, "Gaussian Blur");
	CImgDisplay sf_disp(sFiltered, "Sobel Filtered");
	CImgDisplay non_disp(non, "Non-Maxima Supp.");
	CImgDisplay thres_disp(thres, "threshold");
	CImgDisplay final_disp(follow, "final");

	while (!original_disp.is_closed()
		|| !gray_disp.is_closed()
		|| !gf_disp.is_closed()
		|| !sf_disp.is_closed()
		|| !non_disp.is_closed()
		|| !thres_disp.is_closed()
		|| !final_disp.is_closed()) {}
	}
}


CImg<unsigned char> canny::toGrayScale()
{
	grayscaled.assign(CImg<unsigned char>(img._width, img._height, 1)); //To one channel
	cimg_forXY(img, x, y) {
		int r = img(x, y, 0);
		int g = img(x, y, 1);
		int b = img(x, y, 2);

		double newValue = (r * 0.2126 + g * 0.7152 + b * 0.0722);
		grayscaled(x, y) = newValue;
	}	
	return grayscaled;
}

vector<vector<double>> canny::createFilter(int row, int column, double sigmaIn)
{
	vector<vector<double>> filter;

	for (int i = 0; i < row; i++)
	{
        vector<double> col;
        for (int j = 0; j < column; j++)
        {
            col.push_back(-1);
        }
		filter.push_back(col);
	}

	float coordSum = 0;
	float constant = 2.0 * sigmaIn * sigmaIn;

	// Sum is for normalization
	float sum = 0.0;

	for (int x = - row/2; x <= row/2; x++)
	{
		for (int y = -column/2; y <= column/2; y++)
		{
			coordSum = (x*x + y*y);
			filter[x + row/2][y + column/2] = (exp(-(coordSum) / constant)) / (M_PI * constant);
			sum += filter[x + row/2][y + column/2];
		}
	}

	// Normalize the Filter
	for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            filter[i][j] /= sum;

	return filter;

}

CImg<unsigned char> canny::useFilter(CImg<unsigned char> img_in, vector<vector<double>> filterIn)
{
    int size = (int)filterIn.size()/2;
	CImg<unsigned char> filteredImg = CImg<unsigned char>(img_in._width - 2*size, img_in._height - 2*size, 1);
	
	for (int x = size; x < img_in._width - size; x++)
	{
		for (int y = size; y < img_in._height - size; y++)
		{
			double sum = 0;

			for (int i = 0; i < filterIn.size(); i++) {
				for (int j = 0; j < filterIn.size(); j++) {
					sum += filterIn[i][j] * (double)(img_in(x + i - size, y + j - size));
				}
			}
			filteredImg(x - size, y - size) = sum;
		}
	}
	return filteredImg;
}

CImg<unsigned char> canny::sobel()
{

    //Sobel X Filter
    double x1[] = {-1.0, 0, 1.0};
    double x2[] = {-2.0, 0, 2.0};
    double x3[] = {-1.0, 0, 1.0};

    vector<vector<double>> xFilter(3);
    xFilter[0].assign(x1, x1+3);
    xFilter[1].assign(x2, x2+3);
    xFilter[2].assign(x3, x3+3);
    
    //Sobel Y Filter
    double y1[] = {1.0, 2.0, 1.0};
    double y2[] = {0, 0, 0};
    double y3[] = {-1.0, -2.0, -1.0};
    
    vector<vector<double>> yFilter(3);
    yFilter[0].assign(y1, y1+3);
    yFilter[1].assign(y2, y2+3);
    yFilter[2].assign(y3, y3+3);
    
    //Limit Size
    int size = (int)xFilter.size()/2;
    
	CImg<unsigned char> filteredImg = CImg<unsigned char>(gFiltered._width - 2*size, gFiltered._height - 2*size, 1);
    
    angles.assign(CImg<unsigned char>(gFiltered._width - 2*size, gFiltered._height - 2*size, 1)); //AngleMap

	for (int i = size; i < gFiltered._width - size; i++)
	{
		for (int j = size; j < gFiltered._height - size; j++)
		{
			double sumx = 0;
			double sumy = 0;

			for (int x = 0; x < xFilter.size(); x++)
				for (int y = 0; y < xFilter.size(); y++)
				{
					sumx += xFilter[x][y] * (double)(gFiltered(i + x - size, j + y - size)); //Sobel_X Filter Value
					sumy += yFilter[x][y] * (double)(gFiltered(i + x - size, j + y - size)); //Sobel_Y Filter Value
				}
			double sumxsq = sumx * sumx;
			double sumysq = sumy * sumy;

			double sq2 = sqrt(sumxsq + sumysq);

			if (sq2 > 255) //Unsigned Char Fix
				sq2 = 255;
			filteredImg(i - size, j - size) = sq2;

			if (sumx == 0) //Arctan Fix
				angles(i - size, j - size) = 90;
			else
				angles(i - size, j - size) = atan(sumy / sumx);
		}
	}
	
    
    return filteredImg;
}


CImg<unsigned char> canny::nonMaxSupp()
{
	CImg<unsigned char> nonMaxSupped = CImg<unsigned char>(sFiltered._width - 2, sFiltered._height - 2, 1);
	for (int i = 1; i < sFiltered._width - 1; i++) {
		for (int j = 1; j < sFiltered._height - 1; j++) {
			float Tangent = angles(i, j);

			nonMaxSupped(i - 1, j - 1) = sFiltered(i, j);
			//Horizontal Edge
			if (((-22.5 < Tangent) && (Tangent <= 22.5)) || ((157.5 < Tangent) && (Tangent <= -157.5)))
			{
				if ((sFiltered(i, j) < sFiltered(i, j + 1)) || (sFiltered(i, j) < sFiltered(i, j - 1)))
					nonMaxSupped(i - 1, j - 1) = 0;
			}
			//Vertical Edge
			if (((-112.5 < Tangent) && (Tangent <= -67.5)) || ((67.5 < Tangent) && (Tangent <= 112.5)))
			{
				if ((sFiltered(i, j) < sFiltered(i + 1, j)) || (sFiltered(i, j) < sFiltered(i - 1, j)))
					nonMaxSupped(i - 1, j - 1) = 0;
			}

			//-45 Degree Edge
			if (((-67.5 < Tangent) && (Tangent <= -22.5)) || ((112.5 < Tangent) && (Tangent <= 157.5)))
			{
				if ((sFiltered(i, j) < sFiltered(i - 1, j + 1)) || (sFiltered(i, j) < sFiltered(i + 1, j - 1)))
					nonMaxSupped(i - 1, j - 1) = 0;
			}

			//45 Degree Edge
			if (((-157.5 < Tangent) && (Tangent <= -112.5)) || ((22.5 < Tangent) && (Tangent <= 67.5)))
			{
				if ((sFiltered(i, j) < sFiltered(i + 1, j + 1)) || (sFiltered(i, j) < sFiltered(i - 1, j - 1)))
					nonMaxSupped(i - 1, j - 1) = 0;
			}
		}
	}
	return nonMaxSupped;
}

CImg<unsigned char> canny::threshold(CImg<unsigned char> imgin,int low, int high)
{
    if(low > 255)
        low = 255;
    if(high > 255)
        high = 255;
    
    CImg<unsigned char> EdgeMat = CImg<unsigned char>(imgin._width, imgin._height, imgin.spectrum());
    
    cimg_forXY(imgin, i, j) {
        EdgeMat(i,j) = imgin(i,j);
        if(EdgeMat(i,j) > high)
            EdgeMat(i,j) = 255;
        else if(EdgeMat(i,j) < low)
            EdgeMat(i,j) = 0;
        else
        {
            bool anyHigh = false;
            bool anyBetween = false;
            for (int x=i-1; x < i+2; x++) 
            {
                for (int y = j-1; y<j+2; y++) 
                {
                    if(x <= 0 || y <= 0 || EdgeMat._width || y > EdgeMat._height) //Out of bounds
                        continue;
                    else
                    {
                        if(EdgeMat(x,y) > high)
                        {
                            EdgeMat(i,j) = 255;
                            anyHigh = true;
                            break;
                        }
                        else if(EdgeMat(x,y) <= high && EdgeMat(x,y) >= low)
                            anyBetween = true;
                    }
                }
                if(anyHigh)
                    break;
            }
            if(!anyHigh && anyBetween)
                for (int x=i-2; x < i+3; x++) 
                {
                    for (int y = j-1; y<j+3; y++) 
                    {
                        if(x < 0 || y < 0 || x > EdgeMat._width || y > EdgeMat._height) //Out of bounds
                            continue;
                        else
                        {
                            if(EdgeMat(x,y) > high)
                            {
                                EdgeMat(i,j) = 255;
                                anyHigh = true;
                                break;
                            }
                        }
                    }
                    if(anyHigh)
                        break;
                }
            if(!anyHigh)
                EdgeMat(i,j) = 0;
        }
        
    }
    return EdgeMat;
}


CImg<unsigned char> canny::edgeLink(CImg<unsigned char> img, float threshold)
{
	CImg<unsigned char> linked(img);

	//link the edge
	/*cimg_forXY(linked, x, y) {
		link(linked, x, y, threshold);
	}*/

	struct node
	{
		int pre, x, y, depth;
		node(int p, int _x, int _y, int d):pre(p), x(_x), y(_y), depth(d) {}
	};

	vector<vector<int>> flag;
	for (int i = 0; i < linked._width + 2; i++) {
		vector<int> tmp;
		for (int j = 0; j < linked._height + 2; j++) {
			tmp.push_back(1);
		}
		flag.push_back(tmp);
	}

	cimg_forXY(linked, x, y) {
		queue<node> q;
		vector<node> vec;
		if (flag[x][y] != 0 && linked(x, y) > 0) {
			q.push(node(-1, x, y, 0));
			flag[x][y] = 0;
		}

		//detect the edge
		while (!q.empty()) {
			bool f = true;
			vec.push_back(q.front());
			int n = vec.size() - 1;

			q.pop();
			int x0 = (vec[n].x == 0) ? vec[n].x : vec[n].x - 1;
			int x2 = (vec[n].x == linked._width - 1) ? vec[n].x : vec[n].x + 1;
			int y0 = (vec[n].y == 0) ? vec[n].y : vec[n].y - 1;
			int y2 = (vec[n].y == linked._height - 1) ? vec[n].y : vec[n].y + 1;

			for (int i = x0; i <= x2; i++) {
				for (int j = y0; j <= y2; j++) {
					if (flag[i][j] && linked(i, j) > threshold) {
						q.push(node(n, i, j, vec[n].depth + 1));
						flag[i][j] = 0;
						f = false;
					}
				}
			}

			//delete the short edge
			if (f && vec[n].depth <= 20) {
				linked(vec[n].x, vec[n].y) = 0;
				while (vec[n].pre != -1)
				{
					n = vec[n].pre;
					linked(vec[n].x, vec[n].y) = 0;
				}
			}
		}
	}
	return linked;
}

void canny::link(CImg<unsigned char> img, int x, int y, float threshold)
{
	int x0 = (x == 0) ? x : x - 1;
	int x2 = (x == img._width - 1) ? x : x + 1;
	int y0 = (y == 0) ? y : y - 1;
	int y2 = (y == img._height - 1) ? y : y + 1;

	for (int i = x0; i <= x2; i++) {
		for (int j = y0; j <= y2; j++) {
			if ((i != x || j != y) && img(i, j) == 0 && gFiltered(i, j) >= threshold) {
				img(i, j) = gFiltered(x, y);
				link(img, i, j, threshold);
			}
		}
	}

}
