/*
��ͷ�ļ�����Ҫ��������Windowsƽ̨�½���׼ȷ�ļ�ʱ
�÷����£�
����Ҫ��ʱ�Ĵ���ǰ����MyTimer����t1,�����ÿ�ʼ��ʱ����t.start();
�ڴ����β����t.stop()����ü�ʱʱ����Ϊt.elapse()����λΪ����:ms
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