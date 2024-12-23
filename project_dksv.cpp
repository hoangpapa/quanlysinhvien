#include <iostream>
#include <cstring>  // Su dung thu vien string
#include <cctype>  // Thu vi?n h? tr? ki?m tra k� t?
#include <sstream>
#include "mylib.h"
#include "console.h"
#include <math.h>
#include <iomanip>
//#include <bits/stdc++.h>

using namespace std;
const int MAXLOPSV = 10000;
const int MAX_LTC = 10000;   // S? lu?ng l?p t�n ch? t?i da


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
    PTRSV First = NULL;
};


// Ki?m tra m� l?p t�n ch? d� t?n t?i chua
bool kiemTraMaLopTinChi(List_LTC& dsltc, int MALOPTC) {
    for (int i = 0; i < dsltc.n; i++) {
        if (dsltc.nodes[i]->MALOPTC == MALOPTC) {
            return true; // M� l?p t�n ch? d� t?n t?i
        }
    }
    return false; // M� l?p t�n ch? kh�ng t?n t?i
}

// Ki?m tra ni�n kh�a c� h?p l? hay kh�ng (nam k?t th�c kh�     ng qu� 1 nam so v?i nam b?t d?u)
bool kiemTraNienKhoa(string& nienKhoa) {
    if (nienKhoa.length() != 9) return false;  // �? d�i ph?i l� 9 k� t? (VD: 2024-2025)
    if (nienKhoa[4] != '-') return false;      // K� t? th? 5 ph?i l� d?u '-'

    // L?y nam b?t d?u v� nam k?t th�c t? chu?i
    string namBatDauStr = nienKhoa.substr(0, 4);      // L?y 4 k� t? d?u ti�n
    string namKetThucStr = nienKhoa.substr(5, 4);     // L?y 4 k� t? cu?i c�ng
    int namBatDau = stoi(namBatDauStr);               // Chuy?n th�nh s? nguy�n
    int namKetThuc = stoi(namKetThucStr);             // Chuy?n th�nh s? nguy�n

    // Ki?m tra xem nam k?t th�c c� l?n hon nam b?t d?u, nhung kh�ng qu� 1 nam
    if (namKetThuc != namBatDau + 1) {
        return false;
    }
    return true;
}

// H�m ki?m tra chu?i c� h?p l? kh�ng (ch? ch?a k� t? s?)
bool kiemTraChuoiSo(string& input) {
    for (auto c : input) {
        if (!isdigit(c)) {  // Ki?m tra t?ng k� t? c� ph?i l� s? kh�ng
            return false;
        }
    }
    return true;
}

// H�m nh?p chu?i v� ki?m tra t�nh h?p l?
string nhapChuoiSo(string thongBao) {
    string input;
    cout << thongBao;
    getline(cin, input);
    return input;
}

string nhapChuoiSo_2(string thongBao) {
    string input;
    do {
        cout << thongBao;
        cin >> input;
        if (input == "|") return input;
        if (!kiemTraChuoiSo(input)) {
            cout << "Loi: Vui long nhap chi so nguyen hop le.\n";
        }
        else {
            return input;  // Tr? v? chu?i h?p l? n?u t?t c? c�c k� t? l� s?
        }
    } while (true);
}

// Hien thi bang lop tin chi hien co
void hienThiDanhSachLopTinChi(List_LTC& dsltc) {
    if (dsltc.n == 0) {
        cout << "Danh sach lop tin chi rong.\n";
        return;
    }
    cout << "\n===== DANH SACH LOP TIN CHI =====\n";
    cout << "STT\tMaLopTC\tMaMH\tNienKhoa\tHocKy\tNhom\tSV Min\tSV Max\n";
    for (int i = 1; i <= dsltc.n; i++) {
        cout << i << "\t"
            << dsltc.nodes[i]->MALOPTC << "\t"
            << dsltc.nodes[i]->MAMH << "\t"
            << dsltc.nodes[i]->NienKhoa << "\t"
            << dsltc.nodes[i]->Hocky << "\t"
            << dsltc.nodes[i]->Nhom << "\t"
            << dsltc.nodes[i]->sosvmin << "\t"
            << dsltc.nodes[i]->sosvmax << endl;
    }
}


bool check(string s) {
    if (s.size() > 50) {
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

// Hàm tìm kiếm môn học theo mã
treeMH searchMH(treeMH root, const string& mamh) {
    if (root == NULL) return NULL;
    if (root->mh.MAMH == mamh) return root;
    if (root->mh.MAMH > mamh) return searchMH(root->left, mamh);
    return searchMH(root->right, mamh);
}

// Hàm kiểm tra mã môn học đã tồn tại chưa
bool isDuplicateMH(treeMH root, const string& mamh) {
    return searchMH(root, mamh) != NULL;
}

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
//void drawListBoxLTC(int x, int y, int w, int h, List_LTC& dsltc, int soTrang, int chonHang, int soDongMoiTrang, const string tieuDe[], int ntieuDe) {
//    int khoangCachMoiCot[] = { w * 0.07, w * 0.2, w * 0.18, w * 0.15, w * 0.15, w * 0.1, w * 0.1, w * 0.1 };
//    gotoXY(x, y);
//    printf("%-*s", khoangCachMoiCot[0], "STT");
//    for (int i = 0; i < ntieuDe; i++) {
//        printf("%-*s", khoangCachMoiCot[i + 1], tieuDe[i].c_str());
//    }
//    cout << endl;
//
//    int start = soTrang * soDongMoiTrang;
//    int end = min(start + soDongMoiTrang, dsltc.n);
//
//    for (int i = start; i < end; i++) {
//        gotoXY(x, y + 1 + (i - start));
//        if (i == chonHang) {
//            textcolor(200);
//            SetColor(0);
//        }
//        printf("%-*d", khoangCachMoiCot[0], i + 1);
//        printf("%-*d", khoangCachMoiCot[1], dsltc.nodes[i]->MALOPTC);
//        printf("%-*s", khoangCachMoiCot[2], dsltc.nodes[i]->MAMH.c_str());
//        printf("%-*d", khoangCachMoiCot[3], dsltc.nodes[i]->NienKhoa);
//        printf("%-*d", khoangCachMoiCot[4], dsltc.nodes[i]->Hocky);
//        printf("%-*d", khoangCachMoiCot[5], dsltc.nodes[i]->Nhom);
//        printf("%-*d", khoangCachMoiCot[6], dsltc.nodes[i]->sosvmin);
//        printf("%-*d", khoangCachMoiCot[7], dsltc.nodes[i]->sosvmax);
//
//        if (i == chonHang) {
//            textcolor(7);
//        }
//        cout << endl;
//    }
//}
//
//int listBoxLTC(List_LTC& dsltc, const string tieuDe[], int ntieuDe) {
//    int totalRows = dsltc.n;
//    int sttOfTrang = 0;
//    int hangNgangdangChon = 0;
//    int soDongMoiTrang = 10; // Số dòng hiển thị mỗi trang
//    ShowCur(false);
//
//    while (true) {
//        drawListBoxLTC(xLB, yLB, wLB, hLB, dsltc, sttOfTrang, hangNgangdangChon, soDongMoiTrang, tieuDe, ntieuDe);
//
//        int key = _getch();
//        if (key == KEY_UP) {
//            if (hangNgangdangChon > 0) {
//                hangNgangdangChon--;
//                if (hangNgangdangChon < sttOfTrang * soDongMoiTrang) {
//                    sttOfTrang--;
//                }
//            }
//        }
//        else if (key == KEY_DOWN) {
//            if (hangNgangdangChon < totalRows - 1) {
//                hangNgangdangChon++;
//                if (hangNgangdangChon >= (sttOfTrang + 1) * soDongMoiTrang) {
//                    sttOfTrang++;
//                    xoa_noi_dung_khung();
//                }
//            }
//        }
//        else if (key == KEY_ENTER) {
//            ShowCur(true);
//            return hangNgangdangChon;
//        }
//        else if (key == KEY_ESC) {
//            ShowCur(true);
//            return -1;
//        }
//    }
//}

// Xoa lop tin chi (hien thi danh sach lop tin chi truoc khi xoa) 
//void xoaLopTinChi(List_LTC& dsltc) {
   /* hienThiDanhSachLopTinChi(dsltc); */
    //int nTieuDe = 7;
    //string tieuDe[] = { "MaLopTC", "MaMH", "NienKhoa", "HocKy", "Nhom", "SVMIN", "SVMAX" };
    //listBoxLTC(dsltc, tieuDe, nTieuDe);
    //if (dsltc.n == 0) return;
    //int ok = 1;
    //do {
    //    string input = nhapChuoiSo("Nhap ma lop tin chi muon xoa (An phim '|' de quay lai): ");
    //    if (input == "|") return;
    //    int MALOPTC = stoi(input);  // Chuyen chuoi thanh so
    //    int i = TimLTC(MALOPTC, dsltc);
    //    if (i == -1) {
    //        cout << "Khong tim thay lop tin chi de xoa.\n";
    //    }
    //    else {
    //        if (dsltc.nodes[i]->dssvdk != NULL) {
    //            cout << "Da co sv dk ltc nay - ko the xoa!\n";
    //        }
    //        else {
    //            char confirm;
    //            do {
    //                cout << "Ban co chac muon xoa lop tin chi nay khong? (y/n): ";
    //                cin >> confirm;
    //                cin.ignore();
    //                if (confirm == 'y' || confirm == 'Y') {
    //                    ok = 0;
    //                    delete dsltc.nodes[i];
    //                    for (int j = i; j <= dsltc.n - 1; j++) {
    //                        dsltc.nodes[j] = dsltc.nodes[j + 1];
    //                    }
    //                    dsltc.n--;
    //                    cout << "Lop tin chi da duoc xoa thanh cong.\n";
    //                    break;
    //                }
    //                else if (confirm == 'n' || confirm == 'N') {
    //                    cout << "Da huy thao tac xoa!!!\n";
    //                    break;
    //                }
    //                else {
    //                    cout << "Vui long nhap dung cu phap!\n";
    //                }
    //            } while (1);
    //        }
    //    }
    //} while (ok);
//}


void generateFakeLTCData(List_LTC& dsltc, int numberOfRecords) {
    for (int i = 1; i < numberOfRecords; i++) {
        if (dsltc.n >= MAX_LTC) {
            cout << "Danh sach Lop Tin Chi da day!" << endl;
            return;
        }

        LopTinChi* newLTC = new LopTinChi();
        newLTC->MALOPTC = 1000 + i;                // Mã lớp tín chỉ tăng dần
        newLTC->MAMH = "MH" + to_string(i + 1);    // Mã môn học là MH1, MH2,...
        newLTC->NienKhoa = "2022-2023";// Niên khóa như 2020-2021
        newLTC->Hocky =  1;               // Học kỳ 1 hoặc 2
        newLTC->Nhom = (i % 3) + 1;                // Nhóm 1, 2 hoặc 3
        newLTC->sosvmin = 10 + (i % 5);            // Số SV tối thiểu: 10, 11, 12,...
        newLTC->sosvmax = newLTC->sosvmin + 10;    // Số SV tối đa lớn hơn tối thiểu 10
        newLTC->huylop = false;                    // Mặc định lớp không bị hủy
        dsltc.nodes[dsltc.n++] = newLTC;           // Thêm lớp tín chỉ vào danh sách
    }
}
void xoaMonHoc(List_LTC& dsltc, int index) {


    // Giải phóng bộ nhớ nếu dùng con trỏ
    delete dsltc.nodes[index];

    // Dịch các phần tử còn lại trong danh sách
    for (int i = index; i < dsltc.n - 1; i++) {
        dsltc.nodes[i] = dsltc.nodes[i + 1];
    }

    // Giảm số lượng phần tử
    dsltc.n--;

    cout << "Da xoa mon hoc  " << endl;
}

void drawListBoxLTC(int x, int y, int w, int h, List_LTC& dsltc, int soTrang, int chonHang, int soDongMoiTrang, const string tieuDe[], int ntieuDe) {
    int khoangCachMoiCot[] = { w * 0.07, w * 0.2, w * 0.18, w * 0.15, w * 0.15, w * 0.1, w * 0.1, w * 0.1 };
    gotoXY(x, y);
    printf("%-*s", khoangCachMoiCot[0], "STT");
    for (int i = 0; i < ntieuDe; i++) {
        printf("%-*s", khoangCachMoiCot[i + 1], tieuDe[i].c_str());
    }
    cout << endl;
    int k = 0;
    int start = soTrang * soDongMoiTrang;
    int end = min(start + soDongMoiTrang, dsltc.n);

    for (int i = start + 1; i < end; i++) {
        gotoXY(x, y + 1 + (i - start + 1));
        if (i == chonHang) {
            textcolor(200);
            SetColor(0);

        }
        printf("%-*d", khoangCachMoiCot[0], k + 1);
        printf("%-*d", khoangCachMoiCot[1], dsltc.nodes[i]->MALOPTC);
        printf("%-*s", khoangCachMoiCot[2], dsltc.nodes[i]->MAMH.c_str());
        printf("%-*d", khoangCachMoiCot[3], dsltc.nodes[i]->NienKhoa.c_str());
        printf("%-*d", khoangCachMoiCot[4], dsltc.nodes[i]->Hocky);
        printf("%-*d", khoangCachMoiCot[5], dsltc.nodes[i]->Nhom);
        printf("%-*d", khoangCachMoiCot[6], dsltc.nodes[i]->sosvmin);
        printf("%-*d", khoangCachMoiCot[7], dsltc.nodes[i]->sosvmax);
        k++;
        if (i == chonHang) {
            textcolor(7);

        }
        cout << endl;
    }
}

int listBoxLTC(List_LTC& dsltc, const string tieuDe[], int ntieuDe) {
    int totalRows = dsltc.n;
    int sttOfTrang = 0;
    int hangNgangdangChon = 0;
    int soDongMoiTrang = 10; // Số dòng hiển thị mỗi trang
    ShowCur(false);

    while (true) {
        drawListBoxLTC(xLB, yLB, wLB, hLB, dsltc, sttOfTrang, hangNgangdangChon, soDongMoiTrang, tieuDe, ntieuDe);

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
            // Xóa môn học tại vị trí được chọn
            xoaMonHoc(dsltc, hangNgangdangChon);

            // Cập nhật lại danh sách
            totalRows = dsltc.n;
            if (hangNgangdangChon >= totalRows) {
                hangNgangdangChon = totalRows - 1; // Di chuyển chọn về dòng cuối cùng
            }
            if (sttOfTrang * soDongMoiTrang >= totalRows) {
                sttOfTrang = max(0, totalRows / soDongMoiTrang - 1);
            }
        }
        else if (key == KEY_ESC) {
            ShowCur(true);
            return -1;
        }
    }
}
void SearchingBar(List_LTC& dsltc) {
    while (true) {
        // Hiển thị thông báo nhập mã lớp tín chỉ
        gotoXY(10, 25);
        string input = nhapChuoiSo("Nhap ma lop tin chi muon xoa (An phim '|' de quay lai): ");

        // Kiểm tra nếu người dùng muốn thoát
        if (input == "|") {
            cout << "Huy bo thao tac xoa.\n";
            return; // Thoát khỏi hàm
        }

        // Chuyển chuỗi nhập vào thành số
        int MALOPTC;

        MALOPTC = stoi(input);

        int i = TimLTC(MALOPTC, dsltc);
        if (i == -1) {
            cout << "Khong tim thay lop tin chi de xoa.\n";
        }
        else {
            // Kiểm tra nếu lớp tín chỉ đã có sinh viên đăng ký
            if (dsltc.nodes[i]->dssvdk != NULL) {
                cout << "Da co sinh vien dang ky lop tin chi nay - Khong the xoa!\n";
            }
            else {
                // Yêu cầu xác nhận trước khi xóa
                cout << "Ban co chac chan muon xoa lop tin chi nay? (Nhan Enter de xoa, ESC de huy)\n";
                int key = _getch();
                if (key == KEY_ENTER) {
                    xoaMonHoc(dsltc, i);
                    cout << "Lop tin chi da duoc xoa thanh cong.\n";
                    return; // Thoát khỏi hàm sau khi xóa thành công
                }
                else if (key == KEY_ESC) {
                    cout << "Huy bo thao tac xoa.\n";
                    return; // Thoát khỏi hàm khi hủy
                }
            }
        }
    }
}

// Xoa lop tin chi (hien thi danh sach lop tin chi truoc khi xoa) 
void xoaLopTinChi(List_LTC& dsltc) {
    generateFakeLTCData(dsltc, 10);

    /* hienThiDanhSachLopTinChi(dsltc); */
    int nTieuDe = 7;
    string tieuDe[] = { "MaLopTC", "MaMH", "NienKhoa", "HocKy", "Nhom", "SVMIN", "SVMAX" };
    listBoxLTC(dsltc, tieuDe, nTieuDe);

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

void Nhap_ma_mon_hoc_ltc(LopTinChi& ltc, int viTriChon, treeMH& root) {
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

void Nhap_nien_khoa_ltc(LopTinChi& ltc, int viTriChon) {
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

void Nhap_hoc_ki_ltc(LopTinChi& ltc, int viTriChon) {
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

void Nhap_nhom_ltc(LopTinChi& ltc, int viTriChon) {
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

void Nhap_sosvmin_ltc(LopTinChi& ltc, int viTriChon) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                             ";
        gotoXY(40, viTriChon);
        cout << "NHAP SO SINH VIEN TOI THIEU: ";
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

void Nhap_sosvmax_ltc(LopTinChi& ltc, int viTriChon) {
    do {
        SetColor(4);
        gotoXY(40, viTriChon);
        cout << "                                             ";
        gotoXY(40, viTriChon);
        cout << "NHAP SO SINH VIEN TOI DA: ";
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

// Them lop tin chi (co nut quay lai)
void themLopTinChi(List_LTC& dsltc, treeMH root) {
    HideCursor();
    LopTinChi ltc;
    xoa_noi_dung_khung();
    gotoXY(65, 4);
    SetColor(9);
    cout << "THEM LOP TIN CHI";
    SetColor(7);
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
            char key = _getch();  // L?y k? t? ngu?i dùng nh?n
            if (key == 72) {  // Mui tên lên
                if (viTriChon > 8) {
                    viTriChon -= 2;
                    HienThi_Them_ltc(ltc, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui tên xu?ng
                if (viTriChon < 20) {
                    viTriChon += 2;
                    HienThi_Them_ltc(ltc, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap diem
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
                                themLopTinChi(dsltc, root);
                                return;
                            }
                        }
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
                    int ok = -1;
                    if (viTriChon == 8) Nhap_ma_mon_hoc_ltc(ltc, viTriChon, root);
                    else if (viTriChon == 10) Nhap_nien_khoa_ltc(ltc, viTriChon);
                    else if (viTriChon == 12) Nhap_hoc_ki_ltc(ltc, viTriChon);
                    else if (viTriChon == 14) Nhap_nhom_ltc(ltc, viTriChon);
                    else if (viTriChon == 16) Nhap_sosvmin_ltc(ltc, viTriChon);
                    else if (viTriChon == 18) Nhap_sosvmax_ltc(ltc, viTriChon);
                    //======
                    if (ltc.MAMH == "--") ok = 8;
                    else if (ltc.NienKhoa == "--") ok = 10;
                    else if (ltc.Hocky == -1) ok = 12;
                    else if (ltc.Nhom == -1) ok = 14;
                    else if (ltc.sosvmin == -1) ok = 16;
                    else if (ltc.sosvmax == -1) ok = 18;
                    if (ok != -1) {
                        HienThi_Them_ltc(ltc, ok, viTriChon, text);
                        viTriChon = ok;
                    }
                    else {
                        ok = viTriChon;
                        viTriChon = 20;
                        HienThi_Them_ltc(ltc, viTriChon, ok, text);
                    }
                }
            }
            else if (key == 27) {  // Nh?n ESC d? thoát
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}

// Hi?u ch?nh l?p t�n ch?
void suaLopTinChi(List_LTC& dsltc, treeMH& root) {
    hienThiDanhSachLopTinChi(dsltc);  
    if (dsltc.n == 0) return;
    int ok = 1;
    do {
        string input = nhapChuoiSo_2("Nhap ma lop tin chi can sua (An phim '|' de quay lai): ");
        if (input == "|") return;
        int MALOPTC = stoi(input);
        int i = TimLTC(MALOPTC, dsltc);
        if (i == -1) {
            cout << "Khong tim thay lop tin chi de sua.\n";
        }
        else {
            int luaChonSua;
            do {
                cout << "Chon thong tin can sua:\n";
                cout << "1. Ma mon hoc\n";
                cout << "2. Nien khoa\n";
                cout << "3. Hoc ky\n";
                cout << "4. Nhom\n";
                cout << "5. So sinh vien toi thieu\n";
                cout << "6. So sinh vien toi da\n";
                cout << "7. Thoat\n";
                cout << "Nhap lua chon: ";
                cin >> luaChonSua;

                switch (luaChonSua) {
                case 1:
                    cin.ignore();
                    do {
                        cout << "Nhap ma mon hoc moi(An phim '|' de thoat): ";
                        getline(cin, input);
                        if (input == "|") {
                            break;
                        }
                        if (isDuplicateMH(root, input)) {
                            dsltc.nodes[i]->MAMH = input;
                            cout << "Cap nhat ma mon hoc moi thanh cong!\n";
                            break;
                        }
                        cout << "Khong ton tai ma mon hoc nay!!!\n";
                    } while (1);
                    break;
                case 2:
                    cin.ignore();
                    do {
                        cout << "Nhap nien khoa moi (dinh dang YYYY-YYYY)(An phim '|' de thoat): ";
                        getline(cin, input);
                        if (input == "|") {
                            cout << "Da thoat!\n";
                            break;
                        }
                        if (kiemTraNienKhoa(dsltc.nodes[i]->NienKhoa)) {
                            dsltc.nodes[i]->NienKhoa = input;
                            cout << "Cap nhap nien khoa moi thanh cong!\n";
                            break;
                        }
                        cout << "Loi: Nien khoa khong hop le. Vui long nhap lai.\n";
                    } while (1);
                    break;
                case 3:
                    cin.ignore();
                    do {
                        cout << "Nhap hoc ky moi(An phim '|' de thoat): ";
                        getline(cin, input);
                        if (input == "|") {
                            cout << "Da thoat!\n";
                            break;
                        }
                        if (kiemTraChuoiSo(input)) {
                            dsltc.nodes[i]->Hocky = stoi(input);
                            cout << "Cap nhat hoc ky moi thanh cong!\n";
                            break;
                        }
                        cout << "Hoc ky moi la so nguyen duong!!!\n";
                    } while (1);
                    break;
                case 4:
                    cin.ignore();
                    do {
                        cout << "Nhap nhom moi(An phim '|' de thoat): ";
                        getline(cin, input);
                        if (input == "|") {
                            cout << "Da thoat!\n";
                            break;
                        }
                        if (kiemTraChuoiSo(input)) {
                            dsltc.nodes[i]->Nhom = stoi(input);
                            cout << "Cap nhat nhom moi thanh cong!\n";
                            break;
                        }
                        cout << "Nhom moi la so nguyen duong!!!\n";
                    } while (1);
                    break;
                case 5:
                    cin.ignore();
                    do {
                        cout << "Nhap so sinh vien toi thieu moi(An phim '|' de thoat): ";
                        getline(cin, input);
                        if (input == "|") {
                            cout << "Da thoat!\n";
                            break;
                        }
                        if (kiemTraChuoiSo(input) && stoi(input) <= dsltc.nodes[i]->sosvmax) {
                            dsltc.nodes[i]->sosvmin = stoi(input);
                            cout << "Da cap nhat so sv min moi thanh cong!\n";
                            break;
                        }
                        if (stoi(input) > dsltc.nodes[i]->sosvmax)
                            cout << "So sv min ko duoc lon hon so sv max\n";
                        else cout << "So sinh vien toi thieu moi la so nguyen duong!!!\n";
                    } while (1);
                    break;
                case 6:
                    cin.ignore();
                    do {
                        cout << "Nhap so sinh vien toi da moi(An phim '|' de thoat): ";
                        getline(cin, input);
                        if (input == "|") {
                            cout << "Da thoat!\n";
                            break;
                        }
                        if (kiemTraChuoiSo(input) && stoi(input) >= dsltc.nodes[i]->sosvmin) {
                            dsltc.nodes[i]->sosvmax = stoi(input);
                            cout << "Da cap nhat so sv max moi thanh cong!\n";
                            break;
                        }
                        if (stoi(input) < dsltc.nodes[i]->sosvmax)
                            cout << "So sv max ko duoc nho hon so sv min\n";
                        else cout << "So sinh vien toi da moi la so nguyen duong!!!\n";
                    } while (1);
                    break;
                case 7:
                    cout << "Thoat chinh sua.\n";
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                }
            } while (luaChonSua != 7);
            ok = 0;
            return;
        }
    } while (ok);
}
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
void inDanhSachSinhVien(List_LTC& dsltc) {
    if (dsltc.First == NULL) {
        cout << "Danh sach sinh vien trong lop rong.\n";
        return;
    }
    cout << "Danh sach sinh vien:\n";
    PTRSV p = dsltc.First;
    while (p != NULL) {
        inThongTinSV(p->sv);
        p = p->next;
    }
}
void huyLTC(List_LTC& dsltc) {
    if (dsltc.n == 0) {
        cout << "Danh sach lop tin chi rong!\n";
        return;
    }
    bool ok = 1;
    LopTinChi* LTC_tmp;
    for (int i = 1; i <= dsltc.n; i++) {
        LTC_tmp = dsltc.nodes[i];
        int So_SV_DK = DemSoSinhVien(LTC_tmp->dssvdk);
        if (So_SV_DK < LTC_tmp->sosvmin && LTC_tmp->huylop == false) {
            if (ok == 1) {
                cout << "----DANH SACH LOP TIN CHI DU DIEU KIEN DE HUY----\n";
                cout << "Ma LTC\tMa MH\tNien Khoa\tHoc Ky\tNhom\tSo SV Min\tSo SV Max\tSo SV Da DK\n";
                ok = 0;
            }
            cout << LTC_tmp->MALOPTC << "\t" << LTC_tmp->MAMH << "\t" << LTC_tmp->NienKhoa
                << "\t" << LTC_tmp->Hocky << "\t" << LTC_tmp->Nhom << "\t" << LTC_tmp->sosvmin
                << "\t\t" << LTC_tmp->sosvmax << "\t\t" << So_SV_DK << endl;
        }
    }
    if (ok == 1) {
        cout << "Khong co lop tin chi nao du dieu kien de huy!\n";
        return;
    }
    string input;
    do {
        do {
            cout << "Nhap ma lop tin chi muon huy(An phim '|' de thoat): ";
            getline(cin, input);
            if (input == "|") {
                cout << "Da thoat!\n";
                return;
            }
            if (kiemTraChuoiSo(input)) break;
            else cout << "Ma lop tin chi la so nguyen duong!\n";
        } while (1);
        for (int i = 1; i <= dsltc.n; i++) {
            LTC_tmp = dsltc.nodes[i];
            if (LTC_tmp->MALOPTC == stoi(input) && DemSoSinhVien(LTC_tmp->dssvdk) < LTC_tmp->sosvmin && LTC_tmp->huylop == false) {
                do {
                    cout << "Ban co that su muon huy lop tin chi nay khong?(y/n): ";
                    getline(cin, input);
                    if (input == "Y" || input == "y") {
                        dsltc.nodes[i]->huylop = true;
                        cout << "Da huy lop tin chi nay!\n";
                        return;
                    }
                    else if (input == "n" || input == "N") {
                        cout << "Da huy thao tac huy lop tin chi nay!\n";
                        return;
                    }
                    else cout << "Vui long nhap lua chon hop le!\n";
                } while (1);
            }
        }
        cout << "Lua chon cua ban khong hop le!\n";
    } while (1);
}


void MoLopTinChi(List_LTC& dsltc, treeMH& root) {
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "Lop Tin Chi");
        boxVuong(35, 3, 80, 22, 15);
        string text[] = { "Them lop tin chi", "Xoa lop tin chi", "Sua lop tin chi", "In danh sach LTC", "Huy lop tin chi ", "Thoat" };
        int luachon = thanhSangListBox(xL, yL, wL, hL, 11, 14, text, 6);
        switch (luachon) {
        case 0:
            themLopTinChi(dsltc, root);
            break;
        case 1:
            xoaLopTinChi(dsltc);
            break;
        case 2:
            suaLopTinChi(dsltc, root);
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

bool timLopSV(DS_LOPSV& dsLopSV, string& maSV) {
    for (int i = 0; i < dsLopSV.n; ++i) {
        SinhVien* a = searchSV(dsLopSV.nodes[i], maSV);
        if (a != NULL) {
            cout << a->MASV << " || " << a->HO << " || " << a->TEN
                << " || " << a->PHAI << " || " << a->SODT << endl;
            return true;
        }
    }
    cout << "Sinh vien khong ton tai!" << endl;
    return false;
}

void InDSSV_LTC(LopTinChi* LTC, DS_LOPSV& dsLop) {
    PTRDK DSSV = LTC->dssvdk;
    while (DSSV != NULL) {
        bool ok = timLopSV(dsLop, DSSV->dk.MASV);
        DSSV = DSSV->next;
    }
}

// H�m in danh s�ch sinh vi�n
void hienThiDanhSachSV_LTC_TheoThamSo(List_LTC& dsltc, DS_LOPSV& dsLop, string MaMonHoc, string HocKy, string Nhom, string NienKhoa) {
    cout << "Danh sach sinh vien da dang ky theo cac tham so:\n";
    cout << "Nien khoa: " << NienKhoa << " Hoc ky: " << HocKy << " Nhom: " << Nhom << "Ma mon hoc: " << MaMonHoc << endl;
    for (int i = 1; i <= dsltc.n; i++) {
        LopTinChi* LTC = dsltc.nodes[i];
        if ((NienKhoa == "--" || NienKhoa == LTC->NienKhoa)
            && (HocKy == "--" || stoi(HocKy) == LTC->Hocky)
            && (Nhom == "--" || stoi(Nhom) == LTC->Nhom)
            && (MaMonHoc == "--" || MaMonHoc == LTC->MAMH)
            ) {
            InDSSV_LTC(LTC, dsLop);
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
                if (key == 27) {  // Nh?n ESC d? thoát
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
    while (true) {
        if (_kbhit()) {
            char key = _getch();  // L?y k? t? ngu?i dùng nh?n
            if (key == 72) {  // Mui tên lên
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui tên xu?ng
                if (viTriChon < 14) {
                    viTriChon += 2;
                    HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
                if (viTriChon == 14) {
                    hienThiDanhSachSV_LTC_TheoThamSo(dsltc, dsLop, ma, hk, nhom, nk);
                }
                else {
                    int ok = -1;
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
            else if (key == 27) {  // Nh?n ESC d? thoát
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}



void drawListBoxLSV(int x, int y, int w, int h, DS_LOPSV& dssv, int soDuLieu, int soTrang, int chonHang, int soDongMoiTrang, const string tieuDe[], int ntieuDe, string& maSV) {
    if (soDuLieu == 0) {
        gotoXY(x, y + 2);
        cout << "Danh sách rỗng!";
        maSV = "-1";
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
        maSV = dssv.nodes[chonHang].MALOP;
    }
    else {
        maSV = "-1";
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
            else if (key == KEY_ENTER) {
                ShowCur(false);
                return maSV;
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
        cout << "Danh sach lop trong.\n";
        return;
    }
    int soTieuDe = 2;
    string text[] = { "Ma Lop","Ten Lop" };
    string maLop = listBoxLSVforIn(dsLop, 20, text, soTieuDe);
    while (true) {
        if (maLop == "-1") {
            xoa_noi_dung_khung2();
            return;
        }
    }
}



// Hàm in danh sách sinh viên
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

// Hàm kiểm tra mã sinh viên đã tồn tại
bool kiemTraMaSVTonTai(LopSV& lop, string MASV) {
    PTRSV p = lop.First;
    while (p != NULL) {
        if (p->sv.MASV == MASV) {
            return true;  // Tồn tại sinh viên với mã này
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

// Hàm thêm sinh viên vào lớp
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

void tao_sv(LopSV& lop, SinhVien& sv) {
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

// Hàm thêm sinh viên vào l?p
void themSinhVien(LopSV& lop) {
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
        if (_kbhit()) {
            char key = _getch();  // L?y k? t? ngu?i dùng nh?n
            if (key == 72) {  // Mui tên lên
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_sv(sv, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui tên xu?ng
                if (viTriChon < 16) {
                    viTriChon += 2;
                    HienThi_Them_sv(sv, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
                if (viTriChon == 16) {
                    int ok = -1;
                    if (sv.MASV == "--") ok = 6;
                    else if (sv.HO == "--") ok = 8;
                    else if (sv.TEN == "--") ok = 10;
                    else if (sv.PHAI == "--") ok = 12;
                    else if (sv.SODT == "--") ok = 14;
                    if (ok == -1) {
                        tao_sv(lop, sv);
                        gotoXY(40, 24);
                        SetColor(10);
                        cout << "Them sinh vien moi thanh cong!";
                        SetColor(7);
                        for (int i = 1; i <= 370000000; i++);
                        gotoXY(40, 24);
                        cout << "                                                      ";
                        themSinhVien(lop);
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
            else if (key == 27) {  // Nh?n ESC d? thoát
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}


// Hàm xóa sinh viên khỏi lớp (in danh sách trước khi nhập mã)
void xoaSinhVien(LopSV& lop) {
    if (lop.First == NULL) {
        cout << "Danh sach sinh vien rong, khong co gi de xoa.\n";
        return;
    }

    // In danh sách sinh viên trước khi xóa
    inDanhSachSinhVien(lop);

    string MASV;
    cout << "Nhap ma sinh vien can xoa: (An phim '|' de thoat) ";
    /*cin.ignore();*/
    getline(cin, MASV);
    if (MASV == "|") {
        cout << "Da tra lai menu!!!\n";
        return;
    }

    PTRSV prev = NULL, curr = lop.First;

    // Tìm sinh viên cần xóa
    while (curr != NULL && curr->sv.MASV != MASV) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << "Khong tim thay sinh vien co ma " << MASV << " trong danh sach.\n";
        return;
    }

    char confirm;
    cout << "Ban co chac chan muon xoa sinh vien co ma " << MASV << "? (y/n): ";
    cin >> confirm;
    if (confirm != 'y' && confirm != 'Y') {
        cout << "Huy xoa sinh vien.\n";
        return;
    }

    // Xóa sinh viên và giải phóng bộ nhớ
    if (prev == NULL) {  // Nếu sinh viên cần xóa là nút đầu tiên
        lop.First = curr->next;
    }
    else {
        prev->next = curr->next;
    }

    delete curr;  // Giải phóng bộ nhớ cho sinh viên vừa xóa
    cout << "Da xoa sinh vien co ma " << MASV << ".\n";
}

// Hàm hiệu chỉnh thông tin sinh viên (in danh sách trước khi nhập mã và kiểm tra lỗi nhập liệu)
void hieuChinhSinhVien(LopSV& lop) {
    if (lop.First == NULL) {
        cout << "Danh sach sinh vien trong lop rong.\n";
        return;
    }

    // In danh sách sinh viên trước khi hiệu chỉnh
    inDanhSachSinhVien(lop);

    string MASV;
    cout << "Nhap ma sinh vien can hieu chinh: (An phim '|' de thoat) ";
    cin.ignore();
    getline(cin, MASV);
    if (MASV == "|") {
        cout << "Da tro lai menu!!!" << endl;
        return;
    }
    PTRSV p = lop.First;

    // Tìm sinh viên cần hiệu chỉnh
    while (p != NULL && p->sv.MASV != MASV) {
        p = p->next;
    }

    if (p == NULL) {
        cout << "Khong tim thay sinh vien co ma " << MASV << " trong danh sach.\n";
        return;
    }

    // Hiệu chỉnh thông tin sinh viên
    string LuaChon;

    do {
        cout << "Chon thong tin can sua:\n";
        cout << "1. Ho sinh vien\n";
        cout << "2. Ten sinh vien\n";
        cout << "3. Gioi tinh sinh vien\n";
        cout << "4. So dien thoai sinh vien\n";
        cout << "5. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> LuaChon;
        cin.ignore();
        if (LuaChon.size() != 1) {
            cout << "Lua chon khong hop le\n";
        }
        else if (LuaChon != "1" && LuaChon != "2" && LuaChon != "3"
            && LuaChon != "4" && LuaChon != "5") {
            cout << "Lua chon khong hop le\n";
        }
        else {
            int input = stoi(LuaChon);
            switch (input) {
            case 1:
            {
                bool ok;
                do {
                    ok = false;
                    cout << "Nhap ho moi: (An phim '0' de thoat) ";
                    cin.ignore();
                    string HoMoi;
                    getline(cin, HoMoi);
                    if (HoMoi == "0") {
                        cout << "Da thoat!!!\n";
                        ok = false;
                    }
                    else {
                        if (!kiemTraTenHo(HoMoi)) {
                            cout << "Loi: Ho chi duoc chua chu cai. Vui long nhap lai!\n";
                            ok = true;
                        }
                        else {
                            p->sv.HO = HoMoi;
                            cout << "Cap nhat thanh cong\n";
                        }
                    }
                } while (ok);
                PTRSV tmp = lop.First;
                if (tmp == p) {
                    lop.First = lop.First->next;
                }
                else {
                    while (tmp->next != p) {
                        tmp = tmp->next;
                    }
                    tmp->next = tmp->next->next;
                }
                if (lop.First == NULL) {
                    lop.First = p;
                }
                else {
                    PTRSV tmp2 = lop.First;
                    PTRSV prev_tmp = NULL;
                    while (tmp2 != NULL) {
                        if (tmp->sv.TEN < p->sv.TEN) {
                            prev_tmp = tmp2;
                            tmp2 = tmp2->next;
                        }
                        else if (tmp2->sv.TEN == p->sv.TEN) {
                            if (tmp2->sv.HO < p->sv.HO) {
                                prev_tmp = tmp2;
                                tmp2 = tmp2->next;
                            }
                        }
                        else break;
                    }
                    if (prev_tmp != NULL) {
                        p->next = tmp;
                        prev_tmp->next = p;
                    }
                    else {
                        p->next = lop.First;
                        lop.First = p;
                    }
                }
                break;
            }
            case 2:
            {
                bool ok;
                do {
                    ok = false;
                    cout << "Nhap ten moi: (An phim '0' de thoat) ";
                    cin.ignore();
                    string TenMoi;
                    getline(cin, TenMoi);
                    if (TenMoi == "0") {
                        cout << "Da thoat!!!\n";
                        ok = false;
                    }
                    else {
                        if (!kiemTraTenHo(TenMoi)) {
                            cout << "Loi: Ten chi duoc chua chu cai. Vui long nhap lai!\n";
                            ok = true;
                        }
                        else {
                            p->sv.TEN = TenMoi;
                            cout << "Cap nhat thanh cong\n";
                        }
                    }
                } while (ok);
                PTRSV tmp = lop.First;
                if (tmp == p) {
                    lop.First = lop.First->next;
                }
                else {
                    while (tmp->next != p) {
                        tmp = tmp->next;
                    }
                    tmp->next = tmp->next->next;
                }
                if (lop.First == NULL) {
                    lop.First = p;
                }
                else {
                    PTRSV tmp2 = lop.First;
                    PTRSV prev_tmp = NULL;
                    while (tmp2 != NULL) {
                        if (tmp2->sv.TEN < p->sv.TEN) {
                            prev_tmp = tmp2;
                            tmp2 = tmp2->next;
                        }
                        else if (tmp2->sv.TEN == p->sv.TEN) {
                            if (tmp2->sv.HO < p->sv.HO) { 
                                prev_tmp = tmp2;
                                tmp2 = tmp2->next;
                            }
                        }
                        else break;
                    }
                    if (prev_tmp != NULL) {
                        p->next = tmp;
                        prev_tmp->next = p;
                    }
                    else {
                        p->next = lop.First;
                        lop.First = p;
                    }
                }
                break;
            }

            case 3:
            {
                bool ok;
                do {
                    cout << "Nhap gioi tinh moi: (An phim '0' de thoat) ";
                    string GT;
                    cin.ignore();
                    getline(cin, GT);
                    if (GT == "0") {
                        cout << "Da thoat!!!" << endl;
                        ok = false;
                    }
                    else {
                        ok = chuanHoaGioiTinh(GT);  // Chuyển giới tính về chuẩn
                        if (!ok) {
                            p->sv.PHAI = GT;
                            cout << "Cap nhat thanh cong!\n";
                        }
                    }
                } while (ok);
                break;
            }
            case 4:
            {
                bool ok;
                cin.ignore();
                do {
                    ok = false;
                    cout << "Nhap so dien thoai moi: (An phim '0' de thoat) ";
                    string sdt;
                    getline(cin, sdt);
                    if (sdt == "0") {
                        cout << "Da thoat!!!" << endl;
                    }
                    else {
                        if (!kiemTraSoDienThoai(sdt)) {
                            cout << "Loi: So dien thoai phai co 10 so. Vui long nhap lai!\n";
                            ok = true;
                        }
                        else {
                            p->sv.SODT = sdt;
                        }
                    }
                } while (ok);
                break;
            }
            case 5:
            {
                cout << "Da thoat chuc nang hieu chinh\n";
                return;
            }
            }
        }
    } while (LuaChon != "7");
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

// Hàm quản lý sinh viên
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
                if (key == 27) {  // Nh?n ESC d? thoát
                    system("cls");
                    return;
                }
            }
        }
    }
    int soTieuDe = 2;
    string text[] = { "Ma Lop","Ten Lop" };
    string maLop = listBoxLSV(dsLop, 20, text, soTieuDe);
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
        int luachon = thanhSangListBox(xL, yL, wL, hL, 11, 14, text, 5);
        switch (luachon) {
        case 0:
            themSinhVien(lop);
            break;
        case 1:
            xoaSinhVien(lop);
            break;
        case 2:
            hieuChinhSinhVien(lop);
            break;
        case 3: {
            inDanhSachSinhVien(lop);
            break;
        }
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
        cout << "                               ";
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
    cout << "                               ";
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
                if (key == 27) {  // Nh?n ESC d? thoát
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
            char key = _getch();  // L?y k? t? ngu?i dùng nh?n
            if (key == 72) {  // Mui tên lên
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_lop(lop, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui tên xu?ng
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
                    int ok = -1;
                    if (viTriChon == 6) Nhap_ma_lop_lop(lop, viTriChon, dsLop);
                    else if (viTriChon == 8) Nhap_ten_lop_lop(lop, viTriChon);
                    if (lop.MALOP == "--") ok = 6;
                    else if (lop.TENLOP == "--") ok = 8;
                    if (ok != -1) {
                        HienThi_Them_lop(lop, ok, viTriChon, text);
                        viTriChon = ok;
                    }
                    else {
                        ok = viTriChon;
                        viTriChon = 10;
                        HienThi_Them_lop(lop, viTriChon, ok, text);
                    }
                }
            }
            else if (key == 27) {  // Nh?n ESC d? thoát
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}

void xoa_lop(DS_LOPSV& dsLop) {
    if (dsLop.n == 0) {
        cout << "Danh sach lop trong.\n";
        return;
    }
    int soTieuDe = 2;
    string text[] = { "Ma Lop", "Ten Lop" };
    while (true) {
        string maLop = listBoxLSV(dsLop, 20, text, soTieuDe);
        if (maLop == "-1") {
            xoa_noi_dung_khung2();
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
        cout << "Danh sach lop trong.\n";
        return;
    }

    int soTieuDe = 2;
    string tieuDe[] = { "Ma Lop", "Ten Lop" };
    string maLop = listBoxLSV(dsLop, 20, tieuDe, soTieuDe);

    if (maLop == "-1") {
        xoa_noi_dung_khung2();
        return;
    }

    int viTri = Tim_viTri_Lop(dsLop, maLop);
    if (viTri == -1) {
        cout << "Khong tim thay lop co ma " << maLop << ".\n";
        return;
    }
    LopSV& lop = dsLop.nodes[viTri];
    string newMaLop = lop.MALOP;
    string newTenLop = lop.TENLOP;

    int viTriChon = 6;
    string text[3] = { "Sua Ma Lop: ", "Sua Ten Lop: ", "       Luu" };

    ShowCur(false);
    xoa_noi_dung_khung2(); 
    while (true) {
        gotoXY(65, 4);
        SetColor(9);
        cout << "Hieu Chinh Lop Sinh Vien";
        for (int i = 0; i < 3; i++) {
            gotoXY(45, 6 + i * 2);
            if (viTriChon == 6 + i * 2) {
                SetColor(4);
                cout << text[i];
                if (i == 0) {
                    cout << newMaLop;
                    gotoXY(45, 6 + i * 2);

                }
                else if (i == 1) {
                    cout << newTenLop;

                }
                SetColor(7);
            }
            else {
                SetColor(7);
                cout << text[i];
                if (i == 0) {
                    cout << newMaLop;
                }
                else if (i == 1) {
                    cout << newTenLop;
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
                    lop.MALOP = newMaLop;
                    lop.TENLOP = newTenLop;
                    gotoXY(45, 12);
                    SetColor(10);
                    cout << "Cap nhat thanh cong.";
                    SetColor(7);
                    for (int i = 0; i < 300000000; i++);  
                    ShowCur(true);
                    return;
                }
                else if (viTriChon == 6) {  
                    /*while (true) {*/

                        gotoXY(45, 12);
                        cout << "Nhap Ma lop: "; ShowCur(true);
                        cin >> newMaLop;
                        cin.ignore();    
                    //}
                   
                    gotoXY(45, 12);
                    cout << "                             ";
                    ShowCur(false);
                }
                else if (viTriChon == 8) { 
                    /*while (true) {*/
                        ShowCur(true);
                        gotoXY(45, 12);
                        cout << "Nhap Ten Lop: ";
                        getline(cin, newTenLop); 
                   /* }*/
                    gotoXY(45, 12);
                    cout << "                              ";
                    ShowCur(false);
                }
            }
            else if (key == 27) {  
                ShowCur(true);
                return;
            }
        }
    }
}



// Hàm qu?n lý l?p
void capNhatLop(DS_LOPSV& dsLop) {
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "MENU QUAN LY LOP");
        boxVuong(35, 3, 80, 22, 15);
        string text[5] = { "THEM LOP", "XOA LOP", "HIEU CHINH LOP", "IN DANH SACH LOP", "THOAT" };
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

// Hàm hiển thị menu chính và xử lý lựa chọn
void hienThiMenuChinh(DS_LOPSV& dsLop) {
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "MENU LOP - SINH VIEN");
        boxVuong(35, 3, 80, 22, 15);
        string text[] = { "CAP NHAT LOP", "CAP NHAT SINH VIEN", "Thoat" };
        int luachon = thanhSangListBox(xL, yL,  wL, hL, 11, 14, text, 3);
        switch (luachon) {
        case 0:
            capNhatLop(dsLop);
            break;
        case 1:
            capNhatSinhVien(dsLop);
            break;
        case 2:
            if(xacNhanThoat()) {
                system("cls");
                return;
            }
            break;
        }
    }
}

void inDSSVTheoLop(DS_LOPSV& dsLop, string maLop) {
    // Tìm lớp theo mã lớp
    int index = -1;
    for (int i = 0; i < dsLop.n; i++) {
        if (dsLop.nodes[i].MALOP == maLop) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Khong tim thay lop voi ma " << maLop << ".\n";
        return;
    }

    // Lấy lớp và in danh sách sinh viên của lớp này
    LopSV& lop = dsLop.nodes[index];
    PTRSV p = lop.First;
    if (p == NULL) {
        cout << "Danh sach sinh vien trong lop rong!!!\n";
        return;
    }
    cout << "Danh sach sinh vien cua lop " << maLop << ":\n";
    cout << "STT\tMASV\tHO\tTEN\tPHAI\tSODT\n";

    int stt = 1;
    for (; p != NULL; p = p->next) {
        cout << stt++ << "\t" << p->sv.MASV << "\t" << p->sv.HO << "\t"
            << p->sv.TEN << "\t" << p->sv.PHAI << "\t" << p->sv.SODT << "\n";
    }
}

void InSvTheoLop(DS_LOPSV dsLop) {
    string maLop;
    if (dsLop.n == 0) {
        cout << "Danh sach lop rong.\n";
        return;
    }
    while (1) {
        cout << "Nhap ma lop can in danh sach sinh vien (an phim '|' de thoat): ";
        cin >> maLop;
        if (maLop == "|") break;
        inDSSVTheoLop(dsLop, maLop);
    }
}


// Hàm kiểm tra danh sách môn học có trống không
bool isEmpty(treeMH root) {
    return root == NULL;
}

// Hàm thêm môn học vào cây

int height(treeMH N) {
    if (N == NULL)
        return 0;
    return N->bf;
}

// A utility function to right 
// rotate subtree rooted with y 
treeMH rightRotate(treeMH y) {
    treeMH x = y->left;
    treeMH T2 = x->right;
    // Perform rotation 
    x->right = y;
    y->left = T2;
    // Update heights 
    y->bf = 1 + max(height(y->left), height(y->right));
    x->bf = 1 + max(height(x->left), height(x->right));
    // Return new root 
    return x;
}

// A utility function to left rotate 
// subtree rooted with x 
treeMH leftRotate(treeMH x) {
    treeMH y = x->right;
    treeMH T2 = y->left;
    // Perform rotation 
    y->left = x;
    x->right = T2;
    // Update heights 
    x->bf = 1 + max(height(x->left), height(x->right));
    y->bf = 1 + max(height(y->left), height(y->right));
    // Return new root 
    return y;
}

// Get balance factor of node N 
int getBalance(treeMH N) {
    if (N == NULL) return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in 
// the subtree rooted with node 
treeMH insertMH(treeMH root, const MonHoc& mh) {
    // Perform the normal BST insertion
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
    // Update height of this ancestor node 
    root->bf = 1 + max(height(root->left), height(root->right));
    // Get the balance factor of this ancestor node 
    int balance = getBalance(root);
    // If this node becomes unbalanced, 
    // then there are 4 cases 

    // Left Left Case 
    if (balance > 1 && mh.MAMH < root->left->mh.MAMH)  return rightRotate(root);
    // Right Right Case 
    if (balance < -1 && mh.MAMH > root->right->mh.MAMH) return leftRotate(root);

    // Left Right Case 
    if (balance > 1 && mh.MAMH > root->left->mh.MAMH) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Left Case 
    if (balance < -1 && mh.MAMH < root->right->mh.MAMH) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    // Return the (unchanged) node pointer 
    return root;
}


// 
//treeMH insertMH(treeMH& root, const MonHoc& mh) {
//    if (root == NULL) {
//        root = new nodeMH{ mh, 0, NULL, NULL };
//        return root;
//    }
//    if (mh.MAMH < root->mh.MAMH) root->left = insertMH(root->left, mh);
//    else if (mh.MAMH > root->mh.MAMH) root->right = insertMH(root->right, mh);
//    return root;
//}




// Hàm hiển thị danh sách môn học
int stt = 0;
void displayMH(treeMH root, int& stt) {
    if (root == NULL) return;
    displayMH(root->left, stt);
    cout << "STT: " << stt++
        << " | Ma MH: " << root->mh.MAMH
        << " | Ten MH: " << root->mh.TENMH
        << " | STCLT: " << root->mh.STCLT
        << " | STCTH: " << root->mh.STCTH << endl;
    displayMH(root->right, stt);
}

// Hàm thêm môn học với khả năng thoát ra menu chính bất kỳ lúc nào
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
        if (input.size() > 50) {
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


// Hàm thêm môn h?c v?i kh? nang thoát ra menu chính b?t k? lúc nào
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
    while (true) {
        if (_kbhit()) {
            char key = _getch();  // L?y k? t? ngu?i dùng nh?n
            if (key == 72) {  // Mui tên lên
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_mh(mh, viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui tên xu?ng
                if (viTriChon < 14) {
                    viTriChon += 2;
                    HienThi_Them_mh(mh, viTriChon, viTriChon - 2, text);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap mon
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
            else if (key == 27) {  // Nh?n ESC d? thoát
                xoa_noi_dung_khung();
                //system("cls");
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

    //     Update the balance factor and balance the tree
    root->bf = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    //    # Balancing the tree
    //    # Left Left
    if (balance > 1 && getBalance(root->left) >= 0) return rightRotate(root);

    //    # Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //
    //    # Right Right
    if (balance < -1 && getBalance(root->right) <= 0) return leftRotate(root);

    //    # Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}



// Hàm xóa môn học
//treeMH deleteMH(treeMH& root, string mamh) {
//    if (root == NULL) {
//        cout << "Ma mon hoc khong ton tai!" << endl;
//        return NULL;
//    }
//    if (mamh < root->mh.MAMH) root->left = deleteMH(root->left, mamh);
//    else if (mamh > root->mh.MAMH) root->right = deleteMH(root->right, mamh);
//    else {
//        if (root->left == NULL && root->right == NULL) {
//            delete root;
//            root = NULL;
//        }
//        else if (root->left == NULL) {
//            treeMH temp = root;
//            root = root->right;
//            delete temp;
//        }
//        else if (root->right == NULL) {
//            treeMH temp = root;
//            root = root->left;
//            delete temp;
//        }
//        else {
//            treeMH temp = root->right;
//            while (temp->left != NULL) {
//                temp = temp->left;
//            }
//            root->mh = temp->mh;
//            root->right = deleteMH(root->right, temp->mh.MAMH);
//        }
//        cout << "Xoa mon hoc thanh cong!\n";
//    }
//    return root;
//}

// Hàm hiệu chỉnh thông tin môn học


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
        if (index == chonHang) {
            textcolor(7);
        }
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
void getMH(treeMH root, MonHoc& mh, string mamh) {
    if (root == NULL) {
        return;
    }
    if (root->mh.MAMH == mamh) {
        mh = root->mh;
        return;
    }
    else if (root->mh.MAMH > mamh) {
        getMH(root->left, mh, mamh);
    }
    else {
        getMH(root->right, mh, mamh);
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
    while (true) {
        if (_kbhit()) {
            char key = _getch();  // L?y k? t? ngu?i dùng nh?n
            if (key == 72) {  // Mui tên lên
                if (viTriChon > 6) {
                    viTriChon -= 2;
                    HienThi_Them_mh((*mh), viTriChon, viTriChon + 2, text);
                }
            }
            else if (key == 80) {  // Mui tên xu?ng
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
            else if (key == 27) {  // Nh?n ESC d? thoát
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

void NhapMonHoc(treeMH& root, List_LTC& dsltc) {
    system("cls");
    boxDefault(xD, yD, wD, hD, tD, "NHAP MON HOC");
    boxVuong(35, 3, 80, 22, 15);
    string nd[] = { "Them mon hoc", " Xoa mon hoc", "Hieu chinh mon hoc", "Hien thi DSMH",  "Thoat" };
    while (true) {
        
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
                int soDuLieu = countMonHoc(root);
                string mamh;
                string tieuDe[4] = { "MA MON", "TEN MON", "STCLT", "STCTH" };
                string chonHang;
                    while (true) {
                        chonHang = listBoxMH(root, soDuLieu, tieuDe, nTieuDe);
                        if (chonHang == "-1") {
                            xoa_noi_dung_khung2();
                            break;
                        }
                        
                    
                }
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


void LocLTC(const List_LTC dsltc, const string nienkhoa, const int hocky, LopTinChi* ltc[], int& soLuong) {
    soLuong = 0;
    for (int i = 1; i <= dsltc.n; i++) {
        if (dsltc.nodes[i]->NienKhoa == nienkhoa && dsltc.nodes[i]->Hocky == hocky) {
            ltc[soLuong] = dsltc.nodes[i];
            soLuong++;
        }
    }
}


void _dangKyLopTinChi(List_LTC& dsltc, string nienkhoa, int hocky, string maSV, treeMH root, LopTinChi& ltc) {
    int maLoptc;
    cout << "Nhap ma lop tin chi ban muon dang ky(An phim '0' de quay lai): ";
    cin >> maLoptc;
    if (maLoptc == 0) {
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
            }
            else {
                cout << "Dang ky lop tin chi da bi huy bo.\n";
            }
        }
    }
}


void hienThiThongTinLopTinChi_3(treeMH DSMH, LopTinChi* ltc[], int soLuong) {
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

void TimLopTinChiTheoNienKhoaHocKy(List_LTC& dsltc, treeMH dsMonHoc, string& nienkhoa, int hocky, string maSV) {
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
        _dangKyLopTinChi(dsltc, nienkhoa, hocky, maSV, dsMonHoc, **ltc);
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
                    system("cls");
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
    while (1) {
        if (_kbhit()) {
            char key = _getch();  // L?y k? t? ngu?i dùng nh?n
            if (key == 72) {  // Mui tên lên
                if (viTriChon > 11) {
                    viTriChon -= 2;
                    HienThi_DangKyLopTinChi(text, viTriChon, viTriChon + 2, nienkhoa, hocky);
                }
            }
            else if (key == 80) {  // Mui tên xu?ng
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
                    }
                    else if (hocky == "--") {
                        gotoXY(40, 24);
                        SetColor(4);
                        cout << "Chua nhap hoc ky!";
                        for (int i = 1; i <= 300000000; i++);
                        gotoXY(40, 24);
                        cout << "                                         ";
                        HienThi_DangKyLopTinChi(text, 13, viTriChon, nienkhoa, hocky);
                    }
                    else {
                        TimLopTinChiTheoNienKhoaHocKy(dsltc, dsMonHoc, nienkhoa, stoi(hocky), maSV);
                    }
                }
                else {
                    int ok = 15;
                    if (viTriChon == 11) Nhap_nk_in_ds_svdk(nienkhoa, viTriChon);
                    else if (viTriChon == 13) Nhap_hk_in_ds_svdk(hocky, viTriChon);
                    if (nienkhoa == "--") ok = 11;
                    else if (hocky == "--") ok = 13;
                    HienThi_DangKyLopTinChi(text, ok, viTriChon, nienkhoa, hocky);
                    viTriChon = ok;
                }
            }
            else if (key == 27) {  // Nh?n ESC d? thoát
                system("cls");
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
            char key = _getch();  // L?y k? t? ngu?i dùng nh?n

            if (key == 72) {  // Mui tên lên
                if (viTriChon > 1) {
                    viTriChon--;
                    HienThiNhapDiem_2(nhap_diem, viTriChon, viTriChon + 1, So_luong, dsLopSV, nhap_diem->dssvdk);
                }
            }
            else if (key == 80) {  // Mui tên xu?ng
                if (viTriChon <= So_luong - 1) {
                    viTriChon++;
                    HienThiNhapDiem_2(nhap_diem, viTriChon, viTriChon - 1, So_luong, dsLopSV, nhap_diem->dssvdk);
                }
            }
            else if (key == 13) {  // Nhan Enter de nhap diem
                nhapDiemChoSinhVien(viTriChon, nhap_diem->dssvdk, So_luong, dsLopSV);
                return HienThiNhapDiem(nhap_diem, viTriChon, So_luong, dsLopSV);
            }
            else if (key == 27) {  // Nh?n ESC d? thoát
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
            if (key == 27) {  // Nh?n ESC d? thoát
                system("cls");
                ShowCursor();
                return;
            }
        }
    }
}


void Indssvdkltc(List_LTC& dsltc, DS_LOPSV& dsLop, treeMH& root, int input);
    // //
    void Nhap_Bang_Diem(List_LTC & dsltc, string NK, string HK, string Nhom, string MH, DS_LOPSV & dsLop, int input, treeMH & root) {
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
            //sua lai hien thi thong bao =========================================================================
            cout << "Khong ton tai lop tin chi co tham so tren!\n";
            // sua lai hien thi thong bao=========================================================================
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
    // //


    void Indssvdkltc(List_LTC & dsltc, DS_LOPSV & dsLop, treeMH & root, int input) {
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
        while (true) {
            if (_kbhit()) {
                char key = _getch();  // L?y k? t? ngu?i dùng nh?n
                if (key == 72) {  // Mui tên lên
                    if (viTriChon > 6) {
                        viTriChon -= 2;
                        HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, viTriChon + 2, text);
                    }
                }
                else if (key == 80) {  // Mui tên xu?ng
                    if (viTriChon < 14) {
                        viTriChon += 2;
                        HienThi_in_sv_dk_ltc(nk, hk, nhom, ma, viTriChon, viTriChon - 2, text);
                    }
                }
                else if (key == 13) {  // Nhan Enter de nhap mon
                    if (viTriChon == 14) {
                        if (input == 2) hienThiDanhSachSV_LTC_TheoThamSo(dsltc, dsLop, ma, hk, nhom, nk);
                        else {
                            Nhap_Bang_Diem(dsltc, nk, hk, nhom, ma, dsLop, input, root);
                            return;
                        }
                    }
                    else {
                        int ok = -1;
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
                else if (key == 27) {  // Nh?n ESC d? thoát
                    system("cls");
                    ShowCursor();
                    return;
                }
            }
        }
    }
void SVDK_LTC(DS_LOPSV& dsLop, List_LTC& dsltc, treeMH& root) {

    system("cls");
    //    generateExistingData(dsLop, dsltc, root);
    boxDefault(xD, yD, wD, hD, tD, "SINH VIEN DANG KY LOP TIN CHI"); // box lớn nhất
    boxVuong(35, 3, 80, 22, 15); // box lớn bên phải
    string text[] = { "DANG KY LTC", "IN DSSVDDK", "DANH SACH LTC", "THOAT" };
    while (1) {
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
                system("cls");
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
            if (key == 27) {  // Nh?n ESC d? thoát
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
        cout << "Nhap ma lop muon in diem trung binh ket thuc khoa hoc: ";
        getline(cin, malop);
        viTri = Tim_viTri_Lop(dsLop, malop);
        if (viTri != -1) {
            break;
        }
        cout << "Khong ton tai ma lop tren!\n";
    } while (1);
    In_DTB_1_Lop_2(dsltc, root, dsLop, malop, dsLop.nodes[viTri]);
}
//
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
    /*setConsoleBackgroundWhite();*/
    DS_LOPSV dsLop;  // Khởi tạo danh sách lớp
    List_LTC dsltc;  // Khoi tao danh sach lop tin chi
    treeMH root = NULL; //Khoi tao cay mon hoc
    MonHoc mh1;
    
    mh1.MAMH = "int";
    mh1.STCLT = 3;
    mh1.STCTH = 0;
    mh1.TENMH = "Toan";

    nodeMH nmh1;
    nmh1.left = NULL;
    nmh1.right = NULL;
    nmh1.mh = mh1;

    root = &nmh1;


    SinhVien a;
    a.HO = "Le Van";
    a.TEN = "Dai";
    a.MASV = "1";
    a.PHAI = "Nam";
    a.SODT = "0123456789";

    nodeSV sv1;
    sv1.sv = a;
    sv1.next = NULL;

    SinhVien b;
    b.HO = "Le Van";
    b.TEN = "Hung";
    b.MASV = "2";
    b.PHAI = "Nam";
    b.SODT = "0123456789";

    nodeSV sv2;
    sv2.sv = b;
    sv2.next = NULL;
    sv1.next = &sv2;

    SinhVien c;
    c.HO = "Le Van";
    c.TEN = "Vinh";
    c.MASV = "3";
    c.PHAI = "Nam";
    c.SODT = "0123456789";

    nodeSV sv3;
    sv3.sv = c;
    sv3.next = NULL;
    sv2.next = &sv3;

    SinhVien d;
    d.HO = "Nguyen Van";
    d.TEN = "Binh";
    d.MASV = "4";
    d.PHAI = "Nam";
    d.SODT = "0123456789";

    nodeSV sv4;
    sv4.sv = d;
    sv4.next = NULL;

    SinhVien e;
    e.HO = "Nguyen Thi";
    e.TEN = "Xinh";
    e.MASV = "5";
    e.PHAI = "Nu";
    e.SODT = "0123456789";

    nodeSV sv5;
    sv5.sv = e;
    sv5.next = NULL;

    SinhVien f;
    f.HO = "Tran Ha";
    f.TEN = "Linh";
    f.MASV = "6";
    f.PHAI = "Nu";
    f.SODT = "0123456789";

    nodeSV sv6;
    sv6.sv = f;
    sv6.next = NULL;
    sv5.next = &sv6;

    SinhVien g;
    g.HO = "Vuong Thi Xinh";
    g.TEN = "Dep";
    g.MASV = "7";
    g.PHAI = "Nu";
    g.SODT = "0123456789";

    nodeSV sv7;
    sv7.sv = g;
    sv7.next = NULL;
    sv6.next = &sv7;

    LopSV lop1;
    lop1.MALOP = "e23";
    lop1.TENLOP = "cntt";
    lop1.First = &sv1;

    LopSV lop2;
    lop2.MALOP = "e24";
    lop2.TENLOP = "cntt";
    lop2.First = &sv4;

    LopSV lop3;
    lop3.MALOP = "m24";
    lop3.TENLOP = "mkt";
    lop3.First = &sv5;

    dsLop.n = 3;
    dsLop.nodes[0] = lop1;
    dsLop.nodes[1] = lop2;
    dsLop.nodes[2] = lop3;
    // Khởi tạo danh sách các lớp
  

    // Tạo thêm 30 lớp
    for (int i = 3; i < 33; i++) {
        LopSV lop;
        lop.MALOP = "L" + to_string(i); // Mã lớp dạng L3, L4, ...
        lop.TENLOP = (i % 2 == 0) ? "cntt" : "mkt"; // Xen kẽ "cntt" và "mkt"
        lop.First = nullptr; // Giả định không có sinh viên cụ thể liên kết

        dsLop.nodes[i] = lop;
        dsLop.n++;
    }


    LopTinChi tc1;
    tc1.MALOPTC = 1;
    tc1.MAMH = "int";
    tc1.NienKhoa = "2023-2024";
    tc1.Hocky = 2;
    tc1.Nhom = 3;
    tc1.sosvmin = 5;
    tc1.sosvmax = 10;

    dsltc.n = 1;
    dsltc.nodes[1] = &tc1;

    DangKy dk1, dk2, dk3;
    dk1.MASV = "1";
    dk2.MASV = "2";
    dk3.MASV = "3";
    nodeDK ndk1, ndk2, ndk3;
    ndk1.dk = dk1;
    ndk1.next = NULL;
    tc1.dssvdk = &ndk1;
    ndk2.dk = dk2;
    ndk2.next = NULL;
    ndk1.next = &ndk2;
    ndk3.dk = dk3;
    ndk3.next = NULL;
    ndk2.next = &ndk3;
    root = insertMH(root, { "500000", "AN NINH MANG", 2, 0 });
    root = insertMH(root, { "300000", "CAU TRUC DU LIEU", 3, 1 });
    root = insertMH(root, { "812514", "AN TOAN HE THONG", 3, 1 });
    root = insertMH(root, { "750003", "ANH VAN A11", 2, 0 });
    root = insertMH(root, { "100001", "TOAN CAO CAP", 4, 1 });
    root = insertMH(root, { "200002", "LAP TRINH C", 3, 1 });
    root = insertMH(root, { "300003", "LAP TRINH JAVA", 3, 1 });
    root = insertMH(root, { "400004", "CSDL & QLHT", 3, 1 });
    root = insertMH(root, { "500005", "KIEN TRUC MANG", 4, 1 });
    root = insertMH(root, { "600006", "TONG HOP KI THUAT", 2, 0 });
    root = insertMH(root, { "700007", "TOAN RANG BUOC", 4, 1 });
    root = insertMH(root, { "800008", "TIN HOC A", 2, 0 });
    root = insertMH(root, { "900009", "ANH VAN A12", 2, 0 });
    root = insertMH(root, { "100010", "TOAN HOC", 4, 1 });
    root = insertMH(root, { "110011", "THIET KE WEB", 3, 1 });
    root = insertMH(root, { "120012", "PHAN MEM VA XU LY", 3, 1 });
    root = insertMH(root, { "130013", "MAY TINH", 2, 0 });
    root = insertMH(root, { "140014", "LAP TRINH C++", 3, 1 });
    root = insertMH(root, { "150015", "HE THONG MANG", 3, 1 });
    root = insertMH(root, { "160016", "KIEN THUC TOAN", 4, 1 });
    root = insertMH(root, { "170017", "DU LIEU LON", 3, 1 });
    root = insertMH(root, { "180018", "PHAN ANH", 4, 1 });
    root = insertMH(root, { "190019", "TOAN HOC RANG BUOC", 4, 1 });
    root = insertMH(root, { "200020", "KIEN TRUC MANG", 4, 1 });
    root = insertMH(root, { "210021", "HE THONG THONG ", 3, 1 });
    root = insertMH(root, { "220022", "TOAN HOC CAO CAP", 4, 1 });
    root = insertMH(root, { "230023", "THIET KE DIEN TOAN", 3, 1 });
    root = insertMH(root, { "240024", "MAY TINH", 2, 0 });
    root = insertMH(root, { "250025", "LAP TRINH JAVA", 3, 1 });
    root = insertMH(root, { "260026", "VAN HOC", 2, 0 });
    root = insertMH(root, { "270027", "NGON NGU LAP TRINH", 3, 1 });
    root = insertMH(root, { "280028", "ANH VAN A11", 2, 0 });
    root = insertMH(root, { "290029", "QUAN LY KINH DOANH", 3, 1 });
    root = insertMH(root, { "300030", "TOAN CAO CAP", 4, 1 });
    root = insertMH(root, { "310031", "PHAN MEM ", 3, 1 });
    root = insertMH(root, { "320032", "TIN HOC", 2, 0 });

    while (true) {

        boxDefault(xD, yD, wD, hD, tD, "MENU QUAN LY DIEM SINH VIEN THEO HE TIN CHI");
        boxVuong(35, 3, 80, 22, 7);
        string text[] = { "Lop Tin Chi", "Nhap lop - Nhap SV", "Nhap mon hoc", "Sinh vien DKLTC", "Nhap-In Diem sinh vien", "Thoat" };
        /*ListBox(35, 3, 80, 1, 15, 14, text, 6);*/
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

