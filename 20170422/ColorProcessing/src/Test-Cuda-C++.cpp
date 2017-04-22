#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include<thread>
#include<vector>
#include"../lib/mycuda.h"
#include"..\\lib\\ImageProcess.h"
#include"../lib/MyTime.h"
#include"../lib/Uselities.h"
using namespace std;
void static test5();//测试CPU自己和GPU自己负载均衡
void static prepare();// CPU和GPU预热程序
void static CPU_GPU(cv::Mat src,double speedup);
double time1;//自己写的CPU端程序运行耗时
double time2;//CPU+GPU运行耗时(CPU自写 GPU自写)
int main()
{
	const string filename = "data.txt";
	std::vector<cv::Mat> img_lst;
	load_images(filename,img_lst);
	prepare();
	for (int i = 0; i < 15; i++)
		test5();

	return 0;
}
// CPU和GPU预热
void static prepare()
{
	using namespace cv;
	typedef Mat mat;
	mat img = imread("1.bmp");
	mat img2 = img{ Rect{0,0,1,1} };
	cv::medianBlur(img2, img2, 3);
	Gpu_Median_Filter(img2);
}
void static CPU_GPU(cv::Mat src, double speedup)
{
	using namespace cv;
	typedef Mat mat;
	int rownum = src.rows*(speedup / (1 + speedup))*0.9;
	mat cpu_img;
	cpu_img = src{ Rect{ 0, 0, src.cols, rownum } };
	mat gpu_img;
	gpu_img = src{ Rect{ 0, rownum, src.cols, src.rows - rownum } };
	thread t_cpu, t_gpu;
	t_cpu = thread(Gpu_Median_Filter, ref(gpu_img));
	t_gpu = thread(medianBlur, ref(cpu_img), ref(cpu_img), 3);
	MyTimer t3;
	t3.start();
	t_cpu.join();
	t_gpu.join();
	cpu_img.push_back(gpu_img);
	t3.stop();
	/*std::cout << "CPU+GPU Time  is: " << t3.elapse() << " ms" << std::endl << std::endl;*/
	time2 = t3.elapse();
	/*imshow("123",cpu_img);*/
	/*time4 = time2;*/
	cout << "CPU+GPU epeedup=" << time1 / time2 << endl;
	
}
void static test5()
{
	using namespace cv;
	typedef Mat mat;
	mat img = imread("1.bmp");
	mat dst1 = img.clone();
	mat dst2 = img.clone();
	mat dst3;
	/*imshow("ԭͼ",img);*/
	salt(dst1, 3000);
	pepper(dst1, 3000);
	salt(dst2, 3000);
	pepper(dst2, 3000);
	/*imshow("ԭͼ1", dst);*/
	MyTimer t1;
	t1.start();
	Gpu_Median_Filter(dst1);
	t1.stop();
	/*std::cout << "GPU Time  is: " << t1.elapse() << " ms" << std::endl << std::endl;*/
	MyTimer t2;
	t2.start();
	medianBlur(dst2, dst3, 3);
	t2.stop();
	/*std::cout << "CPU Time  is: " << t2.elapse() << " ms" << std::endl << std::endl;*/
	double speedup = t2.elapse() / t1.elapse();
	cout <<"GPU speedup="<<speedup << endl;
	time1 = t2.elapse();
	CPU_GPU(img, speedup);
	/*waitKey(0);*/
}
