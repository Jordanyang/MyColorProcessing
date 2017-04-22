#include<iostream>
#include<fstream>
#include<vector>
/*
filename1 要写入的文件的名字
//times      要写入的文件的名字的标号
*/
void save_to_text(std::string filename1, std::vector<double> &p)
{
	using namespace std;
	fstream outfile;
	string tempfilenanme = filename1;
	outfile.open(tempfilenanme, ios::out | ios::trunc);
	for (auto i = 0; i < p.size(); i++)
		outfile << p[i] << endl;
	outfile.close();
}