#include"..\\lib\\Uselities.h"
#include<vector>
#include<iostream>
#include<string>
void static test()
{
	using namespace std;
	string filename = "./test/testdata/data123.txt";
	vector<double>p;
	p.push_back(1.1);
	p.push_back(2.2);
	save_to_text(filename,p);

}
void main()
{
	using namespace std;
	test();
	cin.get();
}