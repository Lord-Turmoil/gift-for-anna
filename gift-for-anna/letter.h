#ifndef _LETTER_H_
#define _LETTER_H_

#include <cstdio>
#include <cstring>
#include <cctype>
#include <conio.h>
#include <ctime>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <Mmsystem.h>

#pragma comment(lib, "winmm.lib")

const char INPUT_FILE[] = "RESOURCES\\RAW_LETTER.TXT";
const char OUTPUT_FILE[] = "letter.txt";
const char LOG_FILE[] = "RESOURCES\\LOG.TXT";
const std::string SOUND_PRINT = "RESOURCES\\SOUNDS\\PRINT.WAV";
const std::string SOUND_SPACE = "RESOURCES\\SOUNDS\\SPACE.WAV";
const int MAX_LINE = 200;

void gotoPosition(int x, int y);
void hideCursor();
void showCursor();
int random(int left, int right);
bool writeLetter();

#endif