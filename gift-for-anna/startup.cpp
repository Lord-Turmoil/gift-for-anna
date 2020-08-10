#include "star.h"
#include "interface.h"
#include "letter.h"

Star star[MAXSTAR];
char keyboard;
MOUSEMSG mouse;

int main()
{
	Interface *gift = new MainInterface();
	
	srand((unsigned)time(NULL));
	
	if (!writeLetter())
		return 0;

	initgraph(800, 620);

	gift->print();
	delete gift;
	gift = NULL;

	closegraph();
	return 0;
}