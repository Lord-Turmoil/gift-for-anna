#include "letter.h"

void gotoPosition(int x, int y)
{
	HANDLE Output;
	COORD Position;
	
	Position.X = x;
	Position.Y = y;
	Output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(Output, Position);

	return ;
}
void hideCursor()
{
	HANDLE Output;
	CONSOLE_CURSOR_INFO Cursor;
	
	Output = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(Output, &Cursor);
	Cursor.bVisible = false;
	SetConsoleCursorInfo(Output, &Cursor);
}
void showCursor()
{
	HANDLE Output;
	CONSOLE_CURSOR_INFO Cursor;
	
	Output = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(Output, &Cursor);
	Cursor.bVisible = true;
	SetConsoleCursorInfo(Output, &Cursor);
}
int random(int left, int right)
{
	return left + rand() % (right - left + 1);
}
bool writeLetter()
{
	char ch;
	char keyboard;
	int read;
	int delay;
	bool skip;

	int col[MAX_LINE];
	int line;

	std::string sound;
	FILE *fpin;
	FILE *fpout;
	
	system("MODE CON LINES=40 COLS=100");
	hideCursor(); 

	read = false;
	fpin = fopen(LOG_FILE, "r");
	if (fpin == NULL)
	{
		printf("FATAL ERROR!\a");
		return false;
	}
	else
	{
		fscanf(fpin, "%*[^1234567890] %d", &read);
		fclose(fpin);
	}
	
	printf("This is a letter outside the gift box.\n");
	printf("It may take you 4 to 5 minutes to read it.\n");
	printf("Or to be exact, may take me more than 4 minutes to type it.\n");
	while (_kbhit())
		getch();
	printf("\n[Press any key to continue]");
	getch();
	system("CLS");

	fpin = fopen(INPUT_FILE, "r");
	memset(col, 0, sizeof(col));
	line = 0;
	skip = false;
	while (_kbhit())
		getch();
	while ((ch = fgetc(fpin)) != EOF)
	{
		putchar('_');
		putchar('\b');
		//printf("_%-2d\b\b\b", cnt);
		if (_kbhit())
		{
			keyboard = getch();
			if (keyboard == 27)
			{
				if (read > 0)
					skip = true;
			}
		}

		if (ch == '|')
		{
			delay = 50;
		}
		else if (ch == '#')
		{
			delay = random(20, 100);
			sound = SOUND_SPACE;
		}
		else if (ch == ' ')
		{
			delay = random(50, 100);
			sound = SOUND_SPACE;
		}
		else if (ch == ',')
		{

			delay = random(100, 200);
			sound = SOUND_PRINT;
		}
		else if (ch == '.')
		{
			delay = random(300, 400);
			sound = SOUND_PRINT;
		}
		else if (ch == '\n')
		{
			delay = random(400, 600);
			sound = SOUND_SPACE;
		}
		else	//normal letters
		{
			delay = random(20, 200);
			sound = SOUND_PRINT;
		}

		if (!skip)
		{
			Sleep(delay);
		}
		if (ch == '|')
			continue;
		else if (ch == '#')
		{
			if (!skip)
				PlaySound(TEXT(sound.c_str()), NULL, SND_FILENAME | SND_ASYNC);

			if (col[line] > 0)
			{
				putchar(' ');
				putchar('\b');
				putchar('\b');
				putchar(' ');
				putchar('\b');
				col[line]--;
			}
			else
			{
				if (line > 0)
				{
					putchar(' ');
					line--;
					gotoPosition(col[line], line);
				}
				else
				{
					putchar(' ');
					putchar('\b');
					putchar('\b');
					putchar(' ');
					putchar('\b');
				}
			}
		}
		else if (ch == ' ')
		{
			if (!skip)
				PlaySound(TEXT(sound.c_str()), NULL, SND_FILENAME | SND_ASYNC);
			if (col[line] > 80)
			{
				putchar(' ');
				putchar('\n');
				col[line]++;
				line++;
			}
			else
			{
				putchar(ch);
				col[line]++;
			}
		}
		else if (ch == '\n')
		{
			if (!skip)
				PlaySound(TEXT(sound.c_str()), NULL, SND_FILENAME | SND_ASYNC);
			putchar(' ');
			putchar(ch);
			line++;
		}
		else
		{
			if (!skip)
				PlaySound(TEXT(sound.c_str()), NULL, SND_FILENAME | SND_ASYNC);
			putchar(ch);
			col[line]++;
		}
	}
	fclose(fpin);

	read++;
	fpout = fopen(LOG_FILE, "w");
	fprintf(fpout, "read = %d", read);
	fclose(fpout);

	while (_kbhit())
		getch();
	printf("\n[Press any key to continue]");
	getch();

	system("CLS");
	
	return true;
}