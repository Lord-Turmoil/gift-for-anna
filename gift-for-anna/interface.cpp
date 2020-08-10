#include <conio.h>
#include <cmath>
#include <windows.h>
#include "interface.h"
#include "star.h"

extern char keyboard;
extern MOUSEMSG mouse;
extern Star star[MAXSTAR];

/***********************************************************************************************
                                       Button
***********************************************************************************************/
Button::Button() {}
Button::~Button()
{
	clearrectangle(pos.x, pos.y, pos.x + length, pos.y + width);
}
void Button::init(int _length, int _width, int _thickness, int x, int y)
{
	length = _length;
	width = _width;
	thickness = _thickness;
	pos.x = x;
	pos.y = y;
}
void Button::setText(std::string str)
{
	text = str;
}
void Button::show()
{
	int i;
	RECT rect = {pos.x, pos.y, pos.x + length, pos.y + width};

	setlinecolor(MAGENTA);
	for (i = 0; i < thickness; i++)
	{	
		roundrect(pos.x + i, pos.y + i, pos.x + length - i, pos.y + width - i, 50, 50);
		Sleep(20);
	}
	drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
bool Button::print()
{
	int left = pos.x;
	int top = pos.y;
	int right = pos.x + length;
	int bottom = pos.y + width;
	int mx, my;
	int i;
	RECT rect = {pos.x, pos.y, pos.x + length, pos.y + width};

	mx = mouse.x;
	my = mouse.y;

	if ((left < mx) && (mx < right) && (my > top) && (my < bottom))	//mouse is on this button
	{
		setlinecolor(LIGHTMAGENTA);
		for (i = 0; i < thickness; i++)
			roundrect(pos.x + i, pos.y + i, pos.x + length - i, pos.y + width - i, 50, 50);
		//drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (mouse.uMsg == WM_LBUTTONUP)
		{
			mouse.uMsg = WM_MOUSEMOVE;

			return true;
		}
	}
	else
	{
		setlinecolor(MAGENTA);
		for (i = 0; i < thickness; i++)
			roundrect(pos.x + i, pos.y + i, pos.x + length - i, pos.y + width - i, 50, 50);
	}
	//drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	return false;
}
void Button::printText()
{
	RECT rect = {pos.x, pos.y, pos.x + length, pos.y + width};

	drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void Button::clear()
{
	clearrectangle(pos.x, pos.y, pos.x + length, pos.y + width);
}
void Button::erase()
{
	int i;

	setlinecolor(BLACK);
	for (i = 0; i < thickness; i++)
	{	
		roundrect(pos.x + i, pos.y + i, pos.x + length - i, pos.y + width - i, 10, 10);
		//Sleep(40);
	}
	clearrectangle(pos.x, pos.y, pos.x + length, pos.y + width);
}


/***********************************************************************************************
                                        Interface
***********************************************************************************************/
Interface::Interface() {}
Interface::~Interface() {}
void Interface::setRect(RECT &rect, int _left, int _top, int _right, int _bottom)
{
	rect.left = _left;
	rect.top = _top;
	rect.right = _right;
	rect.bottom = _bottom;
}

/***********************************************************************************************
                                     MainInterface
***********************************************************************************************/
MainInterface::MainInterface() {}
MainInterface::~MainInterface()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void MainInterface::show()
{
	Button* but = new Button();

	PlaySound(TEXT("RESOURCES\\SOUNDS\\MENU.WAV"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	clear();
	//START
	but->init(200, 120, 5, 300, 250);
	but->setText("OPEN");
	but->show();
}
int MainInterface::print()
{
	Button* but = new Button();
	Interface* target = NULL;
	unsigned long timestamp;
	int x, y;
	double a;
	int t;
	int maxt = 200;
	bool flag;

	settextstyle(60, 0, "Fixedsys");

	show();

	x = 300;
	y = 250;
	a = 0;
	t = 0;
	flag = true;

	BeginBatchDraw();	//avoid shaking

	//get user command
	while (true)
	{
		timestamp++;

		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == 27)
				break;
		}
		if (MouseHit())
		{
			mouse = GetMouseMsg();
		}
		but->init(200, 120, 5, x + t * cos(a), y + (maxt - t) * sin(a));
		but->setText("OPEN");
		
		if (timestamp % 10 == 0)
		{	
			a += 0.01;
			if (rand() % 1000 < 5)
				a += 3.99;
			if (flag)
				t++;
			else
				t--;
			if (t == maxt || t == 0)
				flag ^= 1;

			but->clear();
			but->init(200, 120, 5, x + t * cos(a), y + (maxt - t) * sin(a));
		}
		but->printText();
		if (but->print())
		{
			target = new GiftInterface();
			target->print();
			target->erase();
			delete target;
			target = NULL;

			PlaySound(TEXT("RESOURCES\\SOUNDS\\MENU.WAV"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
		}

		FlushBatchDraw();
	}

	EndBatchDraw();

	return 0;
}
void MainInterface::clear()
{
	cleardevice();
}
void MainInterface::erase()
{
	Button* but = new Button();

	but->init(200, 120, 5, 295, 225);
	but->erase();
}

/***********************************************************************************************
                                   GiftInterface
***********************************************************************************************/
GiftInterface::GiftInterface() {}
GiftInterface::~GiftInterface()
{
	cleardevice();
}
void GiftInterface::show()
{
	PlaySound(TEXT("RESOURCES\\SOUNDS\\STAR.WAV"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	cleardevice();
}
int GiftInterface::print()
{
	int i;
	RECT rect;

	show();

	for(i = 0; i < MAXSTAR; i++)
		star[i].init();
	
	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == 27)
				break;
		}
		if (MouseHit())
			mouse = GetMouseMsg();

		for (i = 0; i < MAXSTAR; i++)
			star[i].move();
		
		setRect(rect, 0, 250, 800, 300);
		drawtext(_T("HAPPY BIRTHDAY"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		setRect(rect, 0, 350, 800, 400);
		drawtext(_T("ANNA"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
		FlushBatchDraw();

		Sleep(20);
	}

	return 0;
}
void GiftInterface::clear()
{
	cleardevice();
}
void GiftInterface::erase()
{
	cleardevice();
}
