#ifndef __USELITIES_H_
#define __USELITIES_H_
#include <opencv2\opencv.hpp>
#include<string>
#include<vector>
#include<iostream>
// filenameΪ�ļ��������ļ���ÿһ�д���ÿһ��ͼ�����ݵ�����·���� img_lst��Ŷ�ȡ������ͼ������
extern void load_images(const std::string & filename, std::vector<cv::Mat> & img_lst);
/*
filename Ҫд����ļ�������
p Ҫд�������
*/
extern void save_to_text(std::string filename, std::vector<double> &p);
#endif