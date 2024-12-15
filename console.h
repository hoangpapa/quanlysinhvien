#pragma once
#include <iostream>
#include <string>  
#include "mylib.h"
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


void drawListBox(int x, int y, int w, int h, string data[][4], int soDuLieu, int soTrang, int selectedRow, int trangBefore, const string tieuDe[], int ntieuDe) {
	gotoXY(x, y);
	for (int i = 0; i < ntieuDe; i++) {
		printf("%-*s", w / ntieuDe, tieuDe[i].c_str());
	}
	cout << endl;

	int start = soTrang * trangBefore;
	int end = min(start + trangBefore, soDuLieu);
	for (int i = start; i < end; i++) {
		gotoXY(x, y + 1 + (i - start));
		if (i == selectedRow) {
			textcolor(14);
		}
		for (int j = 0; j < ntieuDe; j++) {
			printf("%-*s", w / ntieuDe, data[i][j].c_str());
		}
		if (i == selectedRow) {
			textcolor(11);
		}
		cout << endl;
	}
}
void xoa_noi_dung_khung() {
	int x = 36, y = 4; // T?a d? góc trên cùng c?a khung
	int width = 78, height = 20; // Kích thu?c khung
	// Xóa n?i dung bên trong khung (không xóa du?ng vi?n)
	textcolor(0);
	for (int iy = y + 1; iy <= y + height; iy++) { // Duy?t t? dòng du?i du?ng vi?n trên
		for (int ix = x + 1; ix < x + width; ix++) { // Duy?t t? c?t bên ph?i du?ng vi?n trái
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	SetColor(7);
}


int listBox( string data[][4], int soDuLieu,  string tieuDe[4], int ntieuDe) {
	int totalRows = soDuLieu;
	int sttOfTrang = 0;
	int hangNgangdangChon = 0;
	ShowCur(false);
	while (true) {

		drawListBox(xLB, yLB, wLB, hLB, data, soDuLieu, sttOfTrang, hangNgangdangChon, soDongMoiTrang, tieuDe, ntieuDe);

		int key = _getch();
		if (key == KEY_UP) {
			if (hangNgangdangChon > 0) {
				hangNgangdangChon--;
				if (hangNgangdangChon < sttOfTrang * soDongMoiTrang) {
					sttOfTrang--;
				}
			}
		}
		else if (key == KEY_DOWN) {
			if (hangNgangdangChon < totalRows - 1) {
				hangNgangdangChon++;
				if (hangNgangdangChon >= (sttOfTrang + 1) * soDongMoiTrang) {
					sttOfTrang++;
					xoa_noi_dung_khung();
				}
			}
		}
		else if (key == KEY_ENTER) {
			ShowCur(true);
			return hangNgangdangChon;
		}
		else if (key == KEY_ESC) {
			ShowCur(true);
			return -1;
		}
	}
}
