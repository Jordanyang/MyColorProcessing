#ifndef _ImageProcess_H
#define _ImageProcess_H
#include <opencv2\opencv.hpp>
//������
extern void salt(cv::Mat& image, int n);
//������
extern void pepper(cv::Mat& image, int n);
extern void myMedianBlur(cv::Mat&src, cv::Mat& dst, int windowSize);
#endif