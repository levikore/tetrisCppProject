#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <windows.h>
#include <process.h>
#include <conio.h>
#include <iostream>
using namespace std;

// function definition -- requires windows.h
inline void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// function definition -- requires process.h
inline void clrscr()
{
	system("cls");
}

inline void clearKeyboardBuffer()
{
	while (_kbhit())
	{
		_getch();
	}
}

inline void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}



#endif //!_UTILITY_H_