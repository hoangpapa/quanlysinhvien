#pragma once
#include <iostream>
#include <string>  
#include "mylib.h"
using namespace std;
int xD = 5, yD = 0, wD = 112, hD = 27, tD = 15;//thong so cho box default 
int x = 50, y = 5;
int xL = 7, yL = 3, wL = 25, hL = 2;//thong so cho box list


void boxDefault(int x, int y, int w, int h, int text_color,string nd) {
	SetColor(text_color);
	if (h <= 1 || w <= 1) return;
	for (int ix = x; ix <= x + w; ix++) {
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + h);
		cout << char(196);
	}
	for (int iy = y; iy <= y + h; iy++) {
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + w, iy);
		cout << char(179);
	}
	gotoXY(x, y);       cout << char(218);
	gotoXY(x + w, y);   cout << char(191);
	gotoXY(x, y + h);   cout << char(192);
	gotoXY(x + w, y + h); cout << char(217);
	gotoXY(w / 2.5, y + 1); cout << nd;
}
void boxVuong(int x, int y, int w, int h, int text_color) {
	SetColor(text_color);
	if (h <= 1 || w <= 1) return;
	for (int ix = x; ix <= x + w; ix++) {
		gotoXY(ix, y);
		cout << char(196);
		gotoXY(ix, y + h);
		cout << char(196);
	}
	for (int iy = y; iy <= y + h; iy++) {
		gotoXY(x, iy);
		cout << char(179);
		gotoXY(x + w, iy);
		cout << char(179);
	}
	gotoXY(x, y);       cout << char(218);
	gotoXY(x + w, y);   cout << char(191);
	gotoXY(x, y + h);   cout << char(192);
	gotoXY(x + w, y + h); cout << char(217);
}
int thanhSangListBox(int x, int y, int w, int h, int text_color, int highlight_color, string nd[], int soBox) {
	int yp = y; // tọa độ của dòng đang được làm sáng
	int prevY = y; // tọa độ của mục sáng trước đó
	int k = 0;    // chỉ số của mục được chọn

	ShowCur(false);
	for (int i = 0; i < soBox; i++) {
		if (i == 0) {
			boxDefault(x, y + i * (h + 1), w, h, highlight_color, nd[i]);
		}
		else {
			boxDefault(x, y + i * (h + 1), w, h, text_color, nd[i]);
		}
	}

	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == -32) {
				c = _getch();
				prevY = yp;

				if (c == 72) {
					if (yp != y)
						yp -= (h + 1);
					else
						yp = y + (h + 1) * (soBox - 1);
				}
				else if (c == 80) {
					if (yp != y + (h + 1) * (soBox - 1))
						yp += (h + 1);
					else
						yp = y;
				}

				boxDefault(x, prevY, w, h, text_color, nd[(prevY - y) / (h + 1)]);
				boxDefault(x, yp, w, h, highlight_color, nd[(yp - y) / (h + 1)]);
			}
			else if (c == 13) {
				k = (yp - y) / (h + 1);
				ShowCur(true);
				return k; //tra ve muc dc chon
			}
		}
	}
}

bool xacNhanThoat() {
	int bW = 30;
	int bH = 7;
	int oW = 10;
	int oH = 2;
	int x = (wD - bW) / 2;
	int y = (hD - bH) / 2;
	string question = "BAN CO MUON THOAT?";
	string options[] = { "CO", "KHONG" };
	int currentSelection = 0;
	ShowCur(false);
	boxDefault(x, y, bW, bH, 15, "");
	int questionX = x + (bW - question.length()) / 2;
	int questionY = y + 1;
	gotoXY(questionX, questionY);
	cout << question;
	for (int i = 0; i < 2; i++) {
		int optionX = x + (bW / 4) - (oW / 2) + (i * (bW / 2));
		int optionY = y + bH - 3;
		if (i == currentSelection) {
			boxDefault(optionX, optionY, oW, oH, 14, "");
		}
		else {
			boxDefault(optionX, optionY, oW, oH, 11, "");
		}
		int textX = optionX + (oW - options[i].length()) / 2;
		int textY = optionY + (oH / 2);
		gotoXY(textX, textY);
		cout << options[i];
	}

	while (true) {
		if (_kbhit()) {
			char key = _getch();
			if (key == -32) {
				key = _getch();
				if (key == 75) {
					currentSelection = (currentSelection + 1) % 2;
				}
				else if (key == 77) {
					currentSelection = (currentSelection + 1) % 2;
				}
			}
			else if (key == 13) {
				ShowCur(true);
				if (currentSelection == 0) {
					return true;
				}
				else {
					
					for (int i = 0; i < bH; i++) {
						gotoXY(x, y + i); 
						cout << "                                      ";
						gotoXY(x, y + i+1);
						cout << "                                      ";
					}
					return false;
				}
			}
			for (int i = 0; i < 2; i++) {
				int optionX = x + (bW / 4) - (oW / 2) + (i * (bW / 2));
				int optionY = y + bH - 3;

				if (i == currentSelection) {
					boxDefault(optionX, optionY, oW, oH, 14, "");
				}
				else {
					boxDefault(optionX, optionY, oW, oH, 11, "");
				}
				int textX = optionX + (oW - options[i].length()) / 2;
				int textY = optionY + (oH / 2);
				gotoXY(textX, textY);
				cout << options[i];
			}
		}
	}
}

















