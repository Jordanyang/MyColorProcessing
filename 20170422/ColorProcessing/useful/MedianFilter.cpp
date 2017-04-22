#include<iostream>
#include<stdlib.h>
#include<opencv2/opencv.hpp>
#include"..\\lib\\ImageProcess.h"
typedef struct
{
	unsigned char x;
	unsigned char y;
	unsigned char z;
}myuchar3;
using uchar3 = myuchar3;
using uchar = unsigned char;
uchar static sort_uchar1(uchar* filter, int num)
{
	////Sorting in filter
	for (int i = 0; i <num; i++) {
		for (int j = i + 1; j < num; j++) {
			if (filter[i] > filter[j]) {
				//Swap the variables.
				uchar tmp = filter[i];
				filter[i] = filter[j];
				filter[j] = tmp;
			}
		}
	}
	return filter[num / 2];
}
uchar3 static sort3(uchar3 *filter, int num)
{
	uchar3 temp;
	unsigned char *a = new unsigned char[num];
	unsigned char *b = new unsigned char[num];
	unsigned char *c = new unsigned char[num];
	for (int i = 0; i < num; i++)
	{
		a[i] = filter[i].x;
		b[i] = filter[i].y;
		c[i] = filter[i].z;
	}
	temp.x = sort_uchar1(a, num);
	temp.y = sort_uchar1(b, num);
	temp.z = sort_uchar1(c, num);
	delete[]a;
	delete[]b;
	delete[]c;
	return temp;

}

////////////////中值滤波////////////////////////////////
void static media_filter(unsigned char* src, int width, int height, unsigned char* dst, int windowSize)
{
	uchar3 mid = {0};
	int winsize = windowSize;//滤波窗口大小
	uchar3* windows = new uchar3[winsize*winsize*sizeof(uchar3)];
	uchar3 *inbuffer = (uchar3*)src;
	uchar3 *outbuffer = (uchar3*)dst;
	int pos = (winsize - 1) / 2;
	memcpy(outbuffer, inbuffer, width*height*sizeof(uchar3));
	for (int m = pos; m < height - pos; m++)
	{
		for (int n = pos; n < width - pos; n++)//（m，n）是窗口中心位置
		{
			//提取winsize*winsize的数据进入滤波窗
			int winpos = 0;
			for (int i = -pos; i < (winsize - pos); i++)
				for (int j = -pos; j < (winsize - pos); j++)
					windows[winpos++] = inbuffer[(m + i)*width + n + j];
			//对滤波窗中的数据排序取中值
			mid =sort3(windows, winsize*winsize);
			outbuffer[m*width + n] = mid;
		}
	}
	////对边界进行处理
	////未被处理的地方均取被处理的最边界
	//for (int k = 0; k < pos; k++)
	//	for (int l = pos; l < width - pos; l++)
	//		outbuffer[k*width + l] = outbuffer[pos * width + l];//1到pos这几行未被处理的边界数据，始终取被处理的最上边界一层像素

	//for (int a = height - pos; a < height; a++)
	//	for (int b = pos; b < width - pos; b++)
	//		outbuffer[a*width + b] = outbuffer[(height - pos - 1)*width + b];

	//for (int c = 0; c < pos; c++)
	//	for (int d = 0; d < height; d++)
	//		outbuffer[d*width + c] = outbuffer[d*width + pos];

	//for (int e = width - pos; e < width; e++)
	//	for (int f = 0; f < height; f++)
	//		outbuffer[f*width + e] = outbuffer[f*width + width - pos - 1];

	delete[] windows;
	windows = NULL;
	dst = (uchar*)outbuffer;
	return ;
}
void myMedianBlur(cv::Mat&src, cv::Mat& dst, int windowSize)
{

	dst.create(src.rows, src.cols, src.type());
	media_filter(src.data, src.cols, src.rows, dst.data, windowSize);
}