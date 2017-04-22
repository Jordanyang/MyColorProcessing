#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include<thread>
#include<vector>
#include"../lib/mycuda.h"
#include"../lib/ImageProcess.h"
#include"../lib/MyTime.h"
#include"../lib/Uselities.h"
//using namespace std;
void static test5(cv::Mat&img,double alpha);//测试CPU自己和GPU自己负载均衡
void static prepare(std::vector<cv::Mat>& img_lst);// CPU和GPU预热程序
void static CPU_GPU(cv::Mat src,double speedup);
double time1;//自己写的CPU端程序运行耗时
double time2;//CPU+GPU运行耗时(CPU自写 GPU自写)
std::vector<double> Gpu_speedup;
std::vector<double> MixedSpeedup;
int main()
{
	 
	const std:: string filename = "./data/data.txt";
	const std::string filename1 = "gpu_data.txt";
	const std::string filename2 = "mix_data.txt";
	std::vector<cv::Mat> img_lst;
	load_images(filename,img_lst);
	prepare(img_lst);
	for (int i = 0; i < img_lst.size(); i++)
	{
		test5(img_lst[i],1);
		std::cout << "This is the "<< (i + 1) << " times run the programm" << std::endl;
	}
	save_to_text(filename1, Gpu_speedup);
	save_to_text(filename2, MixedSpeedup);
	return 0;
}
// CPU和GPU预热
void static prepare(std::vector<cv::Mat>& img_lst)
{
	using namespace cv;
	typedef Mat mat;
	mat img = img_lst[0];
	mat img2 = img{ Rect{0,0,1,1} };
	cv::medianBlur(img2, img2, 3);
	Gpu_Median_Filter(img2);
}
void static CPU_GPU(cv::Mat src, double speedup,double alpha)
{
	using namespace cv;
	using namespace std;
	typedef Mat mat;
	int rownum = src.rows*( 1/ (1 + speedup))*alpha;
	if (rownum <= 1)
	{
		MyTimer t3;
		t3.start();
		for (int i = 0; i < 10;i++)
			Gpu_Median_Filter(src);
		t3.stop();
		time2 = t3.elapse()/10;
	}
	else{
		mat cpu_img;
		cpu_img = src{ Rect{ 0, 0, src.cols, rownum } };
		mat gpu_img;
		gpu_img = src{ Rect{ 0, rownum, src.cols, src.rows - rownum } };
		thread t_cpu, t_gpu;
		/*MyTimer t3;
		t3.start();
		for (int i = 0; i < 10; i++)
		{
			thread(Gpu_Median_Filter, ref(gpu_img)).join();
			thread(myMedianBlur, ref(cpu_img), ref(cpu_img), 3).join();
		}*/
		t_gpu = thread(Gpu_Median_Filter, ref(gpu_img));
		t_cpu = thread(cv::medianBlur, ref(cpu_img), ref(cpu_img), 3);
		MyTimer t3;
		t3.start();
		t_cpu.join();
		t_gpu.join();
		
		/*cpu_img.push_back(gpu_img);*/
		t3.stop();
		time2 = t3.elapse();
	}
	cout << "CPU+GPU epeedup=" << time1 / time2 << endl;	
	MixedSpeedup.push_back(time1/time2);
}
void static test5(cv::Mat&src,double alpha)
{
	using namespace cv;
	using namespace std;
	typedef Mat mat;
	mat img = src;
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
	//thread thread1;
	for (int i = 0; i < 1; i++)
		Gpu_Median_Filter(dst1);
	t1.stop();
	/*std::cout << "GPU Time  is: " << t1.elapse() << " ms" << std::endl << std::endl;*/
	MyTimer t2;
	t2.start();
	for (int i = 0; i < 1; i++)
		cv::medianBlur(dst2, dst3, 3);
	t2.stop();
	/*std::cout << "CPU Time  is: " << t2.elapse() << " ms" << std::endl << std::endl;*/
	double speedup = t2.elapse() / t1.elapse();
	cout <<"GPU speedup="<<speedup << endl;
	time1 = t2.elapse()/1;
	CPU_GPU(img, speedup,alpha);
	Gpu_speedup.push_back(speedup);
	/*waitKey(0);*/
}
