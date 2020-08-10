#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <string>
#include <graphics.h>

struct Position
{
	int x;
	int y;
};
class Button
{
private:
	int length;
	int width;
	int thickness;
	Position pos;
	std::string text;
public:
	Button();
	~Button();

	void init(int _length, int width, int _thickness, int x, int y);
	void setText(std::string str);
	void show();	//dynamic effect
	bool print();	//if is clicked, return true
	void printText();
	void clear();
	void erase();
};

class Interface
{
private:
public:
	Interface();
	~Interface();

	virtual void show() = 0;
	virtual int print() = 0;
	virtual void clear() = 0;
	virtual void erase() = 0;

	void setRect(RECT &rect, int _left, int _top, int _right, int _bottom);
};

class MainInterface: public Interface
{
private:
public:
	MainInterface();
	~MainInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class GiftInterface: public Interface
{
private:
public:
	GiftInterface();
	~GiftInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

#endif