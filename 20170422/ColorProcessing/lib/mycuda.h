/*
��ͷ�ļ�����Ҫ��������CPP�ļ��е���cu�ļ��б�д�ĺ���
*/
#ifndef __MYCUDA_H_
#define __MYCUDA_H_
#include <opencv2\opencv.hpp>
extern "C"
void Gpu_Median_Filter(cv::Mat& img);
/*extern "C"
void test2()*/;
#endif
