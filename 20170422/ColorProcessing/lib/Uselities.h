#ifndef __USELITIES_H_
#define __USELITIES_H_
#include <opencv2\opencv.hpp>
#include<string>
#include<vector>
#include<iostream>
// filename为文件名，该文件中每一行代表每一个图像数据的完整路径名 img_lst存放读取出来的图像数据
extern void load_images(const std::string & filename, std::vector<cv::Mat> & img_lst);
/*
filename 要写入的文件的名字
p 要写入的内容
*/
extern void save_to_text(std::string filename, std::vector<double> &p);
#endif