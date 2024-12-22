	#pragma once // tránh d?ng d? thu vi?n khi g?i ch?ng file lên nhau
	#include <stdio.h>
	#include <conio.h>
	#include<ctime> /* thu vi?n h? tr? v? th?i gian th?c */
	#include "windows.h" // thu vi?n này bá d?o l?m nhé - ch?a nhi?u d? choi nek - c? tìm hi?u d?n d?n s
	//======= l?y t?a d? x c?a con tr? hi?n t?i =============
	#define KEY_NONE	-1

	int whereX()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return csbi.dwCursorPosition.X;
		return -1;
	}
	//========= l?y t?a d? y c?a con tr? hi?n t?i =======
	int whereY()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return csbi.dwCursorPosition.Y;
		return -1;
	}
	//============== d?ch con tr? hi?n t?i d?n di?m có t?a d? (x,y) ==========
	void gotoXY(int x, int y)
	{
		HANDLE hConsoleOutput;
		COORD Cursor_an_Pos = { x, y };
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
	}
	//============= d?t màu cho ch? =========
	void SetColor(WORD color)
	{
		HANDLE hConsoleOutput;
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
		GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

		WORD wAttributes = screen_buffer_info.wAttributes;
		color &= 0x000f;
		wAttributes &= 0xfff0;
		wAttributes |= color;

		SetConsoleTextAttribute(hConsoleOutput, wAttributes);
	}
	//============== làm ?n tr? chu?t ===========
	void ShowCur(bool CursorVisibility)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
		SetConsoleCursorInfo(handle, &cursor);
	}
	//======= tr? v? mã phím ngu?i dùng b?m =========
	int inputKey()
	{
		if (_kbhit()) //true
		{
			int key = _getch();

			if (key == 224)
			{
				key = _getch();
				return key + 1000;
			}

			return key;
		}
		else
		{
			return KEY_NONE;
		}
		return KEY_NONE;
	}
	void textcolor(int x)
	{
		HANDLE mau;
		mau = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(mau, x);
	}
	void HideCursor() {
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
		cursorInfo.bVisible = FALSE;  // ?n con tr?
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}
	void ShowCursor() {
		CONSOLE_CURSOR_INFO cursorInfo;
		GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
		cursorInfo.bVisible = TRUE;   // Hi?n th? l?i con tr?
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	}
void setConsoleBackgroundWhite() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
    
    // Đặt màu nền trắng (15) và màu chữ đen (0)
    SetConsoleTextAttribute(hConsole, 240); // 240 = 15 * 16 + 0
    
    // Làm sạch console để áp dụng nền trắng cho toàn bộ màn hình
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    DWORD written; // Số ký tự đã được ghi
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD topLeft = {0, 0}; // Vị trí góc trên bên trái của console

    // Làm sạch màn hình với màu nền trắng
    FillConsoleOutputAttribute(hConsole, 240, consoleSize, topLeft, &written);
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, topLeft, &written);
    SetConsoleCursorPosition(hConsole, topLeft); // Đưa con trỏ về đầu màn hình
}
void SetBColor(int textColor, int bgColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}