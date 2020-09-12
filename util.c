#include "util.h"

void gotoxy(int x, int y)	// Ŀ���� ��ġ�� �̵��ϴ� �Լ��̴�.
{
	COORD Position= { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Position);
}


void SetCursorVisible(BOOL visible)	// Ŀ���� �����Ÿ��� �ʰ� �ϴ� �Լ��̴�.
{
	CONSOLE_CURSOR_INFO true_or_false = { 10, visible };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &true_or_false);
}

void colorchange(int color)// ������ �ٲ��ִ� �Լ��̴�.
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}