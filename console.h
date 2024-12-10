#pragma once
#include <iostream>
#include <string>  
#include "mylib.h"
using namespace std;

void boxchuoi(int x, int y, int w, int h, int text_color, int b_color, string nd) {
	textcolor(b_color);
	for (int iy = y + 1; iy <= y + h - 1; iy++) {
		for (int ix = x + 1; ix <= x + w - 1; ix++) {
			gotoXY(ix, iy);
			cout << " ";
		}
	}
	SetColor(7);
	gotoXY(x + 1, y + 1);
	cout << nd;
	textcolor(1);
	/*SetColor(text_color);*/
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
void thanh_sang(int x, int y, int w, int h, int text_color) {
	SetColor(text_color);
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
void boxDefault(int x, int y, int w, int h, int text_color) {
	if (h <= 1 || w <= 1) return;
	SetColor(text_color);
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

void boxIngredient() {
	//boxDefault(5, 5, 100, 20, 15);//box lon
	//boxDefault(30, 6, 70, 17, 15);//box lon ben phai
	boxDefault(7, 6, 20, 14, 15);//box lon ben trai
	//boxColor(9, 8, 16, 2, 15,1,"Dang ky LTC");//box nho 1 ben trai
	//boxColor(9, 11, 16, 2, 15,1,"In DSSVDDK");//box nho 2 ben trai
	//boxColor(9, 14, 16, 2, 15,1,"Danh sach LTC");//box nho 3 ben trai
	//boxColor(9, 17, 16, 2, 15,1,"Thoat");//box nho 4 ben trai
}




