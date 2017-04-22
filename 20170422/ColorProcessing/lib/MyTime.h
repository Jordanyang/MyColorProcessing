/*
该头文件的主要功能是在Windows平台下进行准确的计时
用法如下：
在需要计时的代码前定义MyTimer对象t1,并设置开始计时，即t.start();
在代码结尾加上t.stop()。获得计时时间间隔为t.elapse()。单位为毫秒:ms
*/
#pragma once
#ifndef _MY_TIMER
#define  _MY_TIMER
#include<windows.h>
class MyTimer
{
private:
	LARGE_INTEGER _freq;
	LARGE_INTEGER _start;
	LARGE_INTEGER _stop;
public:

	MyTimer()
	{
		QueryPerformanceFrequency(&_freq);
	}

	inline void start()
	{
		QueryPerformanceCounter(&_start);
	}

	inline void stop()
	{
		QueryPerformanceCounter(&_stop);
	}

	inline double elapse()
	{
		return 1e3*(_stop.QuadPart - _start.QuadPart) / _freq.QuadPart;
	}

	inline long long ticks()
	{
		return _stop.QuadPart - _start.QuadPart;
	}
};
#endif