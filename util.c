#include "util.h"

void gotoxy(int x, int y)	// 커서의 위치를 이동하는 함수이다.
{
	COORD Position= { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}


void SetCursorVisible(BOOL visible)	// 커서가 깜빡거리지 않게 하는 함수이다.
{
	CONSOLE_CURSOR_INFO true_or_false = { 10, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &true_or_false);
}

void colorchange(int color)// 색상을 바꿔주는 함수이다.
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}