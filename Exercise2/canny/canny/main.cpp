//
//  main.cpp
//  Canny Edge Detector
//
//  Created by Hasan Akgün on 21/03/14.
//  Copyright (c) 2014 Hasan Akgün. All rights reserved.
//

#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector> 
#include "canny.h"

using namespace std;

int main()
{
    string filePath = "test_Data/stpietro.bmp"; //Filepath of input image
    canny cny1(filePath);

    return 0;
}

