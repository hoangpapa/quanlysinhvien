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
    int current_sv = 0;
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

// Xoa lop tin chi (hien thi danh sach lop tin chi truoc khi xoa) 
void xoaLopTinChi(List_LTC& dsltc) {
    hienThiDanhSachLopTinChi(dsltc); // Hien thi danh sach truoc khi xoa
    if (dsltc.n == 0) return;
    int ok = 1;
    do {
        string input = nhapChuoiSo("Nhap ma lop tin chi muon xoa (An phim '|' de quay lai): ");
        if (input == "|") return;
        int MALOPTC = stoi(input);  // Chuyen chuoi thanh so
        int i = TimLTC(MALOPTC, dsltc);
        if (i == -1) {
            cout << "Khong tim thay lop tin chi de xoa.\n";
        }
        else {
            if (dsltc.nodes[i]->dssvdk != NULL) {
                cout << "Da co sv dk ltc nay - ko the xoa!\n";
            }
            else {
                char confirm;
                do {
                    cout << "Ban co chac muon xoa lop tin chi nay khong? (y/n): ";
                    cin >> confirm;
                    cin.ignore();
                    if (confirm == 'y' || confirm == 'Y') {
                        ok = 0;
                        delete dsltc.nodes[i];
                        for (int j = i; j <= dsltc.n - 1; j++) {
                            dsltc.nodes[j] = dsltc.nodes[j + 1];
                        }
                        dsltc.n--;
                        cout << "Lop tin chi da duoc xoa thanh cong.\n";
                        break;
                    }
                    else if (confirm == 'n' || confirm == 'N') {
                        cout << "Da huy thao tac xoa!!!\n";
                        break;
                    }
                    else {
                        cout << "Vui long nhap dung cu phap!\n";
                    }
                } while (1);
            }
        }
    } while (ok);
}


// Them lop tin chi (co nut quay lai)
void themLopTinChi(List_LTC& dsltc, treeMH root) {
    string input;
    LopTinChi ltc;
    if (dsltc.n == 0) ltc.MALOPTC = 1;
    else ltc.MALOPTC = (dsltc.nodes[dsltc.n]->MALOPTC + 1);
    do {
        cout << "Nhap ma mon hoc (nhap '|' de quay lai): ";
        getline(cin, input);
        if (input == "|") {
            cout << "Da quay lai menu.\n";
            return;
        }
        if (isDuplicateMH(root, input)) {
            ltc.MAMH = input;
            break;
        }
        cout << "Khong ton tai ma mon hoc nay!!!\n";
    } while (1);

    // Kiem tra nien khoa co hop le
    do {
        cout << "Nhap nien khoa (dinh dang YYYY-YYYY) (nhap '|' de quay lai): ";
        getline(cin, ltc.NienKhoa);
        if (ltc.NienKhoa == "|") {
            cout << "Da quay lai menu.\n";
            return;
        }
        if (!kiemTraNienKhoa(ltc.NienKhoa)) {
            cout << "Loi: Nien khoa khong hop le. Vui long nhap lai!\n";
        }
    } while (!kiemTraNienKhoa(ltc.NienKhoa)); // Lap lai neu nien khoa khong hop le

    input = nhapChuoiSo("Nhap hoc ky (nhap '|' de quay lai): ");
    if (input == "|") {
        cout << "Da quay lai menu.\n";
        return;
    }
    ltc.Hocky = stoi(input);
    input = nhapChuoiSo("Nhap nhom (nhap '|' de quay lai): ");
    if (input == "|") {
        cout << "Da quay lai menu.\n";
        return;
    }
    ltc.Nhom = stoi(input);

    // Kiem tra tinh hop le cua so sinh vien
    do {
        input = nhapChuoiSo("Nhap so sv toi thieu (nhap '|' de quay lai): ");
        if (input == "|") {
            cout << "Da quay lai menu.\n";
            return;
        }
        ltc.sosvmin = stoi(input);
        input = nhapChuoiSo("Nhap so sv toi da (nhap '|' de quay lai): ");
        if (input == "|") {
            cout << "Da quay lai menu.\n";
            return;
        }
        ltc.sosvmax = stoi(input);
        if (ltc.sosvmin > ltc.sosvmax) {
            cout << "So sinh vien toi thieu khong duoc lon hon so sv toi da. Vui long nhap lai!\n";
        }
    } while (ltc.sosvmin > ltc.sosvmax);
    for (int i = 1; i <= dsltc.n; i++) {
        if (ltc.MAMH == dsltc.nodes[i]->MAMH && ltc.NienKhoa == dsltc.nodes[i]->NienKhoa && ltc.Hocky
            == dsltc.nodes[i]->Hocky && ltc.Nhom == dsltc.nodes[i]->Nhom) {
            cout << "Lop tin nay da ton tai!!!\n";
            return;
        }
    }
    // Th�m l?p t�n ch? v�o danh s�ch
    dsltc.nodes[++dsltc.n] = new LopTinChi(ltc);
    cout << "Lop tin chi duoc them thanh cong.\n";
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
        return false;
    }
    else if (phai == "nu" || phai == "Nu" || phai == "NU") {
        phai = "Nu";
        return false;
    }
    cout << "Gioi tinh khong hop le\n";
    return true;
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
        if ((NienKhoa == "-" || NienKhoa == LTC->NienKhoa)
            && (HocKy == "-" || stoi(HocKy) == LTC->Hocky)
            && (Nhom == "-" || stoi(Nhom) == LTC->Nhom)
            && (MaMonHoc == "-" || MaMonHoc == LTC->MAMH)
            ) {
            InDSSV_LTC(LTC, dsLop);
        }
    }
}

void Indssvdkltc(List_LTC& dsltc, DS_LOPSV& dsLop) {
    if (dsltc.n == 0) {
        cout << "Chua co lop tin chi da mo de sinh vien dang ky!\n";
        return;
    }
    string nk, ma, hk, nhom;
    cout << "Nhap nien khoa muon xem(An phim '-' de bo qua, An phim '|' de thoat): ";
    getline(cin, nk);
    if (nk == "|") {
        cout << "Da thoat!\n";
        return;
    }
    cout << "Nhap hoc ky muon xem(An phim '-' de bo qua, An phim '|' de thoat): ";
    getline(cin, hk);
    if (hk == "|") {
        cout << "Da thoat!\n";
        return;
    }
    cout << "Nhap nhom muon xem(An phim '-' de bo qua, An phim '|' de thoat): ";
    getline(cin, nhom);
    if (nhom == "|") {
        cout << "Da thoat!\n";
        return;
    }
    cout << "Nhap ma mon hoc muon xem(An phim '-' de bo qua, An phim '|' de thoat): ";
    getline(cin, ma);
    if (ma == "|") {
        cout << "Da thoat!\n";
        return;
    }
    hienThiDanhSachSV_LTC_TheoThamSo(dsltc, dsLop, ma, hk, nhom, nk);
}

void inDanhSachLop(DS_LOPSV& dsLop) {
    if (dsLop.n == 0) {
        cout << "Danh sach lop trong.\n";
        return;
    }
    cout << "\n===== DANH SACH LOP =====\n";
    cout << "STT\tMa lop\tTen lop\n";
    for (int i = 0; i < dsLop.n; i++) {
        cout << i + 1 << "\t" << dsLop.nodes[i].MALOP << "\t" << dsLop.nodes[i].TENLOP << "\n";
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

// Hàm thêm sinh viên vào lớp
void themSinhVien(LopSV& lop) {
    SinhVien sv;
    bool ok = false;
    do {
        cout << "Nhap ma sinh vien (An phim '|' de thoat): ";
        string ma;
        cin.ignore();
        getline(cin, ma);
        if (ma == "|") {
            cout << "Da thoat!!!";
            return;
        }
        if (ma.size() > 15) {
            cout << "Ma sinh vien khong duoc qua 15 ki tu!!!\n";
            ok = true;
        }
        else {
            sv.MASV = ma;
            ok = false;
        }
    } while (ok);

    // Kiểm tra mã sinh viên đã tồn tại
    if (kiemTraMaSVTonTai(lop, sv.MASV)) {
        cout << "Ma sinh vien " << sv.MASV << " da ton tai.\n";
        return;
    }

    // Kiểm tra họ sinh viên
    ok = false;
    do {
        cout << "Nhap ho (An phim '|' de thoat) ";
        getline(cin, sv.HO);
        if (sv.HO == "|") {
            cout << "Da thoat!!!" << endl;
            return;
        }
        else {
            if (!kiemTraTenHo(sv.HO)) {
                cout << "Loi: Ho chi duoc chua chu cai. Vui long nhap lai!\n";
                ok = true;
            }
            else ok = false;
        }
    } while (ok);

    // Kiểm tra tên sinh viên
    ok = false;
    do {
        cout << "Nhap ten (An phim '|' de thoat): ";
        getline(cin, sv.TEN);
        if (sv.TEN == "|") {
            cout << "Da thoat\n";
            return;
        }
        else {
            if (!kiemTraTenHo(sv.TEN)) {
                cout << "Loi: Ten chi duoc chua chu cai. Vui long nhap lai!\n";
                ok = true;
            }
            else ok = false;
        }
    } while (ok);

    // Nhập và chuẩn hóa giới tính
    ok = false;
    do {
        cout << "Nhap gioi tinh (Nam/Nu), (An phim '0' de thoat): ";
        getline(cin, sv.PHAI);
        if (sv.PHAI == "0") {
            cout << "Da thoat!!!" << endl;
            return;
        }
        else {
            ok = chuanHoaGioiTinh(sv.PHAI);  // Chuyển giới tính về chuẩn
        }
    } while (ok);

    // Kiểm tra số điện thoại
    ok = false;
    do {
        cout << "Nhap so dien thoai (10 so), (An phim '0' de thoat): ";
        getline(cin, sv.SODT);
        if (sv.SODT == "0") {
            cout << "Da thoat!!!\n";
            return;
        }
        else {
            if (!kiemTraSoDienThoai(sv.SODT)) {
                cout << "Loi: So dien thoai phai co 10 so. Vui long nhap lai!\n";
                ok = true;
            }
            else ok = false;
        }
    } while (ok);
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
    cout << "Them sinh vien thanh cong.\n";
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
    cin.ignore();
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
        cout << "Danh sach lop trong. Vui long tao lop truoc khi cap nhat sinh vien.\n";
        return;
    }

    string MALOP;
    cout << "Nhap ma lop de cap nhat sinh vien: ";
    cin >> MALOP;

    int viTri = Tim_viTri_Lop(dsLop, MALOP);
    for (int i = 0; i < dsLop.n; i++) {
        if (dsLop.nodes[i].MALOP == MALOP) {
            viTri = i;
            break;
        }
    }

    if (viTri == -1) {
        cout << "Khong tim thay lop co ma " << MALOP << ".\n";
        return;
    }

    LopSV& lop = dsLop.nodes[viTri];  // Lấy tham chiếu đến lớp

    int luaChon;
    do {
        cout << "\n===== NHAP SINH VIEN =====\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Xoa sinh vien\n";
        cout << "3. Hieu chinh sinh vien\n";
        cout << "4. In danh sach sinh vien\n";
        cout << "5. Quay lai\n";
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1:
            themSinhVien(lop);
            break;
        case 2:
            xoaSinhVien(lop);
            break;
        case 3:
            hieuChinhSinhVien(lop);
            break;
        case 4:
            inDanhSachSinhVien(lop);
            break;
        case 5:
            cout << "Quay lai menu truoc.\n";
            return;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (luaChon != 5);
}

// Hàm quản lý lớp
void capNhatLop(DS_LOPSV& dsLop) {
    int luaChon;
    do {
        cout << "\n===== CAP NHAT LOP =====\n";
        cout << "1. Them lop\n";
        cout << "2. Xoa lop\n";
        cout << "3. Hieu chinh lop\n";
        cout << "4. In danh sach lop\n";
        cout << "5. Quay lai\n";
        cout << "Lua chon cua ban: ";
        cin >> luaChon;

        switch (luaChon) {
        case 1: {
            if (dsLop.n == 1000) {
                cout << "Danh sach lop da day.\n";
                break;
            }
            LopSV lop;
            string malop ;
            do {
                cout << "Nhap ma lop (An phim '0' de thoat): ";
                cin.ignore();
                getline(cin, malop);
                if (malop.size() > 15) {
                    cout << "Ma lop khong duoc vuot qua 15 ki tu!!!\n";
                }
            } while (malop.size() > 15);
            bool tonTai = false;
            for (int i = 0; i < dsLop.n; i++) {
                if (dsLop.nodes[i].MALOP == malop) {
                    tonTai = true;
                    break;
                }
            }

            if (tonTai) {
                cout << "Ma lop da ton tai.\n";
            }
            else {
                lop.MALOP = malop;
                //   cin.ignore(); 
                cout << "Nhap ten lop (An phim '0' de tra lai): ";
                getline(cin, lop.TENLOP);
                if (lop.TENLOP == "0") {
                    cout << "Da tra lai menu!!!\n";
                    break;
                }
                dsLop.nodes[dsLop.n++] = lop;
                cout << "Them lop thanh cong.\n";
            }
            break;
        }
        case 2: {
            if (dsLop.n == 0) {
                cout << "Danh sach lop trong.\n";
                break;
            }
            inDanhSachLop(dsLop);
            string MALOP;
            cout << "Nhap ma lop can xoa (An phim '0' de tro lai): ";
            cin.ignore();
            getline(cin, MALOP);
            if (MALOP == "0") {
                cout << "Da quay tro lai menu!!!" << endl;
                return;
            }
            int viTri = -1;
            for (int i = 0; i < dsLop.n; i++) {
                if (dsLop.nodes[i].MALOP == MALOP) {
                    viTri = i;
                    break;
                }
            }

            if (viTri == -1) {
                cout << "Khong tim thay lop co ma " << MALOP << ".\n";
            }
            else {
                while (1) {
                    cout << "Ban co chan muon xoa lop nay khong? (y/n)";
                    char confirm; cin >> confirm;
                    if (confirm == 'n') {
                        cout << "Da huy thao tac xoa! \n";
                        break;
                    }
                    else if (confirm == 'y' || confirm == 'Y') {
                        for (int i = viTri; i < dsLop.n - 1; i++) {
                            dsLop.nodes[i] = dsLop.nodes[i + 1];
                        }
                        dsLop.n--;
                        cout << "Xoa lop thanh cong.\n";
                        break;
                    }
                    else {
                        cout << "Thao tac khong hop le!!!\n";
                    }
                }
            }
            break;
        }
        case 3: {
            if (dsLop.n == 0) {
                cout << "Danh sach lop trong.\n";
                break;
            }
            inDanhSachLop(dsLop);
            string MALOP;
            cin.ignore();
            cout << "Nhap ma lop can hieu chinh (An phim '0' de tro lai): ";
            getline(cin, MALOP);
            if (MALOP == "0") {
                cout << "Da tro lai menu!!!" << endl;
                return;
            }
            int viTri = -1;
            for (int i = 0; i < dsLop.n; i++) {
                if (dsLop.nodes[i].MALOP == MALOP) {
                    viTri = i;
                    break;
                }
            }
            if (viTri == -1) {
                cout << "Khong tim thay lop co ma " << MALOP << ".\n";
            }
            else {
                LopSV& lop = dsLop.nodes[viTri];
                cout << "Nhap ten lop moi (An phim '|' de thoat): ";
                cin.ignore();
                string tenMoi;
                if (tenMoi == "|") {
                    cout << "Da thoat!!!\n";
                    break;
                }
                getline(cin, tenMoi);
                if (tenMoi.size() > 0) {
                    lop.TENLOP = tenMoi;
                }
                cout << "Thong tin lop da duoc cap nhat.\n";
            }
            break;
        }
        case 4:
            inDanhSachLop(dsLop);
            break;
        case 5:
            cout << "Quay lai menu truoc.\n";
            return;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (luaChon != 4);
}

// Hàm hiển thị menu chính và xử lý lựa chọn
void hienThiMenuChinh(DS_LOPSV& dsLop) {
    system("cls");
    while (true) {
        boxDefault(xD, yD, wD, hD, tD, "Nhap lop - Nhap SV");
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
treeMH insertMH(treeMH& root, const MonHoc& mh) {
    if (root == NULL) {
        root = new nodeMH{ mh, 0, NULL, NULL };
        return root;
    }
    if (mh.MAMH < root->mh.MAMH) root->left = insertMH(root->left, mh);
    else if (mh.MAMH > root->mh.MAMH) root->right = insertMH(root->right, mh);
    return root;
}

int treeToArray(treeMH root, string data[][4], int& index) {
    if (root == NULL) return index;
    treeToArray(root->left, data, index);
    data[index][0] = root->mh.MAMH;
    data[index][1] = root->mh.TENMH;
    data[index][2] = to_string(root->mh.STCLT);
    data[index][3] = to_string(root->mh.STCTH);
    index++;
    treeToArray(root->right, data, index);
    return index;
}



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
void addMonHoc(treeMH& root) {
    MonHoc mh;
    string input;
    bool ok;
    // Nhập mã môn học
    do {
        cout << "\n==========THEM MON HOC==========\n";
        do {
            cout << "Nhap ma mon hoc (nhap '|' de thoat): ";
            getline(cin, input);
            ok = false;
            if (input == "|") {
                cout << "Da thoat!!!\n";
                return;  // Thoát ra menu chính nếu nhập '|'
            }
            if (input.size() > 10) {
                ok = true;
                cout << "Ma mon hoc khong duoc qua 10 ki tu!!!\n";
            }
            else if (isDuplicateMH(root, input)) {
                cout << "Ma mon hoc da ton tai. Khong the them moi." << endl;
                ok = true;
            }
            if (ok == false) mh.MAMH = input;
        } while (ok);

        // Nhập tên môn học
        do {
            cout << "Nhap ten mon hoc (nhap '|' de thoat): ";
            ok = false;
            getline(cin, input);
            if (input == "|") {
                cout << "Da thoat!!!" << endl;
                return;  // Thoát ra menu chính nếu nhập '|'
            }
            if (input.size() > 50) {
                ok = true;
                cout << "Ten mon hoc khong duoc qua 50 ki tu!!!\n";
            }
            if (ok == false) mh.TENMH = input;
        } while (ok);
        // Nhập số tín chỉ lý thuyết
        do {
            cout << "Nhap so tin chi ly thuyet (nhap '|' de thoat): ";
            getline(cin, input);
            if (input == "|") {
                cout << "Da thoat!!!\n";
                return;
            }
            ok = kiemTraChuoiSo(input);
            if (!ok) cout << "So tin chi ly thuyet la so nguyen khong am!!!\n";
            else mh.STCLT = stoi(input);
        } while (!ok);

        // Nhập số tín chỉ thực hành
        do {
            cout << "Nhap so tin chi thuc hanh (nhap '|' de thoat): ";
            getline(cin, input);
            if (input == "|") {
                cout << "Da thoat!!!\n";
                return;
            }
            ok = kiemTraChuoiSo(input);
            if (!ok) cout << "So tin chi thuc hanh la so nguyen khong am!!!\n";
            else mh.STCTH = stoi(input);
        } while (!ok);

        // Thêm môn học mới vào cây
        root = insertMH(root, mh);
        cout << "Them mon hoc thanh cong!\n";
    } while (1);
}

// Hàm xóa môn học
treeMH deleteMH(treeMH& root, string& mamh) {
    if (root == NULL) {
        cout << "Ma mon hoc khong ton tai!" << endl;
        return NULL;
    }
    if (mamh < root->mh.MAMH) root->left = deleteMH(root->left, mamh);
    else if (mamh > root->mh.MAMH) root->right = deleteMH(root->right, mamh);
    else {
        if (root->left == NULL && root->right == NULL) {
            delete root;
            root = NULL;
        }
        else if (root->left == NULL) {
            treeMH temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL) {
            treeMH temp = root;
            root = root->left;
            delete temp;
        }
        else {
            treeMH temp = root->right;
            while (temp->left != NULL) {
                temp = temp->left;
            }
            root->mh = temp->mh;
            root->right = deleteMH(root->right, temp->mh.MAMH);
        }
        cout << "Xoa mon hoc thanh cong!\n";
    }
    return root;
}

// Hàm hiệu chỉnh thông tin môn học
void updateMH(treeMH& root) {
    string mamh;
    treeMH node;
    if (isEmpty(root)) {
        cout << "Danh sach mon hoc trong!" << endl;
        return;
    }
    do {
        cout << "\n==========HIEU CHINH MON HOC==========\n";
        cout << "Danh sach mon hoc hien co:\n";
        stt = 1;
        displayMH(root, stt);
        cout << "Nhap ma mon hoc can hieu chinh (An phim '|' de thoat): ";
        getline(cin, mamh);
        if (mamh == "|") {
            cout << "Da thoat!!!\n";
            return;
        }
        node = searchMH(root, mamh);
        if (node == NULL) {
            cout << "Khong tim thay mon hoc voi ma: " << mamh << endl;
        }
        else break;
    } while (1);
    int choice;
    while (true) {
        cout << "\n========HIEU CHINH MON HOC CO MA " << mamh << "========" << endl;
        cout << "Chon thong tin can chinh sua:\n";
        cout << "1. Ma mon hoc\n";
        cout << "2. Ten mon hoc\n";
        cout << "3. So tin chi ly thuyet\n";
        cout << "4. So tin chi thuc hanh\n";
        cout << "0. Thoat\n";
        cout << "Lua chon cua ban: ";
        choice = stoi(nhapChuoiSo_2("Nhap lua chon: "));
        bool ok;
        string input;
        switch (choice) {
        case 1: {
            cout << "Nhap ma moi cho mon hoc (nhap '|' de thoat): ";
            string newMAMH;
            cin >> newMAMH;
            if (newMAMH == "|") return; // Thoát nếu người dùng nhập '|'
            if (isDuplicateMH(root, newMAMH)) {
                cout << "Ma mon hoc nay da ton tai. Giu nguyen ma cu.\n";
            }
            else {
                node->mh.MAMH = newMAMH;
                cout << "Ma mon hoc da duoc cap nhat!\n";
            }
            break;
        }
        case 2: {
            cout << "Nhap ten moi cho mon hoc (nhap '|' de thoat): ";
            cin.ignore();
            string newTENMH;
            getline(cin, newTENMH);
            if (newTENMH == "|") return; // Thoát nếu người dùng nhập '|'
            node->mh.TENMH = newTENMH;
            cout << "Ten mon hoc da duoc cap nhat!\n";
            break;
        }
        case 3: {
            cin.ignore();
            do {
                cout << "Nhap so tin chi ly thuyet moi (nhap '|' de thoat): ";
                getline(cin, input);
                if (input == "|") {
                    cout << "Da thoat!!!" << endl;
                    return;
                }
                ok = kiemTraChuoiSo(input);
                if (!ok) cout << "So tin chi ly thuyet phai la so nguyen khong am!!!\n";
                else {
                    node->mh.STCLT = stoi(input);
                    cout << "Cap nhat thanh cong!\n";
                }
            } while (!ok);
            break;
        }
        case 4: {
            cin.ignore();
            do {
                cout << "Nhap so tin chi thuc hanh moi (nhap '|' de thoat): ";
                getline(cin, input);
                if (input == "|") {
                    cout << "Da thoat!!!" << endl;
                    return;
                }
                ok = kiemTraChuoiSo(input);
                if (!ok) cout << "So tin chi thuc hanh phai la so nguyen khong am!!!\n";
                else {
                    node->mh.STCTH = stoi(input);
                    cout << "Cap nhat thanh cong!\n";
                }
            } while (!ok);
            break;
        }
        case 0:
            cout << "Thoat hieu chinh.\n";
            return; // Thoát hàm nếu chọn thoát
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    }
}

void Xoa_MH(treeMH& root, List_LTC& dsltc) {
    string mamh;
    if (isEmpty(root)) {
        cout << "Danh sach mon hoc trong!" << endl;
        
        return;
    }
    do {
        cout << "\n==========XOA MON HOC==========\n";
        cout << "Danh sach mon hoc hien co:\n";
        stt = 1;
        displayMH(root, stt);
        cout << "Nhap ma mon hoc can xoa (an phim '|' de thoat): ";
        getline(cin, mamh);
        if (mamh == "|") {
            cout << "Da thoat!!!" << endl;
            return;
        }
        root = deleteMH(root, mamh);
    } while (1);
}
int countMonHoc(treeMH root) {
    if (root == NULL) {
        return 0;
    }
    else {
         return 1 + countMonHoc(root->left) + countMonHoc(root->right);
    }
}



void NhapMonHoc(treeMH& root, List_LTC& dsltc) {
    system("cls");
    boxDefault(xD, yD, wD, hD, tD, "NHAP MON HOC");
    boxVuong(35, 3, 80, 22, 15);
    string nd[] = { "Them mon hoc", " Xoa mon hoc", "Hieu chinh mon hoc", "Hien thi DSMH",  "Thoat" };
        int index = 0;
 
        string data[250][4];
        treeToArray(root, data, index);
        int nTieuDe = 4;
        int soDuLieu = countMonHoc(root);
        string tieuDe[4] = { "MA MON", "TEN MON", "STCLT", "STCTH" };
    while (true) {
        
        int luachon = thanhSangListBox(xL, yL, wL, hL, 7, 14, nd, 5);
        int selectedRow;
        switch (luachon) {
        case 0:
            addMonHoc(root);
            break;
        case 1:
            selectedRow = listBox(data, soDuLieu, tieuDe, nTieuDe);
            cout << selectedRow << endl;
            Xoa_MH(root, dsltc);
             
            break;
        case 2:
            updateMH(root);
             selectedRow = listBox(data, soDuLieu, tieuDe, nTieuDe);
            cout << selectedRow << endl;
            break;
        case 3:
            if (isEmpty(root)) {
                cout << "Danh sach mon hoc trong!" << endl;
            }
            else {
                cout << "Danh sach mon hoc:\n";
                stt = 1;
                cout << "\n==========DANH SACH MON HOC==========\n";
                displayMH(root,stt);
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


void DangKyLopTinChi(List_LTC& dsltc, DS_LOPSV& dsLop, treeMH dsMonHoc) {
    string maSV, nienkhoa;
    int hocky;
    if (dsltc.n == 0) {
        cout << "Danh sach lop tin chi rong.\n";
        return;
    }   
    bool sinhVienTonTai = false;
    do {
        cout << "Nhap ma sinh vien(An phim '|' de thoat): ";
        cin >> maSV;
        cin.ignore();
        if (maSV == "|") {
            return;
        }
        sinhVienTonTai = timLopSV(dsLop, maSV);
    } while (!sinhVienTonTai);
    do {
        cout << "Nhap nien khoa (dinh dang YYYY-YYYY) (nhap '|' de quay lai): ";
        getline(cin, nienkhoa);
        if (nienkhoa == "|") {
            cout << "Da quay lai menu.\n";
            return;
        }
        if (!kiemTraNienKhoa(nienkhoa)) {
            cout << "Loi: Nien khoa khong hop le. Vui long nhap lai!\n";
        }
    } while (!kiemTraNienKhoa(nienkhoa));

    cout << "Nhap hoc ky: ";
    cin >> hocky;
    TimLopTinChiTheoNienKhoaHocKy(dsltc, dsMonHoc, nienkhoa, hocky, maSV);
}
void generateExistingData(DS_LOPSV& dsLop, List_LTC& dsltc, treeMH& root) {
    // Generate some sample data for LopSV
    LopSV lop1 = { "L01", "Lop 1" };
    LopSV lop2 = { "L02", "Lop 2" };
    dsLop.nodes[dsLop.n++] = lop1;
    dsLop.nodes[dsLop.n++] = lop2;

    // Generate some sample data for SinhVien
    SinhVien sv1 = { "SV01", "Nguyen", "An", "Nam", "0123456789" };
    SinhVien sv2 = { "SV02", "Tran", "Binh", "Nu", "0987654321" };
    PTRSV node1 = new nodeSV{ sv1, NULL };
    PTRSV node2 = new nodeSV{ sv2, NULL };
    dsLop.nodes[0].First = node1;
    dsLop.nodes[1].First = node2;

    // Generate some sample data for MonHoc
    MonHoc mh1 = { "MH01", "Mon Hoc 1", 3, 2 };
    MonHoc mh2 = { "MH02", "Mon Hoc 2", 2, 1 };
    root = insertMH(root, mh1);
    root = insertMH(root, mh2);

    // Generate some sample data for LopTinChi
    LopTinChi ltc1 = { 1, "MH01", "2023-2024", 1, 1, 10, 30, false, NULL, 0 };
    LopTinChi ltc2 = { 2, "MH02", "2023-2024", 1, 1, 10, 30, false, NULL, 0 };
    dsltc.nodes[dsltc.n++] = new LopTinChi(ltc1);
    dsltc.nodes[dsltc.n++] = new LopTinChi(ltc2);
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
            Indssvdkltc(dsltc, dsLop);
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
SinhVien* Timsv(DS_LOPSV& dsLopSV, string maSV) {
   for (int i = 0; i < dsLopSV.n; ++i) {
       SinhVien* a = searchSV(dsLopSV.nodes[i], maSV);
       if (a != NULL) {
           return a;
       }
   }
}
// //
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
           cout << "                                                             ";
           gotoXY(3, i + 3); cout << i;
           gotoXY(10, i + 3); cout << "| " << sv->MASV;
           gotoXY(18, i + 3); cout << "| " << sv->HO;
           gotoXY(40, i + 3); cout << "| " << sv->TEN;
           gotoXY(51, i + 3); cout << "| ";
           ShowCursor();
           //		        cin >> dssv->dk.DIEM;
           nhap_diem(point);
           //				cout << "Xac nhan!"
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
           cout << "                                                          ";
           gotoXY(3, i + 3); cout << i;
           gotoXY(10, i + 3); cout << "| " << sv->MASV;
           gotoXY(18, i + 3); cout << "| " << sv->HO;
           gotoXY(40, i + 3); cout << "| " << sv->TEN;
           gotoXY(51, i + 3);
           if (dssv->dk.DIEM == -1)  cout << "| --";
           else cout << "| " << fixed << setprecision(1) << dssv->dk.DIEM << endl;
           SetColor(7);
       }
       if (i == viTriChon_cu) {
           sv = Timsv(dsLopSV, dssv->dk.MASV);
           SetColor(7);
           gotoXY(0, i + 3);
           cout << "                                                          ";
           gotoXY(3, i + 3); cout << i;
           gotoXY(10, i + 3); cout << "| " << sv->MASV;
           gotoXY(18, i + 3); cout << "| " << sv->HO;
           gotoXY(40, i + 3); cout << "| " << sv->TEN;
           gotoXY(51, i + 3);
           if (dssv->dk.DIEM == -1)  cout << "| --";
           else cout << "| " << fixed << setprecision(1) << dssv->dk.DIEM << endl;
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
       gotoXY(10, i + 3); cout << "| " << sv->HO;
       gotoXY(40, i + 3); cout << "| " << sv->TEN;
       gotoXY(51, i + 3); 
       if (dssv->dk.DIEM == -1)  cout << "| --";
       else cout << "| " << fixed << setprecision(1) << dssv->dk.DIEM << endl;
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

// //
void Nhap_Bang_Diem(List_LTC& dsltc, string NK, string HK, string Nhom, string MH, DS_LOPSV& dsLop, int input, treeMH &root) {
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
   }
   else {
       if ((nhap_diem)->dssvdk == NULL) {
           cout << "Khong co sinh vien trong lop tin chi tren!\n";
       }
       else {
           if (input == 1) {
               int So_luong = DemSoSinhVien((nhap_diem)->dssvdk);
               int viTriChon = 1;
               bool ok = HienThiNhapDiem(nhap_diem, viTriChon, So_luong, dsLop);
           }
           else if (input == 0) {
               treeMH Monhoc = searchMH(root, MH);
               In_Diem_LTC(nhap_diem, Monhoc->mh.TENMH, dsLop);
           }
       }
   }
}
// //
void Nhap_Diem(List_LTC& dsltc, treeMH& root, DS_LOPSV& dsLop, int input) {
   cout << "==========NHAP-IN DIEM SINH VIEN=========\n";
   string NK, HK, Nhom, MH;
   do {
       cout << "Nhap nien khoa(An phim '|' de thoat): ";
       getline(cin, NK);
       if (NK == "|") {
           cout << "Da thoat!\n";
           return;
       }
       if (!kiemTraNienKhoa(NK)) {
           cout << "Loi: Nien khoa khong hop le. Vui long nhap lai!\n";
       }
       else break;
   } while (1);
   do {
       cout << "Nhap hoc ky(An phim '|' de thoat): ";
       getline(cin, HK);
       if (HK == "|") {
           cout << "Da thoat!\n";
           return;
       }
       if (!kiemTraChuoiSo(HK)) {
           cout << "Loi: Hoc ky la so nguyen duong. Vui long nhap lai!\n";
       }
       else break;
   } while (1);
   do {
       cout << "Nhap nhom(An phim '|' de thoat): ";
       getline(cin, Nhom);
       if (HK == "|") {
           cout << "Da thoat!\n";
           return;
       }
       if (!kiemTraChuoiSo(Nhom)) {
           cout << "Loi: Nhom la so nguyen duong. Vui long nhap lai!\n";
       }
       else break;
   } while (1);
   do {
       cout << "Nhap mon hoc(An phim '|' de thoat): ";
       getline(cin, MH);
       if (MH == "|") {
           cout << "Da thoat!\n";
           return;
       }
       if (_findTenMH(root, MH) == NULL) {
           cout << "Khong ton tai mon hoc nay!\n";
       }
       else break;
   } while (1);
   Nhap_Bang_Diem(dsltc, NK, HK, Nhom, MH, dsLop, input, root);
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
           Nhap_Diem(dsltc, root, dsLop, 1);
           break;
       case 1:
           Nhap_Diem(dsltc, root, dsLop, 0);
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
            ShowCur(true);
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

