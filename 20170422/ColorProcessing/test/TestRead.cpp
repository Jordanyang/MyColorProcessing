#include<opencv2/opencv.hpp>
#include<iostream>
#include<fstream>
#include<thread>
#include<vector>
#include"..//lib//Uselities.h"
using namespace std;
void static test()
{
	string filename = "data.txt";
	vector<cv::Mat> imagelist;
	load_images(filename, imagelist);
	imshow("last", imagelist[imagelist.size()-1]);
	cv::waitKey(0);
}
void main()
{
	test();
	cin.get();
}
void load_images(const string & filename, vector< cv::Mat > & img_lst)
{
	using namespace cv;
	string line;
	fstream file;
	file.open(filename);
	if (!file.is_open())
	{
		cerr << "Unable to open the list of images from " << filename << " filename." << endl;
		exit(-1);
	}

	bool end_of_parsing = false;
	while (!end_of_parsing)
	{
		getline(file, line);
		if (line.empty()) // no more file to read
		{
			end_of_parsing = true;
			break;
		}
		Mat img = imread(line); // load the image
		if (img.empty()) // invalid image, just skip it.
			continue;
		img_lst.push_back(img.clone());
		/*imshow("123",img);
		waitKey(0);*/
	}
}