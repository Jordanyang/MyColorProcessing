#include<iostream>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include"..\\lib\\ImageProcess.h"
using namespace std;
void test()
{
	using namespace cv;
	Mat img = imread("1.bmp",2|4);
	imshow("origin", img);
	salt(img, 3000);
	pepper(img, 3000);
	imshow("salt", img);
	Mat dst;
	myMedianBlur(img,dst,5);
	imshow("dst",dst);
	waitKey(0);
}
void main()
{
	test();
	cin.get();
}