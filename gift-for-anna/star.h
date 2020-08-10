// ±‡“Îª∑æ≥£∫Visual C++ 6.0£¨EasyX 2018¥∫∑÷∞Ê
// http://www.easyx.cn
//
#include <graphics.h>
#include <time.h>
#include <conio.h>

#ifndef _STAR_H_
#define _STAR_H_

#include <graphics.h>

const int MAXSTAR = 1000;

class Star
{
private:
	double x;
	int	y;
	double step;
	int	color;
public:
	Star();
	~Star();

	void init();
	void move();
};

#endif