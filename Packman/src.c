#include "stdafx.h"
#include <Windows.h>


void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };
	BOOL bSuccess;
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	/* fill the entire screen with blanks */

	bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten);

	/* get the current text attribute */

	bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);

	/* now set the buffer's attributes accordingly */

	bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten);

	/* put the cursor at (0, 0) */

	bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
	return;
}

void clrscr()
{
	cls(GetStdHandle(STD_OUTPUT_HANDLE));
}

void delay(int milliseconds) {
	Sleep(milliseconds);
}

void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int kbhit()
{
	HANDLE hIn;
	INPUT_RECORD InRec;
	DWORD EventCount, fdwSaveOldMode, foo;
	int res = 0;

	hIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hIn, &fdwSaveOldMode);

	SetConsoleMode(hIn, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);

	GetNumberOfConsoleInputEvents(hIn, &EventCount);

	if (EventCount)
	{
		ReadConsoleInput(hIn, &InRec, 1, &foo);

		if (InRec.EventType == KEY_EVENT)
		{
			res = 1;
		}
	}
	return res;
}

char getch()
{
	HANDLE hIn;
	INPUT_RECORD InRec;
	DWORD EventCount, fdwSaveOldMode, foo;

	hIn = GetStdHandle(STD_INPUT_HANDLE);

	GetConsoleMode(hIn, &fdwSaveOldMode);

	SetConsoleMode(hIn, ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT);


	for (;;)
	{
		GetNumberOfConsoleInputEvents(hIn, &EventCount);

		if (EventCount)
		{
			ReadConsoleInput(hIn, &InRec, 1, &foo);

			if (InRec.EventType == KEY_EVENT)
			{
				SetConsoleMode(hIn, fdwSaveOldMode);
				return static_cast<signed char>(InRec.Event.KeyEvent.uChar.AsciiChar);
			}
		}
	}
}

struct object
{
	char face[10];
	int x;
	int y;
};

int _tmain(int argc, _TCHAR* argv[])
{
	struct object player = { "(OO)", 30, 15 };
	struct object enemy1 = { "(xx)", 10, 10 };
	//struct object enemy2 = { "(XX)", 30, 15 };

	char i = 0;
	while (i != 'q')
	{
		gotoxy(player.x, player.y);
		printf(player.face);
		gotoxy(enemy1.x, enemy1.y);
		printf(enemy1.face);
		i = getch();
		gotoxy(player.x, player.y);
		for (int j = 0; j < strlen(player.face); j++)
			printf(" ");
		gotoxy(enemy1.x, enemy1.y);
		for (int j = 0; j < strlen(enemy1.face); j++)
			printf(" ");

		switch (i)
		{
		case 'i':
			player.y--;
			break;
		case 'k':
			player.y++;
			break;
		case 'j':
			player.x--;
			break;
		case 'l':
			player.x++;
			break;
		case 'w':
			enemy1.y--;
			break;
		case 's':
			enemy1.y++;
			break;
		case 'a':
			enemy1.x--;
			break;
		case 'd':
			enemy1.x++;
			break;
		default:
			break;
		}
		delay(10);
	}
	return 0;
}