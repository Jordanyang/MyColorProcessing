/*
该头文件的主要作用是在CPP文件中调用cu文件中编写的函数
*/
#ifndef __MYCUDA_H_
#define __MYCUDA_H_
#include <opencv2\opencv.hpp>
extern "C"
void Gpu_Median_Filter(cv::Mat& img);
/*extern "C"
void test2()*/;
#endif
