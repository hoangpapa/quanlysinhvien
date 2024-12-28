#include <iostream>
#include <cstring>  // Su dung thu vien string
#include <cctype>  // Thu vi?n h? tr? ki?m tra k? t?
#include <sstream>
#include "mylib.h"
#include "console.h"
#include <math.h>
#include <iomanip>
#include <fstream>
//#include <bits/stdc++.h>

using namespace std;
const int MAXLOPSV = 10000;
const int MAX_LTC = 10000;
const int MAX_SIZE_NAME_MH = 50;


struct MonHoc {
    string MAMH;
    string TENMH;
    int STCLT, STCTH;
};

struct nodeMH {
    MonHoc mh;
    int bf;
    nodeMH* left, * right;
};
typedef nodeMH* treeMH;

struct SinhVien {
    string MASV; string HO; string TEN;
    string  PHAI; string SODT;
};

struct nodeSV {
    SinhVien sv;
    nodeSV* next;
    int n=0;
};
typedef nodeSV* PTRSV;

struct LopSV {
    string MALOP;
    string TENLOP;
    PTRSV First = NULL;
};

struct DS_LOPSV {
    int n = 0;
    LopSV nodes[MAXLOPSV];
};
struct DangKy {
    string MASV; float DIEM = -1.0; bool huydangky = false;
};

struct nodeDK {
    DangKy dk;
    nodeDK* next;
};
typedef nodeDK* PTRDK;

struct LopTinChi {
    int MALOPTC;
    string  MAMH;
    string NienKhoa;
    int Hocky, Nhom, sosvmin, sosvmax;
    bool huylop = false;
    PTRDK dssvdk = NULL;
};

struct List_LTC {
    int n = 0;
    LopTinChi* nodes[MAX_LTC];
    // PTRSV First = NULL;
};
int DemSoSinhVien(PTRDK dssvdk) {
    int count = 0;
    while (dssvdk != NULL) {
        if (!dssvdk->dk.huydangky) {
            count++;
        }
        dssvdk = dssvdk->next;
    }
    return count;
}
int countSVtrongLop(PTRSV sv) {
    int i = 0;
    while (sv != NULL) {
        i++;
        sv = sv->next;
    }
    return i;
}
void xuat_file_dsLop(DS_LOPSV dsLop) {
    ofstream xuatFile;
    xuatFile.open("C:\\Users\\admin\\Downloads\\C++\\dsLop.txt");
    xuatFile << dsLop.n << endl;
    for (int i = 0; i < dsLop.n; i++) {
        xuatFile << dsLop.nodes[i].MALOP << "," << dsLop.nodes[i].TENLOP << endl;
    }
    xuatFile.close();
}

void xuat_file_DSSV(DS_LOPSV dsLopSV) {
    
    ofstream xuatFile;
    
    xuatFile.open("C:\\Users\\admin\\Downloads\\C++\\dsSV.txt");
    xuatFile<<dsLopSV.n<<endl;
    for(int i =0; i<dsLopSV.n;i++){
        PTRSV a = dsLopSV.nodes[i].First;
        int soDuLieu= countSVtrongLop(a);
            xuatFile << soDuLieu << endl;
            while (a != NULL) {
                xuatFile << a->sv.MASV << "," << a->sv.HO<<"," << a->sv.TEN<<"," << a->sv.PHAI<<"," << a->sv.SODT << endl;
                a = a->next;
            }
    }
     xuatFile.close();
}
// void xuat_file_SVDKLTC(List_LTC ds){
//     ofstream xuatFile;
//     xuatFile.open("C:\\Users\\admin\\Downloads\\C++\\dsdkltc.txt");
//     for(int i =0;i<ds.n;i++){
//         xuatFile<<ds.nodes[i]->MALOPTC<<","<<ds.nodes[i]->MAMH<<","<<ds.nodes[i]->NienKhoa<<","<<ds.nodes[i]->Hocky<<","<<ds.nodes[i]->Nhom<<","<<ds.nodes[i]->sosvmin<<","<<ds.nodes[i]->sosvmax<<","<<endl;

//     }

// }
void xuat_file_SVDKLTC(List_LTC ds){
    ofstream xuatFile;
    xuatFile.open("C:\\Users\\admin\\Downloads\\C++\\dsdkltc.txt");
    xuatFile<<ds.n<<endl;
    int soSVDK;
    for(int i =1;i<=ds.n;i++){
         soSVDK =DemSoSinhVien(ds.nodes[i]->dssvdk);
         xuatFile << soSVDK << ",";
        xuatFile<<ds.nodes[i]->MALOPTC<<","<<soSVDK<<endl;
       
        PTRDK tmp = ds.nodes[i]->dssvdk;
        while(tmp!=NULL){
            xuatFile << tmp->dk.MASV << ",";
            tmp = tmp->next;
        }
        xuatFile<<endl;
    }

}

void box_huong_dan_menu() {
    textcolor(0);
    SetColor(2);
    for (int ix = 45; ix <= 100; ix++) {
        gotoXY(ix, 18);
        cout << char(196);
        gotoXY(ix, 24);
        cout << char(196);
    }
    for (int iy = 18; iy <= 24; iy++) {
        gotoXY(45, iy);
        cout << char(179);
        gotoXY(100, iy);
        cout << char(179);
    }
    gotoXY(45, 18); cout << char(218);
    gotoXY(100, 18); cout << char(191);
    gotoXY(45, 24); cout << char(192);
    gotoXY(100, 24); cout << char(217);
    SetColor(11);
    gotoXY(55, 20); cout << "DUNG MUI TEN LEN XUONG DE DI CHUYEN";
    gotoXY(59, 22); cout << "AN PHIM ENTER DE CHON";
}

bool kiemTraNienKhoa(string& nienKhoa) {
    if (nienKhoa.length() != 9) return false;
    if (nienKhoa[4] != '-') return false;      // K? t? th? 5 ph?i l? d?u '-'
    string namBatDauStr = nienKhoa.substr(0, 4);      // L?y 4 k? t? d?u ti?n
    string namKetThucStr = nienKhoa.substr(5, 4);     // L?y 4 k? t? cu?i c?ng
    int namBatDau = stoi(namBatDauStr);               // Chuy?n th?nh s? nguy?n
    int namKetThuc = stoi(namKetThucStr);             // Chuy?n th?nh s? nguy?n
    if (namKetThuc != namBatDau + 1) {
        return false;
    }
    return true;
}

bool kiemTraChuoiSo(string& input) {
    for (auto c : input) {
        if (!isdigit(c)) {  // Ki?m tra t?ng k? t? c? ph?i l? s? kh?ng
            return false;
        }
    }
    return true;
}

bool check(string s) {
    if (s.size() > MAX_SIZE_NAME_MH) {
        cout << "Ma mon hoc khong duoc qua 50 ki tu!!!\n";
        return true;
    }
    for (auto x : s) {
        if (!isdigit(x) && !isalpha(x)) {
            cout << "Ma mon hoc khong duoc co ki tu dac biet!!!\n";
            return true;
        }
    }
    return false;
}

// Ham tim kiem mon hoc theo ma
treeMH searchMH(treeMH root, string& mamh) {
    if (root == NULL) return NULL;
    if (root->mh.MAMH == mamh) return root;
    if (root->mh.MAMH > mamh) return searchMH(root->left, mamh);
    return searchMH(root->right, mamh);
}

// Ham kiem tra ma mon hoc da ton tai chua
bool isDuplicateMH(treeMH root, string& mamh) {
    return searchMH(root, mamh) != NULL;
}

// tim kiem nhi phan
int TimLTC(int ma, List_LTC dsltc) {
    int left = 1;
    int right = dsltc.n;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (dsltc.nodes[mid]->MALOPTC == ma) return mid;
        else if (dsltc.nodes[mid]->MALOPTC < ma) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void xoaLopTinChi_2(List_LTC& dsltc, int index) {
    if (dsltc.nodes[index]->dssvdk != NULL) {
        gotoXY(50, 26);
        SetColor(8);
        cout << "Da co sv dk ltc nay - ko the xoa!";
        SetColor(7);
        for (int i = 1; i <= 300000000; i++);
        gotoXY(50, 26);
        cout << "                                     ";
    }
    else {
        bool xacNhan;
        HideCursor();
        boxXacNhan(40, 10, 30, 5, "Xac nhan xoa mon hoc?", "Co", "Khong", xacNhan);
        if (xacNhan) {
            delete dsltc.nodes[index];
            for (int j = index; j <= dsltc.n - 1; j++) {
                dsltc.nodes[j] = dsltc.nodes[j + 1];
            }
            dsltc.n--;
            return;
        }
    }
}

void drawListBoxLTC(int x, int y, int w, int h, List_LTC& dsltc, int soTrang, int chonHang, int soDongMoiTrang, const string tieuDe[], int ntieuDe, int index, int khoangCachMoiCot[], int& viTri) {
    SetColor(2);
    gotoXY(x, y);
    printf("%-*s", khoangCachMoiCot[0], "STT");
    for (int i = 0; i < ntieuDe; i++) {
        printf("%-*s", khoangCachMoiCot[i + 1], tieuDe[i].c_str());
    }
    SetColor(7);
    cout << endl;
    int start = soTrang * soDongMoiTrang;
    int end = min(start + soDongMoiTrang, dsltc.n);
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    for (int i = start + 1; i <= end; i++) {
        gotoXY(x, y + (i - start));
        if (i == chonHang) {
            viTri = index;
            textcolor(200);
            SetColor(0);
        }
        printf("%-*d", khoangCachMoiCot[0], index);
        printf("%-*d", khoangCachMoiCot[1], dsltc.nodes[i]->MALOPTC);
        printf("%-*s", khoangCachMoiCot[2], dsltc.nodes[i]->MAMH.c_str());
        printf("%-*s", khoangCachMoiCot[3], dsltc.nodes[i]->NienKhoa.c_str());
        printf("%-*d", khoangCachMoiCot[4], dsltc.nodes[i]->Hocky);
        printf("%-*d", khoangCachMoiCot[5], dsltc.nodes[i]->Nhom);
        printf("%-*d", khoangCachMoiCot[6], dsltc.nodes[i]->sosvmin);
        printf("%-*d", khoangCachMoiCot[7], dsltc.nodes[i]->sosvmax);
        index++;
        textcolor(7);
    }
}

int listBoxLTC(List_LTC& dsltc, const string tieuDe[], int ntieuDe, int input) {
    int khoangCachMoiCot[] = { wLB * 0.07, wLB * 0.2, wLB * 0.18, wLB * 0.15, wLB * 0.15, wLB * 0.1, wLB * 0.1, wLB * 0.1 };
    int totalRows = dsltc.n;
    int sttOfTrang = 0;
    int hangNgangdangChon = 1;
    int soDongMoiTrang = 20; // S? d?ng hi?n th? m?i trang
    int viTri;
    ShowCur(false);
    int index = 1;
    while (true) {
        drawListBoxLTC(xLB, yLB, wLB, hLB, dsltc, sttOfTrang, hangNgangdangChon, soDongMoiTrang, tieuDe, ntieuDe, index, khoangCachMoiCot, viTri);
        int key = _getch();
        if (key == KEY_UP) {
            if (hangNgangdangChon > 1) {
                hangNgangdangChon--;
                if (hangNgangdangChon <= sttOfTrang * soDongMoiTrang) {
                    sttOfTrang--;
                    index -= 20;
                }
            }
        }
        else if (key == KEY_DOWN) {
            if (hangNgangdangChon < totalRows) {
                hangNgangdangChon++;
                if (hangNgangdangChon > (sttOfTrang + 1) * soDongMoiTrang) {
                    sttOfTrang++;
                    index += 20;
                    xoa_noi_dung_khung();
                }
            }
        }
        else if (key == KEY_ENTER && input == 0) {
            ShowCursor();
            return viTri;
        }
        else if (key == KEY_ESC) {
            ShowCur(true);
            return -1;
        }
    }
}

void HienThi_Sua_ltc(LopTinChi& ltc, int viTriChon, int viTriChon_cu, string text[]) {
    for (int i = 0; i < 7; i++) {
        if (viTriChon == 8 + i * 2 || viTriChon_cu == 8 + i * 2) {
            gotoXY(40, 8 + i * 2);
            if (viTriChon == 8 + i * 2) SetColor(4);
            else SetColor(7);
            cout << text[i];
            if (i == 0) cout << ltc.MAMH;
            else if (i == 1) cout << ltc.NienKhoa;
            else if (i == 2) cout << ltc.Hocky;
            else if (i == 3) cout << ltc.Nhom;
            else if (i == 4) cout << ltc.sosvmin;
            else if (i == 5) cout << ltc.sosvmax;
            SetColor(7);
        }
    }
}

void Nhap_ma_mon_hoc_ltc(LopTinChi& ltc, int viTriChon, treeMH& root, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                    ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP MA MON HOC: ";
        else if (input == 1) cout << "SUA MA MON HOC: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (isDuplicateMH(root, input)) {
            ltc.MAMH = input;
            break;
        }
        gotoXY(40, 24);
        cout << "Khong ton tai ma mon hoc nay!";
        for (int i = 1; i <= 1000000000; i++);
        gotoXY(40, 24);
        cout << "                               ";
    } while (1);
    HideCursor();
}

void Nhap_nien_khoa_ltc(LopTinChi& ltc, int viTriChon, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP NIEN KHOA: ";
        else if (input == 1) cout << "SUA NIEN KHOA: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (kiemTraNienKhoa(input)) {
            ltc.NienKhoa = input;
            break;
        }
        gotoXY(40, 24);
        cout << "Loi: Nien khoa khong hop le. Vui long nhap lai!";
        for (int i = 1; i <= 300000000; i++);
        gotoXY(40, 24);
        cout << "                                                 ";
    } while (1);
    HideCursor();
};

void Nhap_hoc_ki_ltc(LopTinChi& ltc, int viTriChon, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP HOC KY: ";
        else if (input == 1) cout << "SUA HOC KY: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (kiemTraChuoiSo(input)) {
            ltc.Hocky = stoi(input);
            break;
        }
        gotoXY(40, 24);
        cout << "Loi: Hoc ky la so nguyen duong. Vui long nhap lai!";
        for (int i = 1; i <= 300000000; i++);
        gotoXY(40, 24);
        cout << "                                                   ";
    } while (1);
    HideCursor();
}

void Nhap_nhom_ltc(LopTinChi& ltc, int viTriChon, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP NHOM: ";
        else if (input == 1) cout << "SUA NHOM: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (kiemTraChuoiSo(input)) {
            ltc.Nhom = stoi(input);
            break;
        }
        gotoXY(40, 24);
        cout << "Loi: Nhom la so nguyen duong. Vui long nhap lai!";
        for (int i = 1; i <= 300000000; i++);
        gotoXY(40, 24);
        cout << "                                                   ";
    } while (1);
    HideCursor();
};

void Nhap_sosvmin_ltc(LopTinChi& ltc, int viTriChon, int input) {
    \
        do {
            SetColor(4);
            gotoXY(40, viTriChon);
            cout << "                                             ";
            gotoXY(40, viTriChon);
            if (input == 0) cout << "NHAP SO SINH VIEN TOI THIEU: ";
            else if (input == 1) cout << "SUA SO SINH VIEN TOI THIEU: ";
            ShowCursor();
            string input;
            getline(cin, input);
            if (input == "|") {
                HideCursor();
                return;
            }
            if (!kiemTraChuoiSo(input)) {
                gotoXY(40, 24);
                cout << "Loi: So SV min la so nguyen duong. Vui long nhap lai!";
                for (int i = 1; i <= 300000000; i++);
                gotoXY(40, 24);
                cout << "                                                         ";
                continue;
            }
            if (ltc.sosvmax != -1) {
                if (stoi(input) > ltc.sosvmax) {
                    gotoXY(40, 24);
                    cout << "Loi: So SV min khong duoc lon hon so SV max!";
                    for (int i = 1; i <= 300000000; i++);
                    gotoXY(40, 24);
                    cout << "                                                         ";
                    continue;
                }
            }
            ltc.sosvmin = stoi(input);
            break;
        } while (1);
    HideCursor();
}

void Nhap_sosvmax_ltc(LopTinChi& ltc, int viTriChon, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                             ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP SO SINH VIEN TOI DA: ";
        else if (input == 1) cout << "SUA SO SINH VIEN TOI DA: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (!kiemTraChuoiSo(input)) {
            gotoXY(40, 24);
            cout << "Loi: So SV max la so nguyen duong. Vui long nhap lai!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                                         ";
            continue;
        }
        if (ltc.sosvmin != -1) {
            if (stoi(input) < ltc.sosvmin) {
                gotoXY(40, 24);
                cout << "Loi: So SV max khong duoc nho hon so SV min!";
                for (int i = 1; i <= 300000000; i++);
                gotoXY(40, 24);
                cout << "                                                         ";
                continue;
            }
        }
        ltc.sosvmax = stoi(input);
        break;
    } while (1);
    HideCursor();
}

void Sua_xoaLopTinChi(List_LTC& dsltc, treeMH& root, int input);
void suaLopTinChi(List_LTC& dsltc, treeMH& root, int viTri) {
    HideCursor();
    LopTinChi ltc = *dsltc.nodes[viTri];
    xoa_noi_dung_khung();
    gotoXY(65, 4);
    SetColor(9);
    cout << "SUA LOP TIN CHI";
    SetColor(7);
    int viTriChon = 8;
    string text[7] = { "SUA MA MON HOC: ", "SUA NIEN KHOA: ", "SUA HOC KY: ",
                "SUA NHOM: ", "SUA SO SINH VIEN TOI THIEU: ", "SUA SO SINH VIEN TOI DA: ", "          ===CHON LUU===" };
    gotoXY(40, 6);
    SetColor(8);
    cout << "MA LOP TIN CHI: " << ltc.MALOPTC;
    SetColor(7);
    for (int i = 0; i < 7; i++) {
        gotoXY(40, 8 + i * 2);
        SetColor(7);
        if (viTriChon == 8 + i * 2) SetColor(4);
        cout << text[i];
        if (i == 0) cout << ltc.MAMH;
        else if (i == 1) cout << ltc.NienKhoa;
        else if (i == 2) cout << ltc.Hocky;
        else if (i == 3) cout << ltc.Nhom;
        else if (i == 4) cout << ltc.sosvmin;
        else if (i == 5) cout << ltc.sosvmax;
        SetColor(7);
    }
    SetColor(12);
    gotoXY(30, 26);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            gotoXY(30, 24);
            cout << "                                                         ";
            SetColor(12);
            gotoXY(30, 26);
            cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
            if (key == 72) {
                if (viTriChon > 8) {
                    viTriChon -= 2;
                    HienThi_Sua_ltc(ltc, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui t?n xu?ng
                if (viTriChon < 20) {
                    viTriChon += 2;
                    HienThi_Sua_ltc(ltc, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap diem
                if (viTriChon == 20) {
                    bool tonTai = false;
                    for (int i = 1; i <= dsltc.n; i++) {
                        if (ltc.MAMH == dsltc.nodes[i]->MAMH && ltc.NienKhoa == dsltc.nodes[i]->NienKhoa && ltc.Hocky
                            == dsltc.nodes[i]->Hocky && ltc.Nhom == dsltc.nodes[i]->Nhom) {
                            gotoXY(40, 24);
                            SetColor(11);
                            tonTai = true;
                            cout << "LOP TIN CHI NAY DA TON TAI!";
                            break;
                        }
                    }
                    if (!tonTai) {
                        dsltc.nodes[viTri] = &ltc;
                        gotoXY(40, 24);
                        SetColor(10);
                        cout << "Hieu chinh lop tin chi thanh cong!";
                        SetColor(7);
                        for (int i = 1; i <= 370000000; i++);
                        gotoXY(40, 24);
                        cout << "                                                         ";
                        return;
                    }
                }
                else {
                    SetColor(12);
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 8) Nhap_ma_mon_hoc_ltc(ltc, viTriChon, root, 1);
                    else if (viTriChon == 10) Nhap_nien_khoa_ltc(ltc, viTriChon, 1);
                    else if (viTriChon == 12) Nhap_hoc_ki_ltc(ltc, viTriChon, 1);
                    else if (viTriChon == 14) Nhap_nhom_ltc(ltc, viTriChon, 1);
                    else if (viTriChon == 16) Nhap_sosvmin_ltc(ltc, viTriChon, 1);
                    else if (viTriChon == 18) Nhap_sosvmax_ltc(ltc, viTriChon, 1);
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                xoa_noi_dung_khung();
                ShowCursor();
                return;
            }
        }
    }
}

// Sua Xoa lop tin chi (hien thi danh sach lop tin chi truoc khi xoa) 
void Sua_xoaLopTinChi(List_LTC& dsltc, treeMH& root, int input) {
    int nTieuDe = 7;
    SetColor(9);
    int viTri;
    string tieuDe[] = { "MaLopTC", "MaMH", "NienKhoa", "HocKy", "Nhom", "SVMIN", "SVMAX" };
    while (1) {
        viTri = listBoxLTC(dsltc, tieuDe, nTieuDe, 0);
        if (viTri == -1) {
            xoa_noi_dung_khung();
            return;
        }
        else {
            if (input == 0) {
                xoaLopTinChi_2(dsltc, viTri);
                xoa_noi_dung_khung();
                Sua_xoaLopTinChi(dsltc, root, input);
                return;
            }
            else if (input == 1) {
                suaLopTinChi(dsltc, root, viTri);
                xoa_noi_dung_khung();
                Sua_xoaLopTinChi(dsltc, root, input);
                return;
            }
        }
    }
}

void HienThi_Them_ltc(LopTinChi& ltc, int viTriChon, int viTriChon_cu, string text[]) {
    for (int i = 0; i < 7; i++) {
        gotoXY(40, 8 + i * 2);
        if (viTriChon == 8 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (ltc.MAMH != "--") cout << ltc.MAMH;
                else cout << "--";
            }
            else if (i == 1) {
                if (ltc.NienKhoa != "--") cout << ltc.NienKhoa;
                else cout << "--";
            }
            else if (i == 2) {
                if (ltc.Hocky != -1) cout << ltc.Hocky;
                else cout << "--";
            }
            else if (i == 3) {
                if (ltc.Nhom != -1) cout << ltc.Nhom;
                else cout << "--";
            }
            else if (i == 4) {
                if (ltc.sosvmin != -1) cout << ltc.sosvmin;
                else cout << "--";
            }
            else if (i == 5) {
                if (ltc.sosvmax != -1) cout << ltc.sosvmax;
                else cout << "--";
            }
            SetColor(7);
        }
        else if (viTriChon_cu == 8 + i * 2) {
            SetColor(7);
            cout << text[i];
            if (i == 0) {
                if (ltc.MAMH != "--") cout << ltc.MAMH;
                else cout << "--";
            }
            else if (i == 1) {
                if (ltc.NienKhoa != "--") cout << ltc.NienKhoa;
                else cout << "--";
            }
            else if (i == 2) {
                if (ltc.Hocky != -1) cout << ltc.Hocky;
                else cout << "--";
            }
            else if (i == 3) {
                if (ltc.Nhom != -1) cout << ltc.Nhom;
                else cout << "--";
            }
            else if (i == 4) {
                if (ltc.sosvmin != -1) cout << ltc.sosvmin;
                else cout << "--";
            }
            else if (i == 5) {
                if (ltc.sosvmax != -1) cout << ltc.sosvmax;
                else cout << "--";
            }
        }
    }
}

// Them lop tin chi (co nut quay lai)
void themLopTinChi(List_LTC& dsltc, treeMH root) {
    HideCursor();
    LopTinChi ltc;
    xoa_noi_dung_khung();
    gotoXY(65, 4);
    SetColor(9);
    cout << "THEM LOP TIN CHI";
    SetColor(12);
    gotoXY(30, 26);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
    if (dsltc.n == 0) ltc.MALOPTC = 1;
    else ltc.MALOPTC = (dsltc.nodes[dsltc.n]->MALOPTC + 1);
    ltc.MAMH = "--"; ltc.NienKhoa = "--"; ltc.Hocky = -1; ltc.Nhom = -1; ltc.sosvmin = -1; ltc.sosvmax = -1;
    int viTriChon = 8;
    string text[7] = { "NHAP MA MON HOC: ", "NHAP NIEN KHOA: ", "NHAP HOC KY: ",
                "NHAP NHOM: ", "NHAP SO SINH VIEN TOI THIEU: ", "NHAP SO SINH VIEN TOI DA: ", "          ===CHON LUU===" };
    gotoXY(40, 6);
    SetColor(8);
    cout << "MA LOP TIN CHI MOI: " << ltc.MALOPTC;
    SetColor(7);
    for (int i = 0; i < 7; i++) {
        gotoXY(40, 8 + i * 2);
        if (viTriChon == 8 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (ltc.MAMH != "--") cout << ltc.MAMH;
                else cout << "--";
            }
            else if (i == 1) {
                if (ltc.NienKhoa != "--") cout << ltc.NienKhoa;
                else cout << "--";
            }
            else if (i == 2) {
                if (ltc.Hocky != -1) cout << ltc.Hocky;
                else cout << "--";
            }
            else if (i == 3) {
                if (ltc.Nhom != -1) cout << ltc.Nhom;
                else cout << "--";
            }
            else if (i == 4) {
                if (ltc.sosvmin != -1) cout << ltc.sosvmin;
                else cout << "--";
            }
            else if (i == 5) {
                if (ltc.sosvmax != -1) cout << ltc.sosvmax;
                else cout << "--";
            }
            SetColor(7);
        }
        else {
            cout << text[i];
            if (i == 0) {
                if (ltc.MAMH != "--") cout << ltc.MAMH;
                else cout << "--";
            }
            else if (i == 1) {
                if (ltc.NienKhoa != "--") cout << ltc.NienKhoa;
                else cout << "--";
            }
            else if (i == 2) {
                if (ltc.Hocky != -1) cout << ltc.Hocky;
                else cout << "--";
            }
            else if (i == 3) {
                if (ltc.Nhom != -1) cout << ltc.Nhom;
                else cout << "--";
            }
            else if (i == 4) {
                if (ltc.sosvmin != -1) cout << ltc.sosvmax;
                else cout << "--";
            }
            else if (i == 5) {
                if (ltc.sosvmin != -1) cout << ltc.sosvmax;
                else cout << "--";
            }
        }
    }
    while (true) {
        if (_kbhit()) {
            SetColor(12);
            gotoXY(30, 26);
            cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
            SetColor(7);
            char key = _getch();  // L?y k? t? ngu?i d?ng nh?n
            if (key == 72) {  // Mui t?n l?n
                if (viTriChon > 8) {
                    viTriChon -= 2;
                    HienThi_Them_ltc(ltc, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui t?n xu?ng
                if (viTriChon < 20) {
                    viTriChon += 2;
                    HienThi_Them_ltc(ltc, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap diem
                bool luu = false;
                if (viTriChon == 20) {
                    int ok = -1;
                    if (ltc.MAMH == "--") ok = 8;
                    else if (ltc.NienKhoa == "--") ok = 10;
                    else if (ltc.Hocky == -1) ok = 12;
                    else if (ltc.Nhom == -1) ok = 14;
                    else if (ltc.sosvmin == -1) ok = 16;
                    else if (ltc.sosvmax == -1) ok = 18;
                    if (ok == -1) {
                        for (int i = 1; i <= dsltc.n; i++) {
                            if (ltc.MAMH == dsltc.nodes[i]->MAMH && ltc.NienKhoa == dsltc.nodes[i]->NienKhoa && ltc.Hocky
                                == dsltc.nodes[i]->Hocky && ltc.Nhom == dsltc.nodes[i]->Nhom) {
                                gotoXY(40, 24);
                                SetColor(4);
                                cout << "LOP TIN CHI NAY DA TON TAI!";
                                SetColor(7);
                                for (int i = 1; i <= 400000000; i++);
                                gotoXY(40, 24);
                                cout << "                                                         ";
                                luu = true;
                                break;
                            }
                        }
                        if (!luu) {
                            dsltc.nodes[++dsltc.n] = new LopTinChi(ltc);
                            gotoXY(40, 24);
                            SetColor(10);
                            cout << "Them moi lop tin chi thanh cong!";
                            SetColor(7);
                            for (int i = 1; i <= 370000000; i++);
                            gotoXY(40, 24);
                            cout << "                                                         ";
                            themLopTinChi(dsltc, root);
                            return;
                        }
                    }
                    else {
                        SetColor(4);
                        gotoXY(62, 24);
                        cout << "    Nhap thong tin chua day du!";
                        for (int i = 0; i <= 900000000; i++);
                        textcolor(0);
                        gotoXY(62, 24); cout << "                                      ";
                        textcolor(7);
                        SetColor(7);
                        viTriChon = ok;
                        HienThi_Them_ltc(ltc, ok, 20, text);
                    }
                }
                else {
                    SetColor(12);
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    int ok = 20;
                    if (viTriChon == 8) Nhap_ma_mon_hoc_ltc(ltc, viTriChon, root, 0);
                    else if (viTriChon == 10) Nhap_nien_khoa_ltc(ltc, viTriChon, 0);
                    else if (viTriChon == 12) Nhap_hoc_ki_ltc(ltc, viTriChon, 0);
                    else if (viTriChon == 14) Nhap_nhom_ltc(ltc, viTriChon, 0);
                    else if (viTriChon == 16) Nhap_sosvmin_ltc(ltc, viTriChon, 0);
                    else if (viTriChon == 18) Nhap_sosvmax_ltc(ltc, viTriChon, 0);
                    gotoXY(30, 26); cout << "                                                                          ";
                    //======
                    if (ltc.MAMH == "--") ok = 8;
                    else if (ltc.NienKhoa == "--") ok = 10;
                    else if (ltc.Hocky == -1) ok = 12;
                    else if (ltc.Nhom == -1) ok = 14;
                    else if (ltc.sosvmin == -1) ok = 16;
                    else if (ltc.sosvmax == -1) ok = 18;
                    HienThi_Them_ltc(ltc, ok, viTriChon, text);
                    viTriChon = ok;
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}



bool kiemTraSoDienThoai(string SODT) {
    if (SODT.size() != 10) return false;
    for (int i = 0; i < 10; i++) {
        if (!isdigit(SODT[i])) {
            return false;
        }
    }
    return true;
}

// Ham kiem tra ten hoac ho sinh vien (chi chua chu cai)
bool kiemTraTenHo(string& tenHo) {
    for (int i = 0; i < tenHo.size(); i++) {
        if (!isalpha(tenHo[i]) && tenHo[i] != ' ') {
            return false;
        }
    }
    string res = "";
    string w;
    stringstream ss(tenHo);
    while (ss >> w) {
        res += toupper(w[0]);
        for (int i = 1; i < w.size(); i++) {
            res += tolower(w[i]);
        }
        res += " ";
    }
    res.pop_back();
    tenHo = res;
    return true;
}


// Ham chuan hoa gioi tinh (chuyen chu thuong ve chu hoa)
bool chuanHoaGioiTinh(string& phai) {
    if (phai == "nam" || phai == "Nam" || phai == "NAM") {
        phai = "Nam";
        return true;
    }
    else if (phai == "nu" || phai == "Nu" || phai == "NU") {
        phai = "Nu";
        return true;
    }
    return false;
}

// Ham in thong tin sinh vien
void inThongTinSV(SinhVien sv) {
    cout << "Ma SV: " << sv.MASV << " | Ho Ten: " << sv.HO << " " << sv.TEN
        << " | Gioi tinh: " << sv.PHAI << " | So DT: " << sv.SODT << "\n";
}

// Ham in danh sach sinh vien
// void inDanhSachSinhVien(List_LTC& dsltc) {
//     if (dsltc.First == NULL) {
//         cout << "Danh sach sinh vien trong lop rong";
//         return;
//     }
//     cout << "Danh sach sinh vien:\n";
//     PTRSV p = dsltc.First;
//     while (p != NULL) {
//         inThongTinSV(p->sv);
//         p = p->next;
//     }
// }

void drawListBoxDSSVDK(int x, int y, int w, int h, List_LTC& dsltc, int soTrang, int chonHang, int soDongMoiTrang, const string tieuDe[], int ntieuDe, int index, int khoangCachMoiCot[], int& viTri) {
    SetColor(2);
    gotoXY(x, y);
    printf("%-*s", khoangCachMoiCot[0], "STT");
    for (int i = 0; i < ntieuDe; i++) {
        printf("%-*s", khoangCachMoiCot[i + 1], tieuDe[i].c_str());
    }
    SetColor(7);
    cout << endl;
    int start = soTrang * soDongMoiTrang;
    int end = min(start + soDongMoiTrang, dsltc.n);
    for (int i = start; i < end; i++) {
        gotoXY(x, y + 1 + (i - start));
        if (i == chonHang) {
            viTri = index;
            textcolor(200);
            SetColor(0);
        }
        printf("%-*d", khoangCachMoiCot[0], index + 1);
        printf("%-*d", khoangCachMoiCot[1], dsltc.nodes[i]->MALOPTC);
        printf("%-*s", khoangCachMoiCot[2], dsltc.nodes[i]->MAMH.c_str());
        printf("%-*s", khoangCachMoiCot[3], dsltc.nodes[i]->NienKhoa.c_str());
        printf("%-*d", khoangCachMoiCot[4], dsltc.nodes[i]->Hocky);
        printf("%-*d", khoangCachMoiCot[5], dsltc.nodes[i]->Nhom);
        printf("%-*d", khoangCachMoiCot[6], dsltc.nodes[i]->sosvmin);
        printf("%-*d", khoangCachMoiCot[7], dsltc.nodes[i]->sosvmax);
        printf("%-*d", khoangCachMoiCot[8], DemSoSinhVien(dsltc.nodes[i]->dssvdk));
        index++;
        textcolor(7);
        SetColor(7);
    }
}
int listBoxDSSVDK(List_LTC& dsltc, const string tieuDe[], int ntieuDe) {
    int khoangCachMoiCot[] = { wLB * 0.07, wLB * 0.15, wLB * 0.15, wLB * 0.15, wLB * 0.15, wLB * 0.1, wLB * 0.1, wLB * 0.1,wLB * 0.1 };
    int soDuLieu = dsltc.n;
    int soTrang = 0;
    int chonHang = 0;
    int soDongMoiTrang = 20; 
    int viTri;
    ShowCur(false);
    int index = 1;
    while (true) {
        drawListBoxLTC(xLB, yLB, wLB, hLB, dsltc, soTrang, chonHang, soDongMoiTrang, tieuDe, ntieuDe, index, khoangCachMoiCot, viTri);
        int key = _getch();
        if (key == KEY_UP) {
            if (chonHang > 0) {
                chonHang--;
                if (chonHang <= soTrang * soDongMoiTrang) {
                    soTrang--;
                }
            }
        }
        else if (key == KEY_DOWN) {
            if ( chonHang < soDuLieu-1) {
                chonHang++;
                if (chonHang > (soTrang + 1) * soDongMoiTrang) {
                    xoa_noi_dung_khung();
                    soTrang++;
                }
            }
        }
        else if (key == KEY_ENTER ) {
            ShowCursor();
            return viTri;
        }
        else if (key == KEY_ESC) {
            ShowCur(true);
            return -1;
        }
    }
}


void huyLTC(List_LTC& dsltc) {
    system("cls");
    cout << DemSoSinhVien(dsltc.nodes[1]->dssvdk);
    system("pause");
    // if (dsltc.n == 0) {
    //     cout << "Danh sach lop tin chi rong!\n";
    //     system("cls");
    //     return;
    // }
    // bool ok = 1;
    // LopTinChi* LTC_tmp;
    // SetColor(7);
    // string tieuDe[] = { "MaLopTC", "MaMH", "NienKhoa", "HocKy", "Nhom", "SVMIN", "SVMAX","SoSVDK" };
    // int maLop;
    // while (true) {
    //     maLop = listBoxDSSVDK(dsltc, tieuDe, 8);
    // }
    // for (int i = 1; i <= dsltc.n; i++) {
    //     LTC_tmp = dsltc.nodes[i];
    //     int So_SV_DK = DemSoSinhVien(LTC_tmp->dssvdk);
    //     if (So_SV_DK < LTC_tmp->sosvmin && LTC_tmp->huylop == false && LTC_tmp->dssvdk != NULL) {
    //         if (ok == 1) {
    //             cout << "----DANH SACH LOP TIN CHI DU DIEU KIEN DE HUY----\n";
    //             cout << "Ma LTC\tMa MH\tNien Khoa\tHoc Ky\tNhom\tSo SV Min\tSo SV Max\tSo SV Da DK\n";
    //             ok = 0;
    //         }
    //         cout << LTC_tmp->MALOPTC << "\t" << LTC_tmp->MAMH << "\t" << LTC_tmp->NienKhoa
    //             << "\t" << LTC_tmp->Hocky << "\t" << LTC_tmp->Nhom << "\t" << LTC_tmp->sosvmin
    //             << "\t\t" << LTC_tmp->sosvmax << "\t\t" << So_SV_DK << endl;
    //     }
    // }
    // if (ok == 1) {
    //     cout << "Khong co lop tin chi nao du dieu kien de huy!\n";
    //     system("cls");
    //     return;
    // }
    // string input;
    // do {
    //     do {
    //         cout << "Nhap ma lop tin chi muon huy(An phim '|' de thoat): ";
    //         getline(cin, input);
    //         if (input == "|") {
    //             cout << "Da thoat!\n";
    //             system("cls");
    //             return;
    //         }
    //         if (kiemTraChuoiSo(input)) break;
    //         else cout << "Ma lop tin chi la so nguyen duong!\n";
    //     } while (1);
    //     for (int i = 1; i <= dsltc.n; i++) {
    //         LTC_tmp = dsltc.nodes[i];
    //         if (LTC_tmp->MALOPTC == stoi(input) && DemSoSinhVien(LTC_tmp->dssvdk) < LTC_tmp->sosvmin && LTC_tmp->huylop == false) {
    //             do {
    //                 cout << "Ban co that su muon huy lop tin chi nay khong?(y/n): ";
    //                 getline(cin, input);
    //                 if (input == "Y" || input == "y") {
    //                     dsltc.nodes[i]->huylop = true;
    //                     cout << "Da huy lop tin chi nay!\n";
    //                     system("cls");
    //                     return;
    //                 }
    //                 else if (input == "n" || input == "N") {
    //                     cout << "Da huy thao tac huy lop tin chi nay!\n";
    //                     system("cls");
    //                     return;
    //                 }
    //                 else cout << "Vui long nhap lua chon hop le!\n";
    //             } while (1);
    //         }
    //     }
    //     cout << "Lua chon cua ban khong hop le!\n";
    // } while (1);
    system("cls");
}

// Hien thi bang lop tin chi hien co
void hienThiDanhSachLopTinChi(List_LTC& dsltc) {
    SetColor(9);
    int viTri;
    string tieuDe[] = { "MaLopTC", "MaMH", "NienKhoa", "HocKy", "Nhom", "SVMIN", "SVMAX" };
    int* x = new int;
    *x = listBoxLTC(dsltc, tieuDe, 7, 1);
    delete x;
    xoa_noi_dung_khung();
}

void MoLopTinChi(List_LTC& dsltc, treeMH& root) {
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "       LOP TIN CHI");
        boxVuong(35, 3, 80, 22, 15);
        string text[] = { "Them lop tin chi", "Xoa lop tin chi", "Sua lop tin chi", "In danh sach LTC", "Huy lop tin chi ", "Thoat" };
        box_huong_dan_menu();
        int luachon = thanhSangListBox(xL, yL, wL, hL, 11, 14, text, 6);
        switch (luachon) {
        case 0:
            themLopTinChi(dsltc, root);
            break;
        case 1:
            Sua_xoaLopTinChi(dsltc, root, 0);
            break;
        case 2:
            Sua_xoaLopTinChi(dsltc, root, 1);
            break;
        case 3:
            hienThiDanhSachLopTinChi(dsltc);
            break;
        case 4:
            huyLTC(dsltc);
            break;
        case 5:
            if (xacNhanThoat()) {
                system("cls");
                return;
            }
            break;
        }
    }
}

SinhVien* searchSV(LopSV& temparary, string& maSV) {
    PTRSV p = temparary.First;
    while (p != NULL) {
        if (p->sv.MASV == maSV)
        {
            return &p->sv;
        }
        p = p->next;
    }
    return NULL;
}

void timLopSV(DS_LOPSV& dsLopSV, string& maSV) {
    for (int i = 0; i < dsLopSV.n; ++i) {
        SinhVien* a = searchSV(dsLopSV.nodes[i], maSV);
        if (a != NULL) {
            cout << a->MASV << "\t" << a->HO << "\t" << a->TEN
                << "\t" << a->PHAI << "\t" << a->SODT << endl;
            return;
        }
    }
    return;
}

void InDSSV_LTC(LopTinChi* LTC, DS_LOPSV& dsLop) {
    PTRDK DSSV = LTC->dssvdk;
    system("cls");
    while (DSSV != NULL) {
        timLopSV(dsLop, DSSV->dk.MASV);
        DSSV = DSSV->next;
    }
    cout << endl;
    SetColor(4);
    cout << "AN PHIM ESC DE THOAT";
    SetColor(7);
    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) {  // Nh?n ESC d? tho?t
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}

void xuat_file_sv_dk_ltc(LopTinChi* LTC, DS_LOPSV& dsLop, string NienKhoa, int HocKy, int Nhom, string MaMonHoc) {
    ofstream infile;
    infile.open("C:\\Users\\admin\\Downloads\\C++\\ds_sv_dk_ltc.txt", ios_base::out);
    gotoXY(10, 0);
    cout << "DANH SACH SINH VIEN DA DANG KY LOP TIN CHI THEO CAC THAM SO";
    gotoXY(20, 2); infile << "Nien khoa: " << NienKhoa;
    gotoXY(50, 2); infile << "Hoc ky: " << HocKy;
    gotoXY(70, 2); infile << "Nhom: " << Nhom;
    gotoXY(85, 2); infile << "Ma mon hoc: " << MaMonHoc << endl;
    gotoXY(10, 3); infile << "===================================================" << endl;
    PTRDK DSSV = LTC->dssvdk;
    while (DSSV != NULL) {
        for (int i = 0; i < dsLop.n; ++i) {
            SinhVien* a = searchSV(dsLop.nodes[i], DSSV->dk.MASV);
            if (a != NULL) {
                infile << a->MASV << " || " << a->HO << " || " << a->TEN
                    << " || " << a->PHAI << " || " << a->SODT << endl;
                break;
            }
        }
        DSSV = DSSV->next;
    }
    infile.close();
}

// H?m in danh s?ch sinh vi?n
void SVDK_LTC(DS_LOPSV& dsLop, List_LTC& dsltc, treeMH& root);
void hienThiDanhSachSV_LTC_TheoThamSo(List_LTC& dsltc, DS_LOPSV& dsLop, string MaMonHoc, string HocKy, string Nhom, string NienKhoa, treeMH& root) {
    cout << "Danh sach sinh vien da dang ky theo cac tham so:";
    cout << "Nien khoa: " << NienKhoa << " Hoc ky: " << HocKy << " Nhom: " << Nhom << "Ma mon hoc: " << MaMonHoc << endl;
    for (int i = 1; i <= dsltc.n; i++) {
        LopTinChi* LTC = dsltc.nodes[i];
        if ((NienKhoa == "--" || NienKhoa == LTC->NienKhoa)
            && (HocKy == "--" || stoi(HocKy) == LTC->Hocky)
            && (Nhom == "--" || stoi(Nhom) == LTC->Nhom)
            && (MaMonHoc == "--" || MaMonHoc == LTC->MAMH)
            ) {
            xuat_file_sv_dk_ltc(LTC, dsLop, NienKhoa, stoi(HocKy), stoi(Nhom), MaMonHoc);
            InDSSV_LTC(LTC, dsLop);
            SVDK_LTC(dsLop, dsltc, root);
            return;
        }
    }
}

void HienThi_in_sv_dk_ltc(string& nk, string& hk, string& nhom, string& ma, int viTriChon, int viTriChon_cu, string text[]) {
    for (int i = 0; i < 5; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (nk != "--") cout << nk;
                else cout << "--";
            }
            else if (i == 1) {
                if (hk != "--") cout << hk;
                else cout << "--";
            }
            else if (i == 2) {
                if (nhom != "--") cout << nhom;
                else cout << "--";
            }
            else if (i == 3) {
                if (ma != "--") cout << ma;
                else cout << "--";
            }
            SetColor(7);
        }
        else {
            SetColor(7);
            cout << text[i];
            if (i == 0) {
                if (nk != "--") cout << nk;
                else cout << "--";
            }
            else if (i == 1) {
                if (hk != "--") cout << hk;
                else cout << "--";
            }
            else if (i == 2) {
                if (nhom != "--") cout << nhom;
                else cout << "--";
            }
            else if (i == 3) {
                if (ma != "--") cout << ma;
                else cout << "--";
            }
        }
    }
}

void Nhap_nk_in_ds_svdk(string& nk, int viTriChon) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        cout << "NHAP NIEN KHOA: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (!kiemTraNienKhoa(input)) {
            gotoXY(40, 24);
            cout << "Nien khoa khong hop le!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                         ";
            continue;
        }
        nk = input;
        break;
    } while (1);
    HideCursor();
}

void Nhap_hk_in_ds_svdk(string& hk, int viTriChon) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        cout << "NHAP HOC KY: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (!kiemTraChuoiSo(input)) {
            gotoXY(40, 24);
            cout << "Hoc ky la so nguyen khong am!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                         ";
            continue;
        }
        hk = input;
        break;
    } while (1);
    HideCursor();
}

void Nhap_nhom_in_ds_svdk(string& nhom, int& viTriChon) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        cout << "NHAP NHOM: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (!kiemTraChuoiSo(input)) {
            gotoXY(40, 24);
            cout << "Nhom la so nguyen khong am!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                         ";
            continue;
        }
        nhom = input;
        break;
    } while (1);
    HideCursor();
}

void Nhap_mamh_in_ds_svdk(string& ma, int viTriChon, treeMH& root) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        cout << "NHAP MA MON HOC: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (input.size() > 10) {
            gotoXY(40, 24);
            cout << "Ma mon hoc khong duoc qua 10 ki tu!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                     ";
            continue;
        }
        if (!isDuplicateMH(root, input)) {
            gotoXY(40, 24);
            cout << "Ma mon hoc nay khong ton tai!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                         ";
            continue;
        }
        ma = input;
        break;
    } while (1);
    HideCursor();
}

void Indssvdkltc(List_LTC& dsltc, DS_LOPSV& dsLop, treeMH& root) {
    HideCursor();
    xoa_noi_dung_khung();
    gotoXY(55, 4);
    SetColor(9);
    cout << "IN DANH SACH SINH VIEN DANG KY LOP TIN CHI";
    SetColor(7);
    if (dsltc.n == 0) {
        gotoXY(50, 6);
        SetColor(4);
        cout << "CHUA CO LOP TIN CHI NAO DUOC MO DE IN";
        gotoXY(40, 9);
        SetColor(2);
        cout << "An phim ESC de thoat!";
        SetColor(7);
        while (1) {
            if (_kbhit()) {
                char key = getch();
                if (key == 27) {  // Nh?n ESC d? tho?t
                    xoa_noi_dung_khung();
                    ShowCursor();
                    return;
                }
            }
        }
    }
    string nk = "--", ma = "--", hk = "--", nhom = "--";
    int viTriChon = 6;
    string text[5] = { "NHAP NIEN KHOA: ", "NHAP HOC KY: ",
                 "NHAP NHOM: ",
                "NHAP MA MON HOC: ", "          ===IN DANH SACH===" };
    for (int i = 0; i < 5; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (nk != "--") cout << nk;
                else cout << "--";
            }
            else if (i == 1) {
                if (hk != "--") cout << hk;
                else cout << "--";
            }
            else if (i == 2) {
                if (nhom != "--") cout << nhom;
                else cout << "--";
            }
            else if (i == 3) {
                if (ma != "--") cout << ma;
                else cout << "--";
            }
            SetColor(7);
        }
        else {
            cout << text[i];
            if (i == 0) {
                if (nk != "--") cout << nk;
                else cout << "--";
            }
            else if (i == 1) {
                if (hk != "--") cout << hk;
                else cout << "--";
            }
            else if (i == 2) {
                if (nhom != "--") cout << nhom;
                else cout << "--";
            }
            else if (i == 3) {
                if (ma != "--") cout << ma;
                else cout << "--";
            }
        }
    }
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    while (true) {
        if (_kbhit()) {
            gotoXY(30, 26);
            SetColor(12);
            cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
            SetColor(7);
            char key = _getch();  // L?y k? t? ngu?i d?ng nh?n
            if (key == 72) {  // Mui t?n l?n
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui t?n xu?ng
                if (viTriChon < 14) {
                    viTriChon += 2;
                    HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
                if (viTriChon == 14) {
                    hienThiDanhSachSV_LTC_TheoThamSo(dsltc, dsLop, ma, hk, nhom, nk, root);
                }
                else {
                    int ok = 14;
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 6) Nhap_nk_in_ds_svdk(nk, viTriChon);
                    else if (viTriChon == 8) Nhap_hk_in_ds_svdk(hk, viTriChon);
                    else if (viTriChon == 10) Nhap_nhom_in_ds_svdk(nhom, viTriChon);
                    else if (viTriChon == 12) Nhap_mamh_in_ds_svdk(ma, viTriChon, root);
                    if (nk == "--") ok = 6;
                    else if (hk == "--") ok = 8;
                    else if (nhom == "--") ok = 10;
                    else if (ma == "--") ok = 12;
                    HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, ok, viTriChon, text);
                    viTriChon = ok;
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                xoa_noi_dung_khung();
                ShowCursor();
                return;
            }
        }
    }
}

void drawListBoxLSV(int x, int y, int w, int h, DS_LOPSV& dssv, int soDuLieu, int soTrang, int chonHang, int soDongMoiTrang, const string tieuDe[], int ntieuDe, string& maLop) {
    if (soDuLieu == 0) {
        gotoXY(x, y + 2);
        cout << "Danh sach rong!";
        maLop = "-1";
        return;
    }
    int khoangCachMoiCot[] = { w * 0.2, w * 0.4, w * 0.4 };
    gotoXY(x, y);
    printf("%-*s", khoangCachMoiCot[0], "STT");
    for (int i = 0; i < ntieuDe; i++) {
        printf("%-*s", khoangCachMoiCot[i + 1], tieuDe[i].c_str());
    }
    cout << endl;
    int start = soTrang * soDongMoiTrang;
    int end = min(start + soDongMoiTrang, soDuLieu);
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    for (int i = start; i < end; i++) {
        gotoXY(x, y + 1 + (i - start));
        if (i == chonHang) {
            textcolor(225);
        }
        printf("%-*d", khoangCachMoiCot[0], i + 1);
        printf("%-*s", khoangCachMoiCot[1], dssv.nodes[i].MALOP.c_str());
        printf("%-*s", khoangCachMoiCot[2], dssv.nodes[i].TENLOP.c_str());
        if (i == chonHang) {
            textcolor(7);
        }
        cout << endl;
    }
    if (chonHang >= start && chonHang < end) {
        maLop = dssv.nodes[chonHang].MALOP;
    }
    else {
        maLop = "-1";
    }
}

string listBoxLSV(DS_LOPSV& dssv, int soDongMoiTrang, const string tieuDe[], int ntieuDe) {
    int totalRows = dssv.n;
    if (totalRows == 0) {
        return "-1";
    }

    int soTrang = 0;
    int chonHang = 0;
    ShowCur(false);
    string maLop = "-1";

    while (true) {
        drawListBoxLSV(37, 4, 78, 22, dssv, totalRows, soTrang, chonHang, soDongMoiTrang, tieuDe, ntieuDe, maLop);
        if (_kbhit()) {
            int key = _getch();
            if (key == KEY_UP) {
                if (chonHang > 0) {
                    chonHang--;
                    if (chonHang < soTrang * soDongMoiTrang) {
                        soTrang--;
                    }
                }
            }
            else if (key == KEY_DOWN) {
                if (chonHang < totalRows - 1) {
                    chonHang++;
                    if (chonHang >= (soTrang + 1) * soDongMoiTrang) {
                        xoa_noi_dung_khung();
                        soTrang++;
                    }
                }
            }
            else if (key == KEY_ENTER) {
                ShowCur(false);
                return maLop;
            }
            else if (key == KEY_ESC) {
                ShowCur(true);
                return "-1";
            }
        }
    }
}

string listBoxLSVforIn(DS_LOPSV& dssv, int soDongMoiTrang, const string tieuDe[], int ntieuDe) {
    int totalRows = dssv.n;
    if (totalRows == 0) {
        return "-1";
    }
    int soTrang = 0;
    int chonHang = 0;
    ShowCur(false);
    string maSV = "-1";
    while (true) {
        drawListBoxLSV(37, 4, 78, 22, dssv, totalRows, soTrang, chonHang, soDongMoiTrang, tieuDe, ntieuDe, maSV);
        if (_kbhit()) {
            int key = _getch();
            if (key == KEY_UP) {
                if (chonHang > 0) {
                    chonHang--;
                    if (chonHang < soTrang * soDongMoiTrang) {
                        soTrang--;
                    }
                }
            }
            else if (key == KEY_DOWN) {
                if (chonHang < totalRows - 1) {
                    chonHang++;
                    if (chonHang >= (soTrang + 1) * soDongMoiTrang) {
                        xoa_noi_dung_khung();
                        soTrang++;
                    }
                }
            }
            else if (key == KEY_ESC) {
                ShowCur(true);
                return "-1";
            }
        }
    }
}

void inDanhSachLop(DS_LOPSV& dsLop) {
    if (dsLop.n == 0) {
        cout << "Danh sach lop trong";
        return;
    }
    int soTieuDe = 2;
    string text[] = { "Ma Lop","Ten Lop" };
    string maLop = listBoxLSVforIn(dsLop, 20, text, soTieuDe);
    while (true) {
        if (maLop == "-1") {
            xoa_noi_dung_khung();
            return;
        }
    }
}

// H?m in danh s?ch sinh vi?n
void inDanhSachSinhVien(LopSV& lop) {
    if (lop.First == NULL) {
        cout << "Danh sach sinh vien trong lop rong.\n";
        return;
    }
    cout << "Danh sach sinh vien:\n";
    PTRSV p = lop.First;
    while (p != NULL) {
        inThongTinSV(p->sv);
        p = p->next;
    }
}

// H?m ki?m tra m? sinh vi?n d? t?n t?i
bool kiemTraMaSVTonTai(LopSV& lop, string MASV) {
    PTRSV p = lop.First;
    while (p != NULL) {
        if (p->sv.MASV == MASV) {
            return true;  // T?n t?i sinh vi?n v?i m? n?y
        }
        p = p->next;
    }
    return false;
}

void HienThi_Them_sv(SinhVien& sv, int viTriChon, int viTriChon_cu, string text[]) {
    for (int i = 0; i < 6; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (sv.MASV != "--") cout << sv.MASV;
                else cout << "--";
            }
            else if (i == 1) {
                if (sv.HO != "--") cout << sv.HO;
                else cout << "--";
            }
            else if (i == 2) {
                if (sv.TEN != "--") cout << sv.TEN;
                else cout << "--";
            }
            else if (i == 3) {
                if (sv.PHAI != "--") cout << sv.PHAI;
                else cout << "--";
            }
            else if (i == 4) {
                if (sv.SODT != "--") cout << sv.SODT;
                else cout << "--";
            }
            SetColor(7);
        }
        else if (viTriChon_cu == 6 + i * 2) {
            SetColor(7);
            cout << text[i];
            if (i == 0) {
                if (sv.MASV != "--") cout << sv.MASV;
                else cout << "--";
            }
            else if (i == 1) {
                if (sv.HO != "--") cout << sv.HO;
                else cout << "--";
            }
            else if (i == 2) {
                if (sv.TEN != "--") cout << sv.TEN;
                else cout << "--";
            }
            else if (i == 3) {
                if (sv.PHAI != "--") cout << sv.PHAI;
                else cout << "--";
            }
            else if (i == 4) {
                if (sv.SODT != "--") cout << sv.SODT;
                else cout << "--";
            }
        }
    }
}

void Nhap_ma_sv_sv(LopSV& lop, int viTriChon, SinhVien& sv) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        cout << "NHAP MA SINH VIEN: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (input.size() > 15) {
            gotoXY(40, 24);
            cout << "Ma sinh vien khong duoc qua 15 ki tu!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                         ";
            continue;
        }
        if (kiemTraMaSVTonTai(lop, input)) {
            gotoXY(40, 24);
            cout << "Ma sinh vien " << input << " da ton tai.\n";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                         ";
            continue;
        }
        sv.MASV = input;
        HideCursor();
        break;
    } while (1);
    HideCursor();
}

void Nhap_ho_sv_sv(LopSV& lop, int viTriChon, SinhVien& sv) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        cout << "NHAP HO SINH VIEN: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (!kiemTraTenHo(input)) {
            gotoXY(40, 24);
            cout << "Loi: Ho chi duoc chua chu cai. Vui long nhap lai!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                                    ";
            continue;
        }
        sv.HO = input;
        break;
    } while (1);
    HideCursor();
    SetColor(7);
}

void Nhap_ten_sv_sv(LopSV& lop, int viTriChon, SinhVien& sv) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        cout << "NHAP TEN SINH VIEN: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (!kiemTraTenHo(input)) {
            gotoXY(40, 24);
            cout << "Loi: Ten chi duoc chua chu cai. Vui long nhap lai!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                                    ";
            continue;
        }
        sv.TEN = input;
        break;
    } while (1);
    HideCursor();
    SetColor(7);
}

void Nhap_phai_sv_sv(LopSV& lop, int viTriChon, SinhVien& sv) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                             ";
        gotoXY(40, viTriChon);
        cout << "NHAP GIOI TINH SINH VIEN: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (!chuanHoaGioiTinh(input)) {
            gotoXY(40, 24);
            cout << "Nhap gioi tinh chua dung. Vui long nhap lai!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                                    ";
            continue;
        }
        sv.PHAI = input;
        break;
    } while (1);
    HideCursor();
    SetColor(7);
}

void Nhap_sodt_sv_sv(LopSV& lop, int viTriChon, SinhVien& sv) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                           ";
        gotoXY(40, viTriChon);
        cout << "NHAP SO DIEN THOAI SINH VIEN: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (!kiemTraSoDienThoai(input)) {
            gotoXY(40, 24);
            cout << "So dien thoai phai co 10 so. Vui long nhap lai!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                                    ";
            continue;
        }
        sv.SODT = input;
        break;
    } while (1);
    HideCursor();
    SetColor(7);
}

void tao_sv(LopSV& lop, SinhVien sv) {
    PTRSV newSV = new nodeSV;
    newSV->sv = sv;
    newSV->next = NULL;
    if (lop.First == NULL) {
        lop.First = newSV;
    }
    else {
        PTRSV tmp = lop.First;
        PTRSV prev_tmp = NULL;
        while (tmp != NULL) {
            if (tmp->sv.TEN < sv.TEN) {
                prev_tmp = tmp;
                tmp = tmp->next;
            }
            else if (tmp->sv.TEN == sv.TEN) {
                if (tmp->sv.HO < sv.HO) {
                    prev_tmp = tmp;
                    tmp = tmp->next;
                }
            }
            else break;
        }
        if (prev_tmp != NULL) {
            newSV->next = tmp;
            prev_tmp->next = newSV;
        }
        else {
            newSV->next = lop.First;
            lop.First = newSV;
        }
    }
}

// Ham them sinh vien vao lop
void themSinhVien(DS_LOPSV& dsLop,LopSV& lop) {
    HideCursor();
    xoa_noi_dung_khung();
    gotoXY(65, 4);
    SetColor(9);
    cout << "THEM SINH VIEN MOI VAO LOP";
    SetColor(7);
    SinhVien sv;
    sv.MASV = "--"; sv.HO = "--"; sv.TEN = "--"; sv.PHAI = "--"; sv.SODT = "--";
    int viTriChon = 6;
    string text[6] = { "NHAP MA SINH VIEN: ", "NHAP HO SINH VIEN: ",
             "NHAP TEN SINH VIEN: ", "NHAP GIOI TINH SINH VIEN: ",
              "NHAP SO DIEN THOAI SINH VIEN: ", "          ===CHON LUU===" };
    for (int i = 0; i < 6; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (sv.MASV != "--") cout << sv.MASV;
                else cout << "--";
            }
            else if (i == 1) {
                if (sv.HO != "--") cout << sv.HO;
                else cout << "--";
            }
            else if (i == 2) {
                if (sv.TEN != "--") cout << sv.TEN;
                else cout << "--";
            }
            else if (i == 3) {
                if (sv.PHAI != "--") cout << sv.PHAI;
                else cout << "--";
            }
            else if (i == 4) {
                if (sv.SODT != "--") cout << sv.SODT;
                else cout << "--";
            }
            SetColor(7);
        }
        else {
            cout << text[i];
            if (i == 0) {
                if (sv.MASV != "--") cout << sv.MASV;
                else cout << "--";
            }
            else if (i == 1) {
                if (sv.HO != "--") cout << sv.HO;
                else cout << "--";
            }
            else if (i == 2) {
                if (sv.TEN != "--") cout << sv.TEN;
                else cout << "--";
            }
            else if (i == 3) {
                if (sv.PHAI != "--") cout << sv.PHAI;
                else cout << "--";
            }
            else if (i == 4) {
                if (sv.SODT != "--") cout << sv.SODT;
                else cout << "--";
            }
        }
    }
    while (true) {
        SetColor(12);
        gotoXY(30, 26);
        cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
        if (_kbhit()) {
            char key = _getch();  // L?y k? t? ngu?i d?ng nh?n
            if (key == KEY_UP) {  // Mui t?n l?n
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_sv(sv, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == KEY_DOWN) {  // Mui t?n xu?ng
                if (viTriChon < 16) {
                    viTriChon += 2;
                    HienThi_Them_sv(sv, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == KEY_ENTER) {  // Nhan Enter de nhap mon
                if (viTriChon == 16) {
                    int ok = -1;
                    if (sv.MASV == "--") ok = 6;
                    else if (sv.HO == "--") ok = 8;
                    else if (sv.TEN == "--") ok = 10;
                    else if (sv.PHAI == "--") ok = 12;
                    else if (sv.SODT == "--") ok = 14;
                    if (ok == -1) {
                        tao_sv(lop, sv);
                        xuat_file_DSSV(dsLop);
                        gotoXY(40, 24);
                        SetColor(10);
                        cout << "Them sinh vien moi thanh cong!";
                        SetColor(7);
                        for (int i = 1; i <= 370000000; i++);
                        gotoXY(40, 24);
                        cout << "                                                      ";
                        themSinhVien(dsLop,lop);
                        return;
                    }
                    else {
                        SetColor(4);
                        gotoXY(62, 24);
                        cout << "    Nhap thong tin chua day du!";
                        for (int i = 0; i <= 300000000; i++);
                        gotoXY(62, 24); cout << "                                      ";
                        SetColor(7);
                        viTriChon = ok;
                        HienThi_Them_sv(sv, ok, 16, text);
                    }
                }
                else {
                    int ok = -1;
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 6) Nhap_ma_sv_sv(lop, viTriChon, sv);
                    else if (viTriChon == 8) Nhap_ho_sv_sv(lop, viTriChon, sv);
                    else if (viTriChon == 10) Nhap_ten_sv_sv(lop, viTriChon, sv);
                    else if (viTriChon == 12) Nhap_phai_sv_sv(lop, viTriChon, sv);
                    else if (viTriChon == 14) Nhap_sodt_sv_sv(lop, viTriChon, sv);
                    if (sv.MASV == "--") ok = 6;
                    else if (sv.HO == "--") ok = 8;
                    else if (sv.TEN == "--") ok = 10;
                    else if (sv.PHAI == "--") ok = 12;
                    else if (sv.SODT == "--") ok = 14;
                    if (ok != -1) {
                        HienThi_Them_sv(sv, ok, viTriChon, text);
                        viTriChon = ok;
                    }
                    else {
                        ok = viTriChon;
                        viTriChon = 16;
                        HienThi_Them_sv(sv, viTriChon, ok, text);
                    }
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}

void drawListBoxSV(int x, int y, int w, int h, PTRSV& sv, int soDuLieu, int soTrang, int chonHang, int soDongMoiTrang, const string tieuDe[], int ntieuDe, string& maSV) {
    if (soDuLieu == 0) {
        gotoXY(x, y + 2);
        cout << "Danh sach rong!";
        maSV = "-1";
        return;
    }
    PTRSV head = sv;
    int khoangCachMoiCot[] = { w * 0.1, w * 0.2,w * 0.35,w * 0.1,w * 0.22 };
    gotoXY(x, y);
    printf("%-*s", khoangCachMoiCot[0], "STT");
    for (int i = 0; i < ntieuDe; i++) {
        printf("%-*s", khoangCachMoiCot[i], tieuDe[i].c_str());
    }
    cout << endl;
    int start = soTrang * soDongMoiTrang;
    int end = min(start + soDongMoiTrang, soDuLieu);
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    for (int i = start; i < end; i++) {
        gotoXY(x, y + 1 + (i - start));
        if (i == chonHang) {
            textcolor(225);
        }
        printf("%-*d", khoangCachMoiCot[0], i + 1);
        printf("%-*s", khoangCachMoiCot[1], head->sv.MASV.c_str());
        printf("%-*s", khoangCachMoiCot[2], (head->sv.HO + " " + head->sv.TEN).c_str());
        printf("%-*s", khoangCachMoiCot[3], head->sv.PHAI.c_str());
        printf("    %-*s", khoangCachMoiCot[4], head->sv.SODT.c_str());
        if (i == chonHang) {
            textcolor(7);
        }
        cout << endl;
        head = head->next;
    }
    head = sv;
    for (int i = 0; i < chonHang; i++) {
        if (head == NULL) {
            maSV = "-1";
            return;
        }
        head = head->next;
    }
    if (head != NULL) {
        maSV = head->sv.MASV;
    }
    else {
        maSV = "-1";
    }
}

string listBoxSV(PTRSV sv, int soDuLieu, int soDongMoiTrang, const string tieuDe[], int ntieuDe) {
    if (soDuLieu == 0) {
        return "-1";
    }
    xoa_noi_dung_khung2();
    int soTrang = 0;
    int chonHang = 0;
    HideCursor();
    string maSV = "-1";
    while (true) {
        drawListBoxSV(37, 4, 78, 22, sv, soDuLieu, soTrang, chonHang, soDongMoiTrang, tieuDe, ntieuDe, maSV);
        if (_kbhit()) {
            int key = _getch();
            if (key == KEY_UP) {
                if (chonHang > 0) {
                    chonHang--;
                    if (chonHang < soTrang * soDongMoiTrang) {
                        xoa_noi_dung_khung();
                        soTrang--;
                    }
                }
            }
            else if (key == KEY_DOWN) {
                if (chonHang < soDuLieu - 1) {
                    chonHang++;
                    if (chonHang >= (soTrang + 1) * soDongMoiTrang) {
                        xoa_noi_dung_khung();
                        soTrang++;
                    }
                }
            }
            else if (key == KEY_ENTER) {
                return maSV;
            }
            else if (key == KEY_ESC) {
                return "-1";
            }
        }
    }
}
string listBoxSVforIn(PTRSV sv, int soDuLieu, int soDongMoiTrang, const string tieuDe[], int ntieuDe) {
    if (soDuLieu == 0) {
        return "-1";
    }
    int soTrang = 0;
    int chonHang = 0;
    HideCursor();
    string maSV = "-1";
    while (true) {
        drawListBoxSV(37, 4, 78, 22, sv, soDuLieu, soTrang, chonHang, soDongMoiTrang, tieuDe, ntieuDe, maSV);
        if (_kbhit()) {
            int key = _getch();
            if (key == KEY_UP) {
                if (chonHang > 0) {
                    chonHang--;
                    if (chonHang < soTrang * soDongMoiTrang) {
                        xoa_noi_dung_khung();
                        soTrang--;
                    }
                }
            }
            else if (key == KEY_DOWN) {
                if (chonHang < soDuLieu - 1) {
                    chonHang++;
                    if (chonHang >= (soTrang + 1) * soDongMoiTrang) {
                       xoa_noi_dung_khung();
                        soTrang++;
                        
                    }
                }
            }
            else if (key == KEY_ESC) return "-1";
        }
    }
}

void deleteSV(LopSV& lop, string maSV) {
    PTRSV prev = NULL, curr = lop.First;
    // Tim sinh vien can x?a
    while (curr != NULL && curr->sv.MASV != maSV) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return;
    }
    if (prev == NULL) {
        lop.First = curr->next;
    }
    else {
        prev->next = curr->next;
    }
    delete curr;
}

// Ham xoa sinh vien khoi lop (in danh sach truoc khi nhap ma)
void xoaSinhVien(DS_LOPSV& dsLop,LopSV& lop) {
    if (lop.First == NULL) {
        cout << "Danh sach sinh vien rong, khong co gi de xoa";
        return;
    }
    int soDuLieu = countSVtrongLop(lop.First);
    string tieuDe[] = { "MASV","        HO va TEN","                  PHAI","  SODT" };
    int nTieuDe = 4;
    string select;
    /*deleteSV(lop, select);*/
    while (true) {
        select = listBoxSV(lop.First, soDuLieu, 20, tieuDe, nTieuDe);
        if (select == "-1") {
            xoa_noi_dung_khung();
            break;
        }
        else {
            int viTri;
            bool xacNhan;
            boxXacNhan(40, 10, 30, 5, "Xac nhan xoa SV?", "Co", "Khong", xacNhan);
            if (xacNhan) {
                viTri = 0;
                PTRSV p = lop.First;
                while (p != NULL && p->sv.MASV != select) {
                    p = p->next;
                    viTri++;
                }
                if (xacNhan) {
                    xoa_noi_dung_khung();
                    deleteSV(lop, select);
                    soDuLieu--;
                    xuat_file_DSSV(dsLop);
                }
                else {
                    return;
                }
            }
        }
    }
}

void sua_SV(LopSV& lop, string maSV) {
    xoa_noi_dung_khung();
    if (lop.First == NULL) {
        gotoXY(35, 10);
        cout << "Danh sach sinh vien rong, khong co gi de sua";
        return;
    }
    PTRSV p = lop.First;
    while (p != NULL && p->sv.MASV != maSV) {
        p = p->next;
    }
    SinhVien* sv = &p->sv;
    int viTriChon = 6;
    SetColor(2);
    gotoXY(60, 4);
    cout << "SUA THONG TIN SINH VIEN ";
    string text[6] = { "NHAP MA SINH VIEN: ","NHAP HO SINH VIEN: ",
     "NHAP TEN SINH VIEN: ","NHAP GIOI TINH SINH VIEN: ",
    "NHAP SO DIEN THOAI SINH VIEN: ", "        CAP NHAT      " };
    for (int i = 0; i < 6; i++) {
        gotoXY(40, 6 + i * 2);
        SetColor(7);
        if (viTriChon == 6 + i * 2) SetColor(4);
        cout << text[i];
        if (i == 0) cout << sv->MASV;
        else if (i == 1) cout << sv->HO;
        else if (i == 2) cout << sv->TEN;
        else if (i == 3) cout << sv->PHAI;
        else if (i == 4) cout << sv->SODT;
        SetColor(7);
    }
    HideCursor();
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    while (true) {
        if (_kbhit()) {
            gotoXY(30, 26);
            SetColor(12);
            cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
            SetColor(7);
            char key = _getch();
            if (key == 72) {  // Mui t?n l?n
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_sv(*sv, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui t?n xu?ng
                if (viTriChon < 16) {
                    viTriChon += 2;
                    HienThi_Them_sv(*sv, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
                if (viTriChon == 16) {
                    gotoXY(40, 24);
                    SetColor(10);
                    cout << "Cap nhat thong tin sinh vien thanh cong!";
                    SetColor(7);
                    for (int i = 1; i <= 370000000; i++);
                    gotoXY(40, 24);
                    cout << "                                                         ";
                    return;
                }
                else {
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 6) {
                        Nhap_ma_sv_sv(lop, viTriChon, *sv);
                    }
                    else if (viTriChon == 8) {
                        Nhap_ho_sv_sv(lop, viTriChon, *sv);
                    }
                    else if (viTriChon == 10) {
                        Nhap_ten_sv_sv(lop, viTriChon, *sv);
                    }

                    else if (viTriChon == 12) {
                        Nhap_phai_sv_sv(lop, viTriChon, *sv);
                    }
                    else if (viTriChon == 14) {
                        Nhap_sodt_sv_sv(lop, viTriChon, *sv);
                    }

                    else if (viTriChon == 16) {
                        gotoXY(40, 24);
                        SetColor(10);
                        cout << "Cap nhat thanh cong!";
                    }
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                xoa_noi_dung_khung();
                HideCursor();
                return;
            }
        }
    }
}

// Ham hieu chinh thong tin sinh vien 
void SuaThongTinSV(DS_LOPSV& dsLop,LopSV& lop) {
    int soDuLieu = countSVtrongLop(lop.First);
    string tieuDe[] = { "MASV","        HO va TEN","                  PHAI","  SODT" };
    int nTieuDe = 4;
    string select;
    // hieuChinhSinhVien(lop,select);
    while (true) {
        select = listBoxSV(lop.First, soDuLieu, 20, tieuDe, nTieuDe);
        if (select == "-1") {
            xoa_noi_dung_khung();
            break;
        }
        else {
            sua_SV(lop, select);
            soDuLieu--;
            xuat_file_DSSV(dsLop);
            xoa_noi_dung_khung();
        }
    }
}

int Tim_viTri_Lop(DS_LOPSV& dsLop, string MALOP) {
    int viTri = -1;
    for (int i = 0; i < dsLop.n; i++) {
        if (dsLop.nodes[i].MALOP == MALOP) {
            viTri = i;
            break;
        }
    }
    return viTri;
}

void xuat_file_ds_sv_1_lop(LopSV lop) {
    PTRSV head = lop.First;
    int stt = 1;
    ofstream infile;
    infile.open("C:\\Users\\admin\\Downloads\\C++\\ds_sv_1_lop.txt", ios_base::out);
    infile << "     =====DANH SACH SINH VIEN=====" << endl;
    infile << "=====================================" << endl;
    infile << "STT\tMA SINH VIEN\tHO VA TEN\t\tPHAI\tSO DIEN THOAI" << endl;
    while (head != NULL) {
        infile << stt++ << "\t" << head->sv.MASV;
        for (int j = 1; j <= 16 - (head->sv.MASV).size(); j++) infile << " ";
        infile << head->sv.HO << " " << head->sv.TEN;
        for (int j = 1; j <= 24 - (head->sv.HO).size() - (head->sv.TEN).size(); j++) infile << " ";
        infile << head->sv.PHAI << "\t" << head->sv.SODT << endl;
        head = head->next;
    }
    infile.close();
};


// Ham quan ly sinh vien
void capNhatSinhVien(DS_LOPSV& dsLop) {
    if (dsLop.n == 0) {
        HideCursor();
        gotoXY(45, 6);
        SetColor(4);
        cout << "DANH SACH LOP TRONG. VUI LONG TAO LOP TRUOC KHI CAP NHAT SINH VIEN!";
        gotoXY(40, 9);
        SetColor(2);
        cout << "An phim ESC de thoat!";
        SetColor(7);
        while (1) {
            if (_kbhit()) {
                char key = getch();
                if (key == 27) {  // Nhan ESC de thoat
                    system("cls");
                    return;
                }
            }
        }
    }
    int soTieuDe = 2;
    string text[] = { "Ma Lop","Ten Lop" };
    string maLop = listBoxLSV(dsLop, 20, text, soTieuDe);
    if (maLop == "-1") {
        xoa_noi_dung_khung();
        return;
    }
    int viTri;
    do {
        viTri = Tim_viTri_Lop(dsLop, maLop);
        if (viTri == -1) {
            gotoXY(40, 24);
            SetColor(4);
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                                    ";
            continue;
        }
        break;
    } while (1);
    LopSV& lop = dsLop.nodes[viTri];
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "MENU QUAN LY SINH VIEN");
        boxVuong(35, 3, 80, 22, 15);
        string text[5] = { "THEM SINH VIEN", "XOA SINH VIEN", "HIEU CHINH SINH VIEN", "IN DS SINH VIEN", "THOAT" };
        box_huong_dan_menu();
        int luachon = thanhSangListBox(xL, yL, wL, hL, 11, 14, text, 5);
        int soDuLieu = countSVtrongLop(lop.First);
        string tieuDe1[] = { "MASV","        HO va TEN","                  PHAI","  SODT" };
        int nTieuDe1 = 4;
        string select;
        switch (luachon) {
        case 0:
            themSinhVien(dsLop,lop);
            break;
        case 1:
            xoaSinhVien(dsLop,lop);
            break;
        case 2:
            SuaThongTinSV(dsLop,lop);
            break;
        case 3:
            // xuat_file_ds_sv_1_lop(lop);
            select = listBoxSVforIn(lop.First, soDuLieu, 20, tieuDe1, nTieuDe1);
            while (true) {
                if (select == "-1") {
                    xoa_noi_dung_khung();
                    ShowCur(false);
                    break;
                }
            }
            break;
        case 4:
            if (xacNhanThoat()) {
                system("cls");
                return;
            }
        }
    }
}

void HienThi_Them_lop(LopSV lop, int viTriChon, int viTriChon_cu, string text[]) {
    for (int i = 0; i < 3; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            cout << "                              ";
            gotoXY(40, 6 + i * 2);
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (lop.MALOP != "--") cout << lop.MALOP;
                else cout << "--";
            }
            else if (i == 1) {
                if (lop.TENLOP != "--") cout << lop.TENLOP;
                else cout << "--";
            }
            SetColor(7);
        }
        else if (viTriChon_cu == 6 + i * 2) {
            cout << "                              ";
            gotoXY(40, 6 + i * 2);
            SetColor(7);
            cout << text[i];
            if (i == 0) {
                if (lop.MALOP != "--") cout << lop.MALOP;
                else cout << "--";
            }
            else if (i == 1) {
                if (lop.TENLOP != "--") cout << lop.TENLOP;
                else cout << "--";
            }
        }
    }
}

void Nhap_ma_lop_lop(LopSV& lop, int viTriChon, DS_LOPSV& dsLop) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                        ";
        gotoXY(40, viTriChon);
        cout << "NHAP MA LOP: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (input.size() > 15) {
            gotoXY(40, 24);
            cout << "Ma lop khong duoc vuot qua 15 ki tu!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                             ";
            continue;
        }
        if (Tim_viTri_Lop(dsLop, input) != -1) {
            gotoXY(40, 24);
            cout << "Ma lop da ton tai!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                             ";
            continue;
        }
        lop.MALOP = input;
        break;
    } while (1);
    SetColor(7);
    HideCursor();
}

void Nhap_ten_lop_lop(LopSV& lop, int viTriChon) {
    SetColor(4);
    gotoXY(40, viTriChon);
    cout << "                                           ";
    gotoXY(40, viTriChon);
    cout << "NHAP TEN LOP: ";
    ShowCursor();
    string input;
    getline(cin, input);
    if (input == "|") {
        HideCursor();
        return;
    }
    lop.TENLOP = input;
    HideCursor();
}

void them_lop(DS_LOPSV& dsLop) {
    HideCursor();
    xoa_noi_dung_khung();
    gotoXY(65, 4);
    SetColor(9);
    cout << "THEM LOP MOI";
    SetColor(12);
    gotoXY(30, 26);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
    SetColor(7);
    if (dsLop.n == 1000) {
        gotoXY(50, 6);
        SetColor(4);
        cout << "DANH SACH LOP DA DAY!";
        gotoXY(40, 9);
        SetColor(2);
        cout << "An phim ESC de thoat!";
        SetColor(7);
        while (1) {
            if (_kbhit()) {
                char key = getch();
                if (key == 27) {  // Nh?n ESC d? tho?t
                    system("cls");
                    ShowCursor();
                    return;
                }
            }
        }
    }
    LopSV lop;
    lop.MALOP = "--"; lop.TENLOP = "--";
    int viTriChon = 6;
    string text[3] = { "NHAP MA LOP: ", "NHAP TEN LOP: ", "          ===CHON LUU===" };
    for (int i = 0; i < 3; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (lop.MALOP != "--") cout << lop.MALOP;
                else cout << "--";
            }
            else if (i == 1) {
                if (lop.TENLOP != "--") cout << lop.TENLOP;
                else cout << "--";
            }
            SetColor(7);
        }
        else {
            cout << text[i];
            if (i == 0) {
                if (lop.MALOP != "--") cout << lop.MALOP;
                else cout << "--";
            }
            else if (i == 1) {
                if (lop.TENLOP != "--") cout << lop.TENLOP;
                else cout << "--";
            }
        }
    }
    while (true) {
        if (_kbhit()) {
            char key = _getch();  // L?y k? t? ngu?i d?ng nh?n
            if (key == 72) {  // Mui t?n l?n
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_lop(lop, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui t?n xu?ng
                if (viTriChon < 10) {
                    viTriChon += 2;
                    HienThi_Them_lop(lop, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
                if (viTriChon == 10) {
                    int ok = -1;
                    if (lop.MALOP == "--") ok = 6;
                    else if (lop.TENLOP == "--") ok = 8;
                    if (ok == -1) {
                        dsLop.nodes[dsLop.n++] = lop;
                        xuat_file_dsLop(dsLop);
                        gotoXY(40, 24);
                        SetColor(10);
                        cout << "Them lop moi thanh cong!";
                        SetColor(7);
                        for (int i = 1; i <= 370000000; i++);
                        gotoXY(40, 24);
                        cout << "                                                      ";
                        them_lop(dsLop);
                        return;
                    }
                    else {
                        SetColor(4);
                        gotoXY(62, 24);
                        cout << "    Nhap thong tin chua day du!";
                        for (int i = 0; i <= 300000000; i++);
                        gotoXY(62, 24); cout << "                                      ";
                        textcolor(7);
                        SetColor(7);
                        viTriChon = ok;
                        HienThi_Them_lop(lop, ok, 10, text);
                    }
                }
                else {
                    int ok = 10;
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 6) Nhap_ma_lop_lop(lop, viTriChon, dsLop);
                    else if (viTriChon == 8) Nhap_ten_lop_lop(lop, viTriChon);
                    if (lop.MALOP == "--") ok = 6;
                    else if (lop.TENLOP == "--") ok = 8;
                    SetColor(12);
                    gotoXY(30, 26);
                    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
                    HienThi_Them_lop(lop, ok, viTriChon, text);
                    viTriChon = ok;
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}

void xoa_lop(DS_LOPSV& dsLop) {
    if (dsLop.n == 0) {
        cout << "Danh sach lop trong";
        return;
    }
    int soTieuDe = 2;
    string text[] = { "Ma Lop", "Ten Lop" };
    while (true) {
        string maLop = listBoxLSV(dsLop, 20, text, soTieuDe);
        if (maLop == "-1") {
            xoa_noi_dung_khung();
            return;
        }
        int viTri = Tim_viTri_Lop(dsLop, maLop);
        bool xacNhan;
        boxXacNhan(40, 10, 30, 5, "Xac nhan xoa lop?", "Co", "Khong", xacNhan);
        if (xacNhan) {
            for (int i = viTri; i < dsLop.n - 1; i++) {
                dsLop.nodes[i] = dsLop.nodes[i + 1];
            }
            dsLop.n--;
            xuat_file_dsLop(dsLop);
            SetColor(6);
            gotoXY(62, 24);
            cout << "    Xoa thanh cong";
            for (int i = 0; i <= 300000000; i++);
            gotoXY(62, 24); cout << "                                      ";
            textcolor(7);
        }
        xoa_noi_dung_khung();
    }
}
void hieu_chinh_lop(DS_LOPSV& dsLop) {
    if (dsLop.n == 0) {
        cout << "Danh sach lop trong.";
        return;
    }
    int soTieuDe = 2;
    string tieuDe[] = { "Ma Lop", "Ten Lop" };
    string maLop = listBoxLSV(dsLop, 20, tieuDe, soTieuDe);
    if (maLop == "-1") {
        xoa_noi_dung_khung();
        return;
    }
    int viTri = Tim_viTri_Lop(dsLop, maLop);
    LopSV lop = dsLop.nodes[viTri];
    int viTriChon = 6;
    string text[3] = { "NHAP MA LOP: ", "NHAP TEN LOP: ", "       ====Luu====" };
    ShowCur(false);
    xoa_noi_dung_khung();
    SetColor(12);
    gotoXY(30, 26);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
    while (true) {
        gotoXY(65, 4);
        SetColor(9);
        cout << "HIEU CHINH LOP SINH VIEN";
        SetColor(12);
        gotoXY(30, 26);
        cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE QUAY LAI";
        for (int i = 0; i < 3; i++) {
            gotoXY(40, 6 + i * 2);
            if (viTriChon == 6 + i * 2) {
                SetColor(4);
                cout << text[i];
                if (i == 0) {
                    cout << lop.MALOP;
                }
                else if (i == 1) {
                    cout << lop.TENLOP;
                }
                SetColor(7);
            }
            else {
                SetColor(7);
                cout << text[i];
                if (i == 0) {
                    cout << lop.MALOP;
                }
                else if (i == 1) {
                    cout << lop.TENLOP;
                }
            }
        }
        if (_kbhit()) {
            char key = _getch();
            if (key == 72) {
                if (viTriChon > 6) {
                    viTriChon -= 2;
                }
            }
            else if (key == 80) {
                if (viTriChon < 10) {
                    viTriChon += 2;
                }
            }
            else if (key == 13) {
                if (viTriChon == 10) {
                    dsLop.nodes[viTri] = lop;
                    xuat_file_dsLop(dsLop);
                    gotoXY(45, 12);
                    SetColor(10);
                    cout << "Cap nhat thanh cong.";
                    SetColor(7);
                    for (int i = 0; i < 300000000; i++);
                    hieu_chinh_lop(dsLop);
                    return;
                }
                else if (viTriChon == 6) {
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    Nhap_ma_lop_lop(lop, viTriChon, dsLop);
                }
                else if (viTriChon == 8) {
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    Nhap_ten_lop_lop(lop, viTriChon);
                }
            }
            else if (key == 27) {
                ShowCur(true);
                hieu_chinh_lop(dsLop);
                return;
            }
        }
    }
}
// H?m qu?n l? l?p
void capNhatLop(DS_LOPSV& dsLop) {
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "MENU QUAN LY LOP");
        boxVuong(35, 3, 80, 22, 15);
        string text[5] = { "THEM LOP", "XOA LOP", "HIEU CHINH LOP", "IN DANH SACH LOP", "THOAT" };
        box_huong_dan_menu();
        int luachon = thanhSangListBox(xL, yL, wL, hL, 11, 14, text, 5);
        switch (luachon) {
        case 0:
            them_lop(dsLop);
            break;
        case 1:
            xoa_lop(dsLop);
            break;
        case 2: {
            hieu_chinh_lop(dsLop);
            break;
        }
        case 3: {
            inDanhSachLop(dsLop);
            break;
        }
        case 4:
            if (xacNhanThoat()) {
                system("cls");
                return;
            }
            break;
        }
    }
}

// H?m hi?n th? menu ch?nh v? x? l? l?a ch?n
void hienThiMenuChinh(DS_LOPSV& dsLop) {
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "MENU LOP - SINH VIEN");
        boxVuong(35, 3, 80, 22, 15);
        string text[] = { "CAP NHAT LOP", "CAP NHAT SINH VIEN", "Thoat" };
        box_huong_dan_menu();
        int luachon = thanhSangListBox(xL, yL, wL, hL, 11, 14, text, 3);
        switch (luachon) {
        case 0:
            capNhatLop(dsLop);
            break;
        case 1:
            capNhatSinhVien(dsLop);
            break;
        case 2:
            if (xacNhanThoat()) {
                system("cls");
                return;
            }
            break;
        }
    }
}

// H?m kiem tra danh sach mon hoc co trong khong
bool isEmpty(treeMH root) {
    return root == NULL;
}

int height(treeMH root) {
    if (root == NULL)
        return 0;
    return root->bf;
}

treeMH rightRotate(treeMH y) {
    treeMH x = y->left;
    treeMH T2 = x->right;
    x->right = y;
    y->left = T2;
    y->bf = 1 + max(height(y->left), height(y->right));
    x->bf = 1 + max(height(x->left), height(x->right));
    return x;
}

treeMH leftRotate(treeMH x) {
    treeMH y = x->right;
    treeMH T2 = y->left;
    y->left = x;
    x->right = T2;
    x->bf = 1 + max(height(x->left), height(x->right));
    y->bf = 1 + max(height(y->left), height(y->right));
    return y;
}

int getBalance(treeMH root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

treeMH insertMH(treeMH root, MonHoc mh) {
    if (root == NULL) {
        treeMH node = new nodeMH;
        node->bf = 0;
        node->left = NULL;
        node->right = NULL;
        node->mh = mh;
        root = node;
        return root;
    }
    if (mh.MAMH < root->mh.MAMH) root->left = insertMH(root->left, mh);
    else if (mh.MAMH > root->mh.MAMH) root->right = insertMH(root->right, mh);
    root->bf = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && mh.MAMH < root->left->mh.MAMH)  return rightRotate(root);
    if (balance < -1 && mh.MAMH > root->right->mh.MAMH) return leftRotate(root);
    if (balance > 1 && mh.MAMH > root->left->mh.MAMH) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && mh.MAMH < root->right->mh.MAMH) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void HienThi_Them_mh(MonHoc& mh, int viTriChon, int viTriChon_cu, string text[]) {
    for (int i = 0; i < 5; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            cout << "                              ";
            gotoXY(40, 6 + i * 2);
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (mh.MAMH != "--") cout << mh.MAMH;
                else cout << "--";
            }
            else if (i == 1) {
                if (mh.TENMH != "--") cout << mh.TENMH;
                else cout << "--";
            }
            else if (i == 2) {
                if (mh.STCLT != -1) cout << mh.STCLT;
                else cout << "--";
            }
            else if (i == 3) {
                if (mh.STCTH != -1) cout << mh.STCTH;
                else cout << "--";
            }
            SetColor(7);
        }
        else {
            cout << "                              ";
            gotoXY(40, 6 + i * 2);
            SetColor(7);
            cout << text[i];
            if (i == 0) {
                if (mh.MAMH != "--") cout << mh.MAMH;
                else cout << "--";
            }
            else if (i == 1) {
                if (mh.TENMH != "--") cout << mh.TENMH;
                else cout << "--";
            }
            else if (i == 2) {
                if (mh.STCLT != -1) cout << mh.STCLT;
                else cout << "--";
            }
            else if (i == 3) {
                if (mh.STCTH != -1) cout << mh.STCTH;
                else cout << "--";
            }
        }
    }
}

void Nhap_ma_mon_hoc_mh(MonHoc& mh, int viTriChon, treeMH& root, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                          ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP MA MON HOC: ";
        else cout << "SUA MA MON HOC: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (input.size() > 10) {
            gotoXY(40, 24);
            cout << "Ma mon hoc khong duoc qua 10 ki tu!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                     ";
            continue;
        }
        if (!isDuplicateMH(root, input)) {
            mh.MAMH = input;
            break;
        }
        gotoXY(40, 24);
        cout << "Da ton tai ma mon hoc nay!";
        for (int i = 1; i <= 300000000; i++);
        gotoXY(40, 24);
        cout << "                               ";
    } while (1);
    SetColor(7);
    HideCursor();
}

void Nhap_ten_mon_hoc_mh(MonHoc& mh, int viTriChon, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                   ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP TEN MON HOC: ";
        else if (input == 1) cout << "SUA TEN MON HOC: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (input.size() > MAX_SIZE_NAME_MH) {
            gotoXY(40, 24);
            cout << "Ma mon hoc khong duoc qua 50 ki tu!";
            for (int i = 1; i <= 300000000; i++);
            gotoXY(40, 24);
            cout << "                                             ";
            continue;
        }
        mh.TENMH = input;
        break;
    } while (1);
    SetColor(7);
    HideCursor();
}

void Nhap_so_tclt_mh(MonHoc& mh, int viTriChon, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP SO TIN CHI LY THUYET: ";
        else if (input == 1) cout << "SUA SO TIN CHI LY THUYET: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (kiemTraChuoiSo(input)) {
            mh.STCLT = stoi(input);
            break;
        }
        gotoXY(40, 24);
        cout << "So tin chi ly thuyet la so nguyen khong am!";
        for (int i = 1; i <= 300000000; i++);
        gotoXY(40, 24);
        cout << "                                             ";
    } while (1);
    SetColor(7);
    HideCursor();
}

void Nhap_so_tcth_mh(MonHoc& mh, int viTriChon, int input) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                               ";
        gotoXY(40, viTriChon);
        if (input == 0) cout << "NHAP SO TIN CHI THUC HANH: ";
        else if (input == 1) cout << "SUA SO TIN CHI THUC HANH: ";
        ShowCursor();
        string input;
        getline(cin, input);
        if (input == "|") {
            HideCursor();
            return;
        }
        if (kiemTraChuoiSo(input)) {
            mh.STCTH = stoi(input);
            break;
        }
        gotoXY(40, 24);
        cout << "So tin chi thuc hanh la so nguyen khong am!";
        for (int i = 1; i <= 300000000; i++);
        gotoXY(40, 24);
        cout << "                                              ";
    } while (1);
    SetColor(7);
    HideCursor();
}

// Ham them mon hoc
void addMonHoc(treeMH& root) {
    HideCursor();
    xoa_noi_dung_khung();
    gotoXY(65, 4);
    SetColor(9);
    cout << "THEM MOI MON HOC";
    SetColor(7);
    MonHoc mh;
    mh.MAMH = "--"; mh.TENMH = "--"; mh.STCLT = -1; mh.STCTH = -1;
    int viTriChon = 6;
    string text[5] = { "NHAP MA MON HOC: ", "NHAP TEN MON HOC: ",
                 "NHAP SO TIN CHI LY THUYET: ",
                "NHAP SO TIN CHI THUC HANH: ", "          ===CHON LUU===" };
    for (int i = 0; i < 5; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (mh.MAMH != "--") cout << mh.MAMH;
                else cout << "--";
            }
            else if (i == 1) {
                if (mh.TENMH != "--") cout << mh.TENMH;
                else cout << "--";
            }
            else if (i == 2) {
                if (mh.STCLT != -1) cout << mh.STCLT;
                else cout << "--";
            }
            else if (i == 3) {
                if (mh.STCTH != -1) cout << mh.STCTH;
                else cout << "--";
            }
            SetColor(7);
        }
        else {
            cout << text[i];
            if (i == 0) {
                if (mh.MAMH != "--") cout << mh.MAMH;
                else cout << "--";
            }
            else if (i == 1) {
                if (mh.TENMH != "--") cout << mh.TENMH;
                else cout << "--";
            }
            else if (i == 2) {
                if (mh.STCLT != -1) cout << mh.STCLT;
                else cout << "--";
            }
            else if (i == 3) {
                if (mh.STCTH != -1) cout << mh.STCTH;
                else cout << "--";
            }
        }
    }
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    while (true) {
        if (_kbhit()) {
            gotoXY(30, 26);
            SetColor(12);
            cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
            SetColor(7);
            char key = _getch();
            if (key == KEY_UP) {  // Mui ten len
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_mh(mh, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == KEY_DOWN) {  // Mui t?n xu?ng
                if (viTriChon < 14) {
                    viTriChon += 2;
                    HienThi_Them_mh(mh, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == KEY_ENTER) {  // Nhan Enter de nhap mon
                if (viTriChon == 14) {
                    int ok = -1;
                    if (mh.MAMH == "--") ok = 6;
                    else if (mh.TENMH == "--") ok = 8;
                    else if (mh.STCLT == -1) ok = 10;
                    else if (mh.STCTH == -1) ok = 12;
                    if (ok == -1) {
                        root = insertMH(root, mh);
                        gotoXY(40, 24);
                        SetColor(10);
                        cout << "Them moi lop tin chi thanh cong!";
                        SetColor(7);
                        for (int i = 1; i <= 370000000; i++);
                        gotoXY(40, 24);
                        cout << "                                                         ";
                        addMonHoc(root);
                        return;
                    }
                    else {
                        SetColor(4);
                        gotoXY(62, 24);
                        cout << "    Nhap thong tin chua day du!";
                        for (int i = 0; i <= 300000000; i++);
                        textcolor(0);
                        gotoXY(62, 24); cout << "                                      ";
                        textcolor(7);
                        SetColor(7);
                        viTriChon = ok;
                        HienThi_Them_mh(mh, ok, 14, text);
                    }
                }
                else {
                    int ok = -1;
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 6) Nhap_ma_mon_hoc_mh(mh, viTriChon, root, 0);
                    else if (viTriChon == 8) Nhap_ten_mon_hoc_mh(mh, viTriChon, 0);
                    else if (viTriChon == 10) Nhap_so_tclt_mh(mh, viTriChon, 0);
                    else if (viTriChon == 12) Nhap_so_tcth_mh(mh, viTriChon, 0);
                    //======
                    if (mh.MAMH == "--") ok = 6;
                    else if (mh.TENMH == "--") ok = 8;
                    else if (mh.STCLT == -1) ok = 10;
                    else if (mh.STCTH == -1) ok = 12;
                    if (ok != -1) {
                        HienThi_Them_mh(mh, ok, viTriChon, text);
                        viTriChon = ok;
                    }
                    else {
                        ok = viTriChon;
                        viTriChon = 14;
                        HienThi_Them_mh(mh, viTriChon, ok, text);
                    }
                }
            }
            else if (key == KEY_ESC) {
                xoa_noi_dung_khung();
                ShowCursor();
                return;
            }
        }
    }
}

treeMH minValueNode(treeMH& root) {
    treeMH current = root;
    while (current->left != NULL) current = current->left;
    return current;
}

treeMH deleteMH(treeMH& root, string& mamh) {
    if (root == NULL) {
        cout << "Ma mon hoc khong ton tai!" << endl;
        return NULL;
    }
    if (mamh < root->mh.MAMH) root->left = deleteMH(root->left, mamh);
    else if (mamh > root->mh.MAMH) root->right = deleteMH(root->right, mamh);
    else {
        if (root->left == NULL) {
            treeMH temp = root->right;
            root = NULL;
            return temp;
        }
        else if (root->right == NULL) {
            treeMH temp = root->left;
            root = NULL;
            return temp;
        }
        treeMH temp = minValueNode(root->right);
        root->mh = temp->mh;
        root->right = deleteMH(root->right, temp->mh.MAMH);
    }
    if (root == NULL) return root;
    root->bf = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int countMonHoc(treeMH root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return 1 + countMonHoc(root->left) + countMonHoc(root->right);
    }
}
// Ham xoa cua Hoang================================================================================================
void drawMH_InOrder(treeMH root, int x, int y, int khoangCachMoiCot[], int chonHang, int start, int end, int& index, string& mamh) {
    if (root == nullptr) return;
    drawMH_InOrder(root->left, x, y, khoangCachMoiCot, chonHang, start, end, index, mamh);
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    if (index >= start && index < end) {
        gotoXY(x, y + (index - start));
        if (index == chonHang) {
            mamh = root->mh.MAMH;
            textcolor(200);
            SetColor(0);
        }
        printf("%-*d", khoangCachMoiCot[0], index + 1);
        printf("%-*s", khoangCachMoiCot[1], root->mh.MAMH.c_str());
        printf("%-*s", khoangCachMoiCot[2], root->mh.TENMH.c_str());
        printf("%-*d", khoangCachMoiCot[3], root->mh.STCLT);
        printf("%-*d", khoangCachMoiCot[4], root->mh.STCTH);
        textcolor(7);
        cout << endl;
    }
    index++;
    drawMH_InOrder(root->right, x, y, khoangCachMoiCot, chonHang, start, end, index, mamh);
    return;
}
void drawMH(int x, int y, int w, int h, treeMH root, int soDuLieu, int soTrang, int chonHang, int trangBefore, string tieuDe[], int ntieuDe, string& mamh) {
    int khoangCachMoiCot[] = { w * 0.1, w * 0.2, w * 0.5, w * 0.1, w * 0.1 };
    gotoXY(x, y);
    printf("%-*s", khoangCachMoiCot[0], "STT");
    for (int i = 0; i < ntieuDe; i++) {
        printf("%-*s", khoangCachMoiCot[i + 1], tieuDe[i].c_str());
    }
    cout << endl;
    int index = 0;
    int start = soTrang * trangBefore;
    int end = min(start + trangBefore, soDuLieu); drawMH_InOrder(root, x, y + 1, khoangCachMoiCot, chonHang, start, end, index, mamh);
}
string listBoxMH(treeMH root, int soDuLieu, string tieuDe[], int ntieuDe) {
    int totalRows = soDuLieu;
    int sttOfTrang = 0;
    int hangNgangdangChon = 0;
    ShowCur(false);
    string mamh = "-1";
    while (true) {
        drawMH(37, 4, 78, 22, root, soDuLieu, sttOfTrang, hangNgangdangChon, 20, tieuDe, ntieuDe, mamh);
        int key = _getch();
        if (key == KEY_UP) {
            if (hangNgangdangChon > 0) {
                hangNgangdangChon--;
                if (hangNgangdangChon < sttOfTrang * 20) {
                    sttOfTrang--;
                }
            }
        }
        else if (key == KEY_DOWN) {
            if (hangNgangdangChon < totalRows - 1) {
                hangNgangdangChon++;
                if (hangNgangdangChon >= (sttOfTrang + 1) * 20) {
                    sttOfTrang++;
                    xoa_noi_dung_khung();
                }
            }
        }
        else if (key == KEY_ENTER) {
            ShowCur(true);
            return mamh;
        }
        else if (key == KEY_ESC) {
            ShowCur(true);
            return "-1";
        }
    }
}

void Xoa_MH(treeMH& root, List_LTC& dsltc) {
    int index = 0;
    SetColor(7);
    int nTieuDe = 4;
    int soDuLieu = countMonHoc(root);
    string mamh;
    string tieuDe[4] = { "MA MON", "TEN MON", "STCLT", "STCTH" };
    string chonHang;
    while (true) {
        chonHang = listBoxMH(root, soDuLieu, tieuDe, nTieuDe);
        if (chonHang == "-1") {
            xoa_noi_dung_khung();
            break;
        }
        else {
            deleteMH(root, chonHang);
            soDuLieu--;
            xoa_noi_dung_khung();
        }
    }
}

void HieuChinhMH(treeMH root, List_LTC& dsltc);
// End ham xoa cua Hoang=============================================================================================
void updateMH(treeMH& root, string maMH, List_LTC& dsltc) {
    HideCursor();
    xoa_noi_dung_khung();
    gotoXY(65, 4);
    SetColor(9);
    cout << "SUA MON HOC";
    SetColor(7);
    treeMH Sua_mh = searchMH(root, maMH);
    MonHoc* mh = new MonHoc;
    *mh = Sua_mh->mh;
    int viTriChon = 6;
    string text[5] = { "SUA MA MON HOC: ", "SUA TEN MON HOC: ",
                 "SUA SO TIN CHI LY THUYET: ",
                "SUA SO TIN CHI THUC HANH: ", "        ====CAP NHAT====" };
    for (int i = 0; i < 5; i++) {
        gotoXY(40, 6 + i * 2);
        SetColor(7);
        if (viTriChon == 6 + i * 2) SetColor(4);
        cout << text[i];
        if (i == 0) cout << (*mh).MAMH;
        else if (i == 1) cout << (*mh).TENMH;
        else if (i == 2) cout << (*mh).STCLT;
        else if (i == 3)  cout << (*mh).STCTH;
        SetColor(7);
    }
    bool thayDoima = 0;
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    while (true) {
        if (_kbhit()) {
            gotoXY(30, 26);
            SetColor(12);
            cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
            SetColor(7);
            char key = _getch();  // L?y k? t? ngu?i d?ng nh?n
            if (key == 72) {  // Mui t?n l?n
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_mh((*mh), viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui t?n xu?ng
                if (viTriChon < 14) {
                    viTriChon += 2;
                    HienThi_Them_mh((*mh), viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
                if (viTriChon == 14) {
                    if (thayDoima == 0) {
                        Sua_mh->mh = *mh;
                        delete mh;
                    }
                    else {
                        for (int i = 1; i <= dsltc.n; i++) {
                            if (dsltc.nodes[i]->MAMH == Sua_mh->mh.MAMH) dsltc.nodes[i]->MAMH = (*mh).MAMH;
                        }
                        insertMH(root, *mh);
                        deleteMH(root, Sua_mh->mh.MAMH);
                        delete mh;
                    }
                    gotoXY(40, 24);
                    SetColor(10);
                    cout << "Cap nhat mon hoc thanh cong!";
                    SetColor(7);
                    for (int i = 1; i <= 370000000; i++);
                    gotoXY(40, 24);
                    cout << "                                                         ";
                    HieuChinhMH(root, dsltc);
                    return;
                }
                else {
                    SetColor(12);
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 6) {
                        Nhap_ma_mon_hoc_mh((*mh), viTriChon, root, 1);
                        thayDoima = 1;
                    }
                    else if (viTriChon == 8) Nhap_ten_mon_hoc_mh((*mh), viTriChon, 1);
                    else if (viTriChon == 10) Nhap_so_tclt_mh((*mh), viTriChon, 1);
                    else if (viTriChon == 12) Nhap_so_tcth_mh((*mh), viTriChon, 1);
                    //======
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                xoa_noi_dung_khung();
                ShowCursor();
                return;
            }
        }
    }
}

void HieuChinhMH(treeMH root, List_LTC& dsltc) {
    int index = 0;
    SetColor(7);
    int nTieuDe = 4;
    int soDuLieu = countMonHoc(root);
    string mamh;
    string tieuDe[4] = { "MA MON", "TEN MON", "STCLT", "STCTH" };
    string chonHang;
    while (true) {
        chonHang = listBoxMH(root, soDuLieu, tieuDe, nTieuDe);
        if (chonHang == "-1") {
            xoa_noi_dung_khung();
            return;
        }
        else {
            xoa_noi_dung_khung();
            updateMH(root, chonHang, dsltc);
            return;
        }
    }
}

void chuyen_doi(MonHoc mh[], treeMH& root, int& stt) {
    if (root->left != NULL) chuyen_doi(mh, root->left, stt);
    mh[stt++] = root->mh;
    if (root->right != NULL) chuyen_doi(mh, root->right, stt);
    bool swapped = false;
    for (int i = 0; i < stt - 1; i++) {
        for (int j = 0; j < stt - i - 1; j++) {
            if (mh[j].TENMH > mh[j + 1].TENMH) {
                swap(mh[j], mh[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
}


void NhapMonHoc(treeMH& root, List_LTC& dsltc) {
    int stt = 0;
    int soDuLieu = countMonHoc(root);
    MonHoc* mang_mh = new MonHoc[soDuLieu];
    chuyen_doi(mang_mh, root, stt);
    system("cls");
    boxDefault(xD, yD, wD, hD, tD, "NHAP MON HOC");
    boxVuong(35, 3, 80, 22, 15);
    string nd[] = { "Them mon hoc", " Xoa mon hoc", "Hieu chinh mon hoc", "Hien thi DSMH",  "Thoat" };
    while (true) {
        box_huong_dan_menu();
        int luachon = thanhSangListBox(xL, yL, wL, hL, 7, 14, nd, 5);
        switch (luachon) {
        case 0:
            addMonHoc(root);
            break;
        case 1:
            Xoa_MH(root, dsltc);
            break;
        case 2:
            HieuChinhMH(root, dsltc);
            break;
        case 3:
            if (isEmpty(root)) {
                cout << "Danh sach mon hoc trong!" << endl;
            }
            else {
                int index = 0;
                SetColor(7);
                int nTieuDe = 4;
                string mamh;
                string tieuDe[4] = { "MA MON", "TEN MON", "STCLT", "STCTH" };
                string chonHang;
                while (true) {
                    chonHang = listBoxMH(root, soDuLieu, tieuDe, nTieuDe);
                    if (chonHang == "-1") {
                        xoa_noi_dung_khung();
                        break;
                    }
                }
                int stt = 0;
                MonHoc* mang_mh = new MonHoc[soDuLieu];
                chuyen_doi(mang_mh, root, stt);
                ofstream infile;
                infile.open("C:\\Users\\admin\\Downloads\\C++\\ds_mh.txt", ios_base::out);
                infile << "     =====DANH SACH MON HOC=====" << endl;
                infile << "=====================================" << endl;
                infile << "STT\tMA MON HOC\tTEN MON HOC\t\tSO TIN CHI LT\tSO TIN CHI TH" << endl;
                for (int i = 0; i < soDuLieu; i++) {
                    infile << i + 1 << "\t" << mang_mh[i].MAMH;
                    for (int j = 1; j <= 16 - (mang_mh[i].MAMH).size(); j++) infile << " ";
                    infile << mang_mh[i].TENMH;
                    for (int j = 1; j <= 24 - (mang_mh[i].TENMH).size(); j++) infile << " ";
                    infile << mang_mh[i].STCLT << "\t\t" << mang_mh[i].STCTH << endl;
                }
                infile.close();
            }
            break;
        case 4:
            if (xacNhanThoat()) {
                system("cls");
                return;
            }
            break;
        }
    }
}


treeMH _findTenMH(treeMH root, string maMH) {
    if (root == NULL) return NULL;
    if (root->mh.MAMH == maMH) return root;
    else if (root->mh.MAMH > maMH) return _findTenMH(root->left, maMH);
    else return _findTenMH(root->right, maMH);
}


void LocLTC(List_LTC dsltc, string nienkhoa, int hocky, LopTinChi* ltc[], int& soLuong) {
    soLuong = 0;
    for (int i = 1; i <= dsltc.n; i++) {
        if (dsltc.nodes[i]->NienKhoa == nienkhoa && dsltc.nodes[i]->Hocky == hocky) {
            ltc[soLuong] = dsltc.nodes[i];
            soLuong++;
        }
    }
}

void _dangKyLopTinChi(List_LTC& dsltc, string nienkhoa, int hocky, string maSV, treeMH root, LopTinChi& ltc, DS_LOPSV& dsLop) {
    int maLoptc;
    cout << "Nhap ma lop tin chi ban muon dang ky(An phim '0' de quay lai): ";
    cin >> maLoptc;
    cin.ignore();
    if (maLoptc == 0) {
        system("cls");
        SVDK_LTC(dsLop, dsltc, root);
        return;
    }
    int i = TimLTC(maLoptc, dsltc);
    if (i == -1) {
        cout << "Khong tim thay lop tin chi voi ma lop da nhap!\n";
    }
    else {
        if (dsltc.nodes[i]->sosvmax <= DemSoSinhVien(dsltc.nodes[i]->dssvdk)) {
            cout << "So sinh vien dang ky lop tin chi nay da day. Khong the dang ky!\n";
        }
        else {
            PTRDK tmp = dsltc.nodes[i]->dssvdk;
            while (tmp != NULL) {
                if (tmp->dk.MASV == maSV) {
                    cout << "Sinh vien da dang ky lop tin chi nay roi!\n";
                    system("cls");
                    SVDK_LTC(dsLop, dsltc, root);
                    return;
                }
                tmp = tmp->next;
            }
            char confirm;
            cout << "Ban co chac chan muon dang ky lop tin chi nay khong? (y/n): "; cin >> confirm;
            if (confirm == 'y' || confirm == 'Y') {
                PTRDK newdkltc = new nodeDK;
                newdkltc->dk.MASV = maSV;
                newdkltc->dk.huydangky = false;
                newdkltc->next = dsltc.nodes[i]->dssvdk;
                dsltc.nodes[i]->dssvdk = newdkltc;
                cout << "Dang ky lop tin chi thanh cong!\n";
                xuat_file_SVDKLTC(dsltc);
            }
            else {
                cout << "Dang ky lop tin chi da bi huy bo.\n";
            }
        }
        system("cls");
        SVDK_LTC(dsLop, dsltc, root);
        return;
    }
}

void hienThiThongTinLopTinChi_3(treeMH DSMH, LopTinChi* ltc[], int soLuong) {
    system("cls");
    cout << "================DANH SACH LOP TIN CHI================\n";
    cout << "MaLTC\tMAMH\tTENMH\t\tNHOM\tSV_DK\tSlot_Trong\n";
    for (int i = 0; i < soLuong; i++) {
        LopTinChi* tmp = ltc[i];
        treeMH monHoc = _findTenMH(DSMH, ltc[i]->MAMH);
        if (monHoc != NULL) {
            string tenMH = monHoc->mh.TENMH;
            int soSVDaDK = DemSoSinhVien(tmp->dssvdk);
            int soSlotTrong = tmp->sosvmax - soSVDaDK;
            cout << tmp->MALOPTC << "\t" << tmp->MAMH << "\t" << tenMH << "\t\t" << tmp->Nhom << "\t"
                << soSVDaDK << "\t" << soSlotTrong << "\n";
        }
    }
    cout << "\n====================================================\n";
}

SinhVien* Timsv(DS_LOPSV& dsLopSV, string maSV) {
    for (int i = 0; i < dsLopSV.n; ++i) {
        SinhVien* a = searchSV(dsLopSV.nodes[i], maSV);
        if (a != NULL) {
            return a;
        }
    }
    return NULL;
}

void TimLopTinChiTheoNienKhoaHocKy(List_LTC& dsltc, treeMH dsMonHoc, string& nienkhoa, int hocky, string maSV, DS_LOPSV& dsLop) {
    LopTinChi* ltc[MAX_LTC];
    int soLuong = 0;
    for (int i = 1; i <= dsltc.n; i++) {
        if (dsltc.nodes[i]->NienKhoa == nienkhoa && dsltc.nodes[i]->Hocky == hocky) {
            ltc[soLuong] = dsltc.nodes[i];
            soLuong++;
        }
    }
    if (soLuong == 0) {
        cout << "Khong ton tai lop tin chi trong nien khoa va hoc ky nay!!\n";
    }
    else {
        hienThiThongTinLopTinChi_3(dsMonHoc, ltc, soLuong);
        _dangKyLopTinChi(dsltc, nienkhoa, hocky, maSV, dsMonHoc, **ltc, dsLop);
    }
}

void HienThi_DangKyLopTinChi(string text[], int viTriChon, int viTriChon_cu, string nienkhoa, string hocky) {
    for (int i = 0; i < 3; i++) {
        gotoXY(40, 11 + i * 2);
        SetColor(7);
        if (11 + i * 2 == viTriChon) {
            SetColor(4);
            cout << text[i];
            if (i == 0) cout << nienkhoa;
            else if (i == 1) cout << hocky;
        }
        else if (11 + i * 2 == viTriChon_cu) {
            SetColor(7);
            cout << text[i];
            if (i == 0) cout << nienkhoa;
            else if (i == 1) cout << hocky;
        }
    }
    SetColor(7);
}

void DangKyLopTinChi(List_LTC& dsltc, DS_LOPSV& dsLop, treeMH dsMonHoc) {
    xoa_noi_dung_khung();
    if (dsltc.n == 0) {
        gotoXY(50, 6);
        SetColor(4);
        cout << "CHUA CO LOP TIN CHI NAO DUOC MO DE IN";
        gotoXY(40, 9);
        SetColor(2);
        cout << "An phim ESC de thoat!";
        SetColor(7);
        while (1) {
            if (_kbhit()) {
                char key = getch();
                if (key == 27) {
                    xoa_noi_dung_khung();
                    ShowCursor();
                    return;
                }
            }
        }
    }
    string maSV, nienkhoa = "--";
    string hocky = "--";
    bool sinhVienTonTai = false;
    SinhVien* a;
    do {
        SetColor(12);
        gotoXY(30, 26); cout << "                                                                          ";
        gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
        gotoXY(40, 5);
        cout << "                                          ";
        gotoXY(40, 5);
        SetColor(6);
        cout << "NHAP MA SINH VIEN CUA BAN: ";
        cin >> maSV;
        cin.ignore();
        SetColor(7);
        if (maSV == "|") {
            return;
        }
        a = Timsv(dsLop, maSV);
        if (a != NULL) {
            gotoXY(40, 7);
            cout << a->MASV << " || " << a->HO << " || " << a->TEN
                << " || " << a->PHAI << " || " << a->SODT;
            break;
        }
        gotoXY(40, 24);
        SetColor(4);
        cout << "Ma sinh vien " << maSV << " khong ton tai!";
        for (int i = 1; i <= 300000000; i++);
        gotoXY(40, 24);
        cout << "                                         ";
    } while (1);
    gotoXY(50, 9);
    SetColor(9);
    cout << "NHAP NIEN KHOA VA HOC KY DE DANG KY LOP TIN CHI";
    SetColor(7);
    string text[3] = { "NHAP NIEN KHOA: ", "NHAP HOC KY: ", "        ====CHON====" };
    int viTriChon = 11;
    for (int i = 0; i < 3; i++) {
        gotoXY(40, 11 + i * 2);
        SetColor(7);
        if (11 + i * 2 == viTriChon) SetColor(4);
        cout << text[i];
        if (i == 0) cout << nienkhoa;
        if (i == 1) cout << hocky;
    }
    HideCursor();
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    while (1) {
        if (_kbhit()) {
            gotoXY(30, 26);
            SetColor(12);
            cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
            SetColor(7);
            char key = _getch();  // L?y k? t? ngu?i d?ng nh?n
            if (key == 72) {  // Mui t?n l?n
                if (viTriChon > 11) {
                    viTriChon -= 2;
                    HienThi_DangKyLopTinChi(text, viTriChon, viTriChon + 2, nienkhoa, hocky);
                }
            }
            else if (key == 80) {  // Mui t?n xu?ng
                if (viTriChon < 15) {
                    viTriChon += 2;
                    HienThi_DangKyLopTinChi(text, viTriChon, viTriChon - 2, nienkhoa, hocky);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
                if (viTriChon == 15) {
                    int ok = -1;
                    if (nienkhoa == "--") {
                        gotoXY(40, 24);
                        SetColor(4);
                        cout << "Chua nhap nien khoa!";
                        for (int i = 1; i <= 300000000; i++);
                        gotoXY(40, 24);
                        cout << "                                         ";
                        HienThi_DangKyLopTinChi(text, 11, viTriChon, nienkhoa, hocky);
                        viTriChon = 11;
                    }
                    else if (hocky == "--") {
                        gotoXY(40, 24);
                        SetColor(4);
                        cout << "Chua nhap hoc ky!";
                        for (int i = 1; i <= 300000000; i++);
                        gotoXY(40, 24);
                        cout << "                                         ";
                        HienThi_DangKyLopTinChi(text, 13, viTriChon, nienkhoa, hocky);
                        viTriChon = 13;
                    }
                    else {
                        TimLopTinChiTheoNienKhoaHocKy(dsltc, dsMonHoc, nienkhoa, stoi(hocky), maSV, dsLop);
                    }
                }
                else {
                    int ok = 15;
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 11) Nhap_nk_in_ds_svdk(nienkhoa, viTriChon);
                    else if (viTriChon == 13) Nhap_hk_in_ds_svdk(hocky, viTriChon);
                    if (nienkhoa == "--") ok = 11;
                    else if (hocky == "--") ok = 13;
                    HienThi_DangKyLopTinChi(text, ok, viTriChon, nienkhoa, hocky);
                    viTriChon = ok;
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                xoa_noi_dung_khung();
                ShowCursor();
                return;
            }
        }
    }
}


float nhap_diem(float& Diem) {
    string point;
    bool Thoat = false;
    do {
        do {
            cin >> point;
            cin.ignore();
            bool ok = true;
            Thoat = false;
            for (int i = 0; i < point.size(); i++) {
                if (!isdigit(point[i])) {
                    if (point[i] == '.') {
                        if (ok == false || i == point.size() - 1 || i == 0) {
                            cout << "Vui long nhap diem hop le!\n";
                            Thoat = true;
                            break;
                        }
                        else ok = 0;
                    }
                    else {
                        cout << "Vui long nhap diem hop le!\n";
                        Thoat = true;
                        break;
                    }
                }
            }
        } while (Thoat);
        Diem = stof(point);
        Diem = round(Diem * (10)) / 10;
        if (Diem < 0 || Diem > 10) {
            cout << "Diem khong duoc nho hon 0 va lon hon 10!\n";
        }
        else return Diem;
    } while (1);

}

void nhapDiemChoSinhVien(int viTriChon, PTRDK dssv, int So_luong, DS_LOPSV& dsLopSV) {
    int i = 1;
    float point;
    while (dssv != NULL) {
        if (i == viTriChon) {
            SinhVien* sv = Timsv(dsLopSV, dssv->dk.MASV);
            SetColor(4);
            gotoXY(0, i + 3);
            cout << "                                                           ";
            gotoXY(3, i + 3); cout << i;
            gotoXY(10, i + 3); cout << "| " << sv->MASV;
            gotoXY(21, i + 3); cout << "| " << sv->HO;
            gotoXY(40, i + 3); cout << "| " << sv->TEN;
            gotoXY(51, i + 3); cout << "| ";
            ShowCursor();
            nhap_diem(point);
            if (point < 0) return;
            dssv->dk.DIEM = point;
            SetColor(7);
            break;
        }
        i++;
        dssv = dssv->next;
    }
    for (int i = 0; i <= So_luong + 3; i++) {
        cout << "                                             " << endl;
    }
}
// //
void HienThiNhapDiem_2(LopTinChi* nhap_diem, int viTriChon, int viTriChon_cu, int So_luong, DS_LOPSV& dsLopSV, PTRDK dssv) {
    int i = 1;
    gotoXY(0, 3);
    SinhVien* sv;
    while (dssv != NULL) {
        if (i == viTriChon) {
            sv = Timsv(dsLopSV, dssv->dk.MASV);
            SetColor(4);
            gotoXY(0, i + 3);
            cout << "                                                  ";
            gotoXY(3, i + 3); cout << i;
            gotoXY(10, i + 3); cout << "| " << sv->MASV;
            gotoXY(21, i + 3); cout << "| " << sv->HO;
            gotoXY(40, i + 3); cout << "| " << sv->TEN;
            gotoXY(51, i + 3); cout << "| ";
            if (dssv->dk.DIEM == -1) cout << "--";
            else cout << dssv->dk.DIEM;
            cout << endl;
            SetColor(7);
        }
        if (i == viTriChon_cu) {
            sv = Timsv(dsLopSV, dssv->dk.MASV);
            SetColor(7);
            gotoXY(0, i + 3);
            cout << "                                                  ";
            gotoXY(3, i + 3); cout << i;
            gotoXY(10, i + 3); cout << "| " << sv->MASV;
            gotoXY(21, i + 3); cout << "| " << sv->HO;
            gotoXY(40, i + 3); cout << "| " << sv->TEN;
            gotoXY(51, i + 3); cout << "| ";
            if (dssv->dk.DIEM == -1) cout << "--";
            else cout << dssv->dk.DIEM;
            cout << endl;
            SetColor(7);
        }
        dssv = dssv->next;
        i++;
        cout << endl;
    }
}
// //
bool HienThiNhapDiem(LopTinChi* nhap_diem, int viTriChon, int So_luong, DS_LOPSV& dsLopSV) {
    system("cls");
    SetColor(7);
    cout << "========================NHAP DIEM LOP TIN CHI========================" << endl;
    cout << "        Nien khoa: " << nhap_diem->NienKhoa;
    cout << "\tHoc ky: " << nhap_diem->Hocky;
    cout << "\tNhom: " << nhap_diem->Nhom;
    cout << "\tMon hoc: " << nhap_diem->MAMH;
    cout << "\n=====================================================================";
    cout << endl;
    PTRDK dssv = nhap_diem->dssvdk;
    int i = 1;
    gotoXY(3, 3); cout << "STT";
    gotoXY(10, 3); cout << "| MASV";
    gotoXY(21, 3); cout << "| HO";
    gotoXY(40, 3); cout << "| TEN";
    gotoXY(51, 3); cout << "| DIEM" << endl;
    while (dssv != NULL) {
        SinhVien* sv = Timsv(dsLopSV, dssv->dk.MASV);
        SetColor(7);
        if (i == viTriChon) SetColor(4);
        gotoXY(3, i + 3); cout << i;
        gotoXY(10, i + 3); cout << "| " << sv->MASV;
        gotoXY(21, i + 3); cout << "| " << sv->HO;
        gotoXY(40, i + 3); cout << "| " << sv->TEN;
        gotoXY(51, i + 3); cout << "| ";
        if (dssv->dk.DIEM == -1) cout << "--";
        else cout << dssv->dk.DIEM;
        cout << endl;
        i++;
        dssv = dssv->next;
        SetColor(7);
    }
    HideCursor();
    while (true) {
        if (_kbhit()) {
            char key = _getch();  // L?y k? t? ngu?i d?ng nh?n

            if (key == KEY_UP) {  // Mui t?n l?n
                if (viTriChon > 1) {
                    viTriChon--;
                    HienThiNhapDiem_2(nhap_diem, viTriChon, viTriChon + 1, So_luong, dsLopSV, nhap_diem->dssvdk);
                }
            }
            else if (key == KEY_DOWN) {  // Mui t?n xu?ng
                if (viTriChon <= So_luong - 1) {
                    viTriChon++;
                    HienThiNhapDiem_2(nhap_diem, viTriChon, viTriChon - 1, So_luong, dsLopSV, nhap_diem->dssvdk);
                }
            }
            else if (key == KEY_ENTER) {  // Nhan Enter de nhap diem
                nhapDiemChoSinhVien(viTriChon, nhap_diem->dssvdk, So_luong, dsLopSV);
                return HienThiNhapDiem(nhap_diem, viTriChon, So_luong, dsLopSV);
            }
            else if (key == KEY_ESC) {  // Nh?n ESC d? tho?t
                system("cls");
                ShowCursor();
                return true;
            }
        }
    }
    return true;
}


void In_Diem_LTC(LopTinChi* nhap_diem, string TenMon, DS_LOPSV& dsLopSV) {
    system("cls");
    SetColor(7);
    cout << "========================BANG DIEM MON HOC " << TenMon << "========================" << endl;
    cout << "              Nien khoa: " << nhap_diem->NienKhoa;
    cout << "\tHoc ky: " << nhap_diem->Hocky;
    cout << "\tNhom: " << nhap_diem->Nhom;
    cout << "\n=============================================================================";
    cout << endl;
    PTRDK dssv = nhap_diem->dssvdk;
    int i = 1;
    gotoXY(3, 3); cout << "STT";
    gotoXY(10, 3); cout << "| MASV";
    gotoXY(18, 3); cout << "| HO";
    gotoXY(40, 3); cout << "| TEN";
    gotoXY(51, 3); cout << "| DIEM" << endl;
    while (dssv != NULL) {
        SinhVien* sv = Timsv(dsLopSV, dssv->dk.MASV);
        gotoXY(3, i + 3); cout << i;
        gotoXY(10, i + 3); cout << "| " << sv->MASV;
        gotoXY(18, i + 3); cout << "| " << sv->HO;
        gotoXY(40, i + 3); cout << "| " << sv->TEN;
        gotoXY(51, i + 3);
        if (dssv->dk.DIEM == -1)  cout << "| --";
        else cout << "| " << fixed << setprecision(1) << dssv->dk.DIEM << endl;
        i++;
        dssv = dssv->next;
    }
    HideCursor();
    SetColor(4);
    cout << "\nAn phim ESC de thoat!";
    while (1) {
        if (_kbhit()) {
            char key = _getch();
            if (key == KEY_ESC) {  // Nh?n ESC d? tho?t
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}

void Indssvdkltc(List_LTC& dsltc, DS_LOPSV& dsLop, treeMH& root, int input);
void Nhap_Bang_Diem(List_LTC& dsltc, string NK, string HK, string Nhom, string MH, DS_LOPSV& dsLop, int input, treeMH& root) {
    LopTinChi* nhap_diem = NULL;
    for (int i = 1; i <= dsltc.n; i++) {
        if (dsltc.nodes[i]->NienKhoa == NK &&
            dsltc.nodes[i]->Hocky == stoi(HK) &&
            dsltc.nodes[i]->Nhom == stoi(Nhom) &&
            dsltc.nodes[i]->MAMH == MH)
        {
            nhap_diem = dsltc.nodes[i];
            break;
        };
    }
    if (nhap_diem == NULL) {
        cout << "Khong ton tai lop tin chi co tham so tren!\n";
        Indssvdkltc(dsltc, dsLop, root, input);
    }
    else {
        if ((nhap_diem)->dssvdk == NULL) {
            cout << "Khong co sinh vien trong lop tin chi tren!\n";
        }
        else {
            if (input == 0) {
                int So_luong = DemSoSinhVien((nhap_diem)->dssvdk);
                int viTriChon = 1;
                bool ok = HienThiNhapDiem(nhap_diem, viTriChon, So_luong, dsLop);
            }
            else if (input == 1) {
                treeMH Monhoc = searchMH(root, MH);
                In_Diem_LTC(nhap_diem, Monhoc->mh.TENMH, dsLop);
            }
        }
    }
}

void Indssvdkltc(List_LTC& dsltc, DS_LOPSV& dsLop, treeMH& root, int input) {
    HideCursor();
    xoa_noi_dung_khung();
    gotoXY(55, 4);
    SetColor(9);
    if (input == 0) cout << "NHAP VA HIEU CHINH DIEM SINH VIEN CUA LOP TIN CHI";
    else if (input == 1) cout << "IN DANH SACH DIEM CUA SINH VIEN LOP TIN CHI";
    else if (input == 2) cout << "IN DANH SACH SINH VIEN DANG KY LOP TIN CHI";
    SetColor(7);
    if (dsltc.n == 0) {
        gotoXY(50, 6);
        SetColor(4);
        cout << "CHUA CO LOP TIN CHI NAO DUOC MO DE IN";
        gotoXY(40, 9);
        SetColor(2);
        cout << "An phim ESC de thoat!";
        SetColor(7);
        while (1) {
            if (_kbhit()) {
                char key = getch();
                if (key == 27) {
                    system("cls");
                    ShowCursor();
                    return;
                }
            }
        }
    }
    string nk = "--", ma = "--", hk = "--", nhom = "--";
    int viTriChon = 6;
    string text[5] = { "NHAP NIEN KHOA: ", "NHAP HOC KY: ",
                 "NHAP NHOM: ",
                "NHAP MA MON HOC: ", "          ===IN DANH SACH===" };
    for (int i = 0; i < 5; i++) {
        gotoXY(40, 6 + i * 2);
        if (viTriChon == 6 + i * 2) {
            SetColor(4);
            cout << text[i];
            if (i == 0) {
                if (nk != "--") cout << nk;
                else cout << "--";
            }
            else if (i == 1) {
                if (hk != "--") cout << hk;
                else cout << "--";
            }
            else if (i == 2) {
                if (nhom != "--") cout << nhom;
                else cout << "--";
            }
            else if (i == 3) {
                if (ma != "--") cout << ma;
                else cout << "--";
            }
            SetColor(7);
        }
        else {
            cout << text[i];
            if (i == 0) {
                if (nk != "--") cout << nk;
                else cout << "--";
            }
            else if (i == 1) {
                if (hk != "--") cout << hk;
                else cout << "--";
            }
            else if (i == 2) {
                if (nhom != "--") cout << nhom;
                else cout << "--";
            }
            else if (i == 3) {
                if (ma != "--") cout << ma;
                else cout << "--";
            }
        }
    }
    gotoXY(30, 26);
    SetColor(12);
    cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
    SetColor(7);
    while (true) {
        if (_kbhit()) {
            gotoXY(30, 26);
            SetColor(12);
            cout << "DUNG MUI TEN LEN XUONG DE DIEU KIEN. AN ENTER DE CHON. AN ESC DE THOAT";
            SetColor(7);
            char key = _getch();  // L?y k? t? ngu?i d?ng nh?n
            if (key == 72) {  // Mui t?n l?n
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui t?n xu?ng
                if (viTriChon < 14) {
                    viTriChon += 2;
                    HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
                if (viTriChon == 14) {
                    if (input == 2) hienThiDanhSachSV_LTC_TheoThamSo(dsltc, dsLop, ma, hk, nhom, nk, root);
                    else {
                        Nhap_Bang_Diem(dsltc, nk, hk, nhom, ma, dsLop, input, root);
                        return;
                    }
                }
                else {
                    int ok = -1;
                    gotoXY(30, 26); cout << "                                                                          ";
                    gotoXY(30, 26); cout << "NHAP PHIM '|' DE HUY LENH NHAP";
                    if (viTriChon == 6) Nhap_nk_in_ds_svdk(nk, viTriChon);
                    else if (viTriChon == 8) Nhap_hk_in_ds_svdk(hk, viTriChon);
                    else if (viTriChon == 10) Nhap_nhom_in_ds_svdk(nhom, viTriChon);
                    else if (viTriChon == 12) Nhap_mamh_in_ds_svdk(ma, viTriChon, root);
                    if (nk == "--") ok = 6;
                    else if (hk == "--") ok = 8;
                    else if (nhom == "--") ok = 10;
                    else if (ma == "--") ok = 12;
                    if (ok != -1) {
                        HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, ok, viTriChon, text);
                        viTriChon = ok;
                    }
                    else {
                        ok = viTriChon;
                        viTriChon = 14;
                        HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, ok, text);
                    }
                }
            }
            else if (key == 27) {  // Nh?n ESC d? tho?t
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}

void SVDK_LTC(DS_LOPSV& dsLop, List_LTC& dsltc, treeMH& root) {
    system("cls");
    boxDefault(xD, yD, wD, hD, tD, "SINH VIEN DANG KY LOP TIN CHI"); // box l?n nh?t
    boxVuong(35, 3, 80, 22, 15); // box l?n b?n ph?i
    string text[] = { "DANG KY LTC", "IN DSSVDDK", "DANH SACH LTC", "THOAT" };
    while (1) {
        box_huong_dan_menu();
        int luaChon = thanhSangListBox(xL, yL, wL, hL, 11, 14, text, 4);
        switch (luaChon) {
        case 0:
            DangKyLopTinChi(dsltc, dsLop, root);
            break;
        case 1:
            Indssvdkltc(dsltc, dsLop, root);
            break;
        case 2:
            hienThiDanhSachLopTinChi(dsltc);
            break;
        case 3:
            if (xacNhanThoat()) {
                xoa_noi_dung_khung();
                return;
            }
            break;
        }
    }
}



float Tinh_Diem_TB(string masv, List_LTC& dsltc, treeMH& root) {
    float tongdiem = 0;
    int tongtinchi = 0;
    if (dsltc.n == 0) {
        return 0.0;
    }
    for (int i = 1; i <= dsltc.n; i++) {
        PTRDK svdk = dsltc.nodes[i]->dssvdk;
        while (svdk != NULL) {
            if (svdk->dk.MASV == masv && svdk->dk.DIEM != -1.0) {
                treeMH monhoc = searchMH(root, dsltc.nodes[i]->MAMH);
                int TC = (monhoc->mh.STCLT) + (monhoc->mh.STCTH);
                tongdiem += (svdk->dk.DIEM) * TC;
                tongtinchi += TC;
            }
            svdk = svdk->next;
        }
    }
    if (tongtinchi == 0) return 0.0;
    return round((1.0 * tongdiem / tongtinchi) * 10) / 10;
}

void In_DTB_1_Lop_2(List_LTC& dsltc, treeMH& root, DS_LOPSV& dsLop, string malop, LopSV Lop) {
    system("cls");
    SetColor(7);
    if (Lop.First == NULL) {
        cout << "Danh sach sinh vien trong lop rong!\n";
    }
    cout << "===================BANG DIEM TRUNG BINH KHOA HOC==================\n";
    cout << "                          Lop:  " << malop << "                         ";
    cout << "\n==================================================================";
    cout << endl;
    int i = 1;
    PTRSV sv_node = Lop.First;
    gotoXY(3, 3); cout << "STT";
    gotoXY(10, 3); cout << "| MASV";
    gotoXY(21, 3); cout << "| HO";
    gotoXY(40, 3); cout << "| TEN";
    gotoXY(51, 3); cout << "| DIEM" << endl;
    while (sv_node != NULL) {
        SinhVien SV = sv_node->sv;
        gotoXY(3, i + 3); cout << i;
        gotoXY(10, i + 3); cout << "| " << SV.MASV;
        gotoXY(21, i + 3); cout << "| " << SV.HO;
        gotoXY(40, i + 3); cout << "| " << SV.TEN;
        gotoXY(51, i + 3); cout << "| ";
        cout << fixed << setprecision(1) << Tinh_Diem_TB(SV.MASV, dsltc, root) << endl;
        i++;
        sv_node = sv_node->next;
    }
    SetColor(4);
    HideCursor();
    cout << "An phim ESC de thoat!\n";
    SetColor(7);
    while (1) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 27) {  // Nh?n ESC d? tho?t
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}

void In_DTB_1_Lop_1(List_LTC& dsltc, treeMH& root, DS_LOPSV& dsLop) {
    if (dsLop.n == 0) {
        cout << "Khong co lop nao de in diem!\n";
        return;
    }
    string malop;
    int viTri;
    do {
        gotoXY(40, 5);
        cout << "Nhap ma lop muon in(An phim '|' de thoat): ";
        getline(cin, malop);
        if (malop == "|") {
            xoa_noi_dung_khung();
            return;
        }
        viTri = Tim_viTri_Lop(dsLop, malop);
        if (viTri != -1) {
            break;
        }
        cout << "Khong ton tai ma lop tren!\n";
    } while (1);
    In_DTB_1_Lop_2(dsltc, root, dsLop, malop, dsLop.nodes[viTri]);
}

void Nhap_In_Diem(List_LTC& dsltc, treeMH& root, DS_LOPSV& dsLop) {
    if (dsltc.n == 0) {
        cout << "Khong ton tai lop tin chi nao de nhap diem!\n";
        return;
    }
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "MENU NHAP-IN DIEM SINH VIEN");
        boxVuong(35, 3, 80, 22, 15);
        string text[] = { "Nhap diem", "In bang diem cua 1 LTC", "In DTB KT khoa hoc", "Bang DTK mon cua 1SV", "Thoat" };
        box_huong_dan_menu();
        int luachon = thanhSangListBox(xL, yL, wL, hL, 11, 14, text, 5);
        switch (luachon) {
        case 0:
            Indssvdkltc(dsltc, dsLop, root, 0);
            break;
        case 1:
            Indssvdkltc(dsltc, dsLop, root, 1);
            break;
        case 2:
            In_DTB_1_Lop_1(dsltc, root, dsLop);
            break;
        case 3:
            break;
        case 4:
            if (xacNhanThoat()) {
                system("cls");
                return;
            }
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    }
}

int main() {
    DS_LOPSV dsLop;
    List_LTC dsltc;
    treeMH root = NULL;

    ifstream nhapfile;
    nhapfile.open("C:\\Users\\admin\\Downloads\\C++\\docfile.txt");
    int n;
    string ma, ten;
    int lt, th;
    nhapfile >> n;
    nhapfile.ignore();
    for (int i = 0; i < n; i++) {
        getline(nhapfile, ma, ',');
        getline(nhapfile, ten, ',');
        nhapfile >> lt;
        nhapfile.ignore();
        nhapfile >> th;
        nhapfile.ignore();
        root = insertMH(root, { ma, ten, lt, th });
    }
    nhapfile >> n;
    nhapfile.ignore();
    LopSV lop;
    for (int i = 0; i < n; i++) {
        getline(nhapfile, lop.MALOP, ',');
        getline(nhapfile, lop.TENLOP);
        lop.First = nullptr; // Gi? d?nh kh?ng c? sinh vi?n c? th? li?n k?t
        dsLop.nodes[dsLop.n++] = lop;
    }
    int k;
    nhapfile >> k;
    nhapfile.ignore();
    for (int i = 0; i < k; i++) {
        nhapfile >> n;
        nhapfile.ignore();
        string ho, phai, sdt;
        for (int j = 0; j < n; j++) {
            getline(nhapfile, ho, ',');
            getline(nhapfile, ten, ',');
            getline(nhapfile, ma, ',');
            getline(nhapfile, phai, ',');
            getline(nhapfile, sdt);
            tao_sv(dsLop.nodes[i], { ma, ho, ten, phai, sdt });
        }
    }
    nhapfile >> n;
    nhapfile.ignore();
    for (int i = 0; i < n; i++) {
        LopTinChi* newLTC = new LopTinChi();
        if (dsltc.n == 0) newLTC->MALOPTC = 1;
        else newLTC->MALOPTC = dsltc.nodes[dsltc.n]->MALOPTC + 1;
        getline(nhapfile, newLTC->MAMH, ',');
        getline(nhapfile, newLTC->NienKhoa, ',');
        nhapfile >> newLTC->Hocky;
        nhapfile.ignore();
        nhapfile >> newLTC->Nhom;
        nhapfile.ignore();
        nhapfile >> newLTC->sosvmin;
        nhapfile.ignore();
        nhapfile >> newLTC->sosvmax;
        nhapfile.ignore();
        newLTC->huylop = false;
        dsltc.nodes[++dsltc.n] = newLTC;
    }
    nhapfile >> k;
    nhapfile.ignore();
    for (int i = 1; i <= k; i++) {
        nhapfile >> n;
        nhapfile.ignore();
        for (int j = 0; j < n; j++) {
            PTRDK newdkltc = new nodeDK;
            getline(nhapfile, newdkltc->dk.MASV, ',');
            newdkltc->dk.huydangky = false;
            newdkltc->next = dsltc.nodes[i]->dssvdk;
            dsltc.nodes[i]->dssvdk = newdkltc;
        }
    }
    nhapfile.close();
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "MENU QUAN LY DIEM SINH VIEN THEO HE TIN CHI");
        boxVuong(35, 3, 80, 22, 7);
        string text[] = { "Lop Tin Chi", "Nhap lop - Nhap SV", "Nhap mon hoc", "Sinh vien DKLTC", "Nhap-In Diem sinh vien", "Thoat chuong trinh" };
        box_huong_dan_menu();
        int luachon = thanhSangListBox(xL, yL, wL, hL, 7, 14, text, 6);
        switch (luachon) {
        case 0:
            MoLopTinChi(dsltc, root);
            break;
        case 1:
            hienThiMenuChinh(dsLop);
            break;
        case 2:
            NhapMonHoc(root, dsltc);
            break;
        case 3:
            SVDK_LTC(dsLop, dsltc, root);
            break;
        case 4:
            Nhap_In_Diem(dsltc, root, dsLop);
            break;
        case 5:
            if (xacNhanThoat()) {
                system("cls");
                return 0;
            }
            break;
        }
    }
    return 0;
}
