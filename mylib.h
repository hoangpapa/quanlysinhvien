#pragma once // Avoid multiple inclusions of the header file

#include <stdio.h>
#include <conio.h>
#include <ctime> // Library for real-time support
#include <windows.h> // Windows-specific library

#define KEY_NONE -1

// Get the current X coordinate of the cursor
int whereX() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return -1;
}

// Get the current Y coordinate of the cursor
int whereY() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return -1;
}

// Move the cursor to the specified (x, y) position
void gotoXY(int x, int y) {
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Cursor_an_Pos = { x, y };
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Set the text color
void SetColor(WORD color) {
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

// Show or hide the cursor
void ShowCur(bool CursorVisibility) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
    SetConsoleCursorInfo(handle, &cursor);
}

// Return the key code of the pressed key
int inputKey() {
    if (_kbhit()) {
        int key = _getch();
        if (key == 224) {
            key = _getch();
            return key + 1000;
        }
        return key;
    } else {
        return KEY_NONE;
    }
}

// Set the text color
void textcolor(int x) {
    HANDLE mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}
