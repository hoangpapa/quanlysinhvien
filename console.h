#pragma once
#include <iostream>
#include <string>  
#include "mylib.h"
#include <iomanip>
using namespace std;
int xD = 5, yD = 0, wD = 112, hD = 27, tD = 15;//thong so cho box default 
int x = 50, y = 5;
int xL = 7, yL = 3, wL = 25, hL = 2;//thong so cho box list
const int CELL_WIDTH = 20; // Do rong cua o trong bang
const int ROW_HEIGHT = 2;
int	soDongMoiTrang = 20;
int xLB = 37, yLB = 4, wLB = 78, hLB = 22;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#define KEY_ESC 27

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
	int yp = y; // t?a d? c?a dòng dang du?c làm sáng
	int prevY = y; // t?a d? c?a m?c sáng tru?c dó
	int k = 0;    // ch? s? c?a m?c du?c ch?n

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
void xoa_noi_dung_khung() {
	int x = 36, y = 4; // T?a d? góc trên cùng c?a khung
	int width = 78, height = 20; // Kích thu?c khung
	// Xóa n?i dung bên trong khung (không xóa du?ng vi?n)
	textcolor(0);
	for (int iy = y; iy <= y + height; iy++) { // Duy?t t? dòng du?i du?ng vi?n trên
		for (int ix = x + 1; ix < x + width; ix++) { // Duy?t t? c?t bên ph?i du?ng vi?n trái
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	SetColor(7);
	for(int i = 20; i <= 110; i ++){
		gotoXY(i, 26); 
		cout << " ";
	}
}
void xoa_noi_dung_khung2() {
	int x = 35, y = 3; // T?a d? góc trên cùng c?a khung
	int width = 78, height = 21; // Kích thu?c khung
	// Xóa n?i dung bên trong khung (không xóa du?ng vi?n)
	textcolor(0);
	for (int iy = y + 1; iy <= y + height; iy++) { // Duy?t t? dòng du?i du?ng vi?n trên
		for (int ix = x + 1; ix < x + width; ix++) { // Duy?t t? c?t bên ph?i du?ng vi?n trái
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	gotoXY(30, 26); cout << "                                         ";
	SetColor(7);
}
void boxBetaDefault(int x, int y, int w, int h, int text_color, string nd) {
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
	int ndStartX = x + (w - nd.length()) / 2; 
	int ndStartY = y + 1;                  
	gotoXY(ndStartX, ndStartY);
	cout << nd;
}

void boxXacNhan(int x, int y, int w, int h, string noiDung, string luaChon1, string luaChon2, bool& xacNhan) {
	textcolor(0);
	for (int iy = y + 1; iy <= y + h; iy++) { 
		for (int ix = x + 1; ix < x + w; ix++) {
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	SetColor(7);
	boxBetaDefault(x, y, w, h, 14, noiDung); 
	int luaChonHienTai = 1; 
	while (true) {
		gotoXY(x + 2, y + h - 2);
		if (luaChonHienTai == 1) {
			SetColor(12); 
		}
		else {
			SetColor(7);
		}
		cout << "[" << luaChon1 << "]";

		gotoXY(x + w - 10, y + h - 2);
		if (luaChonHienTai == 2) {
			SetColor(12); 
		}
		else {
			SetColor(7); 
		}
		cout << "[" << luaChon2 << "]";
		if (kbhit()) {
			char key = _getch();
			if (key == 75) {
				luaChonHienTai = 1;
			}
			else if (key == 77) {
				luaChonHienTai = 2;
			}
			else if (key == 13) {
				xacNhan = (luaChonHienTai == 1);
				break;
			}
		}
	}
	SetColor(7); 
}
