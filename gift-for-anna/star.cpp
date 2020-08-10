#include "star.h"

Star::Star() {}
Star::~Star() {}
void Star::init()
{
	x = 0.0;
	y = rand() % 620;
	step = (rand() % 5000) / 1000.0 + 1;
	color = (int)(step * 255 / 6.0 + 0.5); //the faster, the brighter
	color = RGB(color, color, color);
}

void Star::move()
{
	putpixel((int)x, y, 0);

	x += step;
	if (x > 800)
		init();

	putpixel((int)x, y, color);
}