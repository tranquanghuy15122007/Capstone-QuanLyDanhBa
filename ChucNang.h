#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "date.h"
#include "quanlydanhba.h"

using namespace std;

class ChucNang : public QuanlyDanhba
{
protected:
    // tinh xem ten bat dau bang chu nao thi vao vector so may
    int TinhIndex(string ten) {
        size_t viTri = ten.rfind(' ');
        string tenChinh = ten;
        if (viTri != string::npos) {
            tenChinh = ten.substr(viTri + 1);
        }
        if (tenChinh.empty()) {
            return 0;
        }

        char c = tenChinh[0];
        int index = 0;
        if (c >= 'a' && c <= 'z') {
            index = c - 'a';
        }
        else if (c >= 'A' && c <= 'Z') {
            index = c - 'A';
        }
        return index;
    }

    bool SDTHopLe(const string& phone) {
        if (phone.length() != 10 || phone[0] != '0')
            return false;

        for (char c : phone) {
            if (!isdigit(static_cast<unsigned char>(c)))
                return false;
        }

        return true;
    }

    // chi cho phep chu cai (khong dau) va khoang trang
    bool ChiChuaChuVaKhoangTrang(const string& s) {
        for (char c : s) {
            if (!isalpha(static_cast<unsigned char>(c)) && c != ' ')
                return false;
        }

        return true;
    }

    bool TenHopLe(const string& ten) {
        return ten.length() >= 2 && ChiChuaChuVaKhoangTrang(ten);
    }

    bool QuanHeHopLe(const string& qh) {
        return qh.length() >= 2 && ChiChuaChuVaKhoangTrang(qh);
    }

    bool GhiChuHopLe(const string& note) {
        return !note.empty();
    }

public:
    ChucNang(string _name = "", string _sdt = "", string _quanhe = "", Date _ngaysinh = Date(), string _ghichu = "")
        : QuanlyDanhba(_name, _sdt, _quanhe, _ngaysinh, _ghichu) {
    }

    // xoa ky tu xuong dong o cuoi va khoang trang o hai dau
    string ChuanHoa(string s) {
        while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) {
            s.pop_back();
        }

        size_t dau = s.find_first_not_of(" \t");

        if (dau == string::npos) {
            return "";
        }

        size_t cuoi = s.find_last_not_of(" \t");

        return s.substr(dau, cuoi - dau + 1);
    }

    // doc 1 dong va chuan hoa
    string DocDong() {
        string s;
        getline(cin, s);
        return ChuanHoa(s);
    }

    // hoi yes/no, tra ve true neu yes, false neu no
    bool XacNhan(const string& cauHoi) {
        cout << cauHoi << " (yes/no): ";
        string s = DocDong();
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        while (s != "yes" && s != "no") {
            cout << "Lua chon khong hop le! Vui long nhap lai (yes/no): ";
            s = DocDong();
            transform(s.begin(), s.end(), s.begin(), ::tolower);
        }
        return s == "yes";
    }

    // hoi cach hien thi a-z hoac z-a
    void Hienthisapxep() {
        string arrange;
        cout << "\nNhap cach hien thi (a-z hoac z-a): ";
        arrange = DocDong();

        while (arrange != "a-z" && arrange != "a-Z" && arrange != "A-z" && arrange != "A-Z" &&
            arrange != "z-a" && arrange != "z-A" && arrange != "Z-a" && arrange != "Z-A") {
            cout << "Lua chon khong hop le! Vui long nhap lai (a-z hoac z-a): ";
            arrange = DocDong();
        }

        if (arrange == "z-a" || arrange == "z-A" || arrange == "Z-a" || arrange == "Z-A")
        {
            Display_DESC();
        }
        else {
            Display();
        }
    }

    // kiem tra trung ten
    // boQua: bo qua nguoi dang sua, neu khong khi sua "nguyen van a" thanh "nguyen van a" van bi bao trung
    bool KiemTraTrungTen(string tenMoi, QuanlyDanhba* boQua = nullptr) {
        string t = ChuanHoa(tenMoi);
        transform(t.begin(), t.end(), t.begin(), ::tolower);

        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);

            for (size_t j = 0; j < nhom.size(); j++) {
                string tenCu = ChuanHoa(nhom[j]->GetName());
                transform(tenCu.begin(), tenCu.end(), tenCu.begin(), ::tolower);

                if (nhom[j] != boQua && tenCu == t)
                    return true;
            }
        }

        return false;
    }

    // kiem tra trung SDT (bo qua nguoi dang sua)
    bool KiemTraTrungSDT(string sdtMoi, QuanlyDanhba* boQua = nullptr) {
        string s = ChuanHoa(sdtMoi);
        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                if (nhom[j] != boQua && ChuanHoa(nhom[j]->GetPhone()) == s) {
                    return true;
                }
            }
        }
        return false;
    }

    // 1. Them contact
    void Them() {
        string name, phone, relationship, dateStr, note;
        Date d;

        cout << "Nhap ho ten: ";
        name = DocDong();

        while (!TenHopLe(name)) {
            cout << "Ten khong hop le! Nhap lai: ";
            name = DocDong();
        }

        if (KiemTraTrungTen(name)) {
            cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)" << endl;
        }

        cout << "Nhap SDT (dung 10 so va bat dau bang 0): ";
        phone = DocDong();

        while (!SDTHopLe(phone) || KiemTraTrungSDT(phone)) {
            if (SDTHopLe(phone) && KiemTraTrungSDT(phone)) {
                cout << "Loi: SDT nay da ton tai trong danh sach! Vui long nhap lai SDT khac: ";
            }
            else {
                cout << "SDT khong hop le (phai du 10 so va bat dau bang 0 va chi duoc chua chu so)! Nhap lai: ";
            }
            phone = DocDong();
        }

        cout << "Nhap quan he: ";
        relationship = DocDong();
        while (!QuanHeHopLe(relationship)) {
            cout << "Quan he khong hop le! Nhap lai: ";
            relationship = DocDong();
        }

        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        dateStr = DocDong();
        while (dateStr.empty() || !d.FromString(dateStr) || !d.IsValidDate()) {
            cout << "Ngay sinh khong hop le hoac sai dinh dang! Nhap lai: ";
            dateStr = DocDong();
        }

        cout << "Nhap ghi chu: ";
        note = DocDong();
        while (!GhiChuHopLe(note)) {
            cout << "Nhap lai ghi chu: ";
            note = DocDong();
        }

        if (!XacNhan("Ban co chac chan muon them lien lac nay khong?")) {
            cout << "Da huy thao tac them.\n";
            return;
        }

        QuanlyDanhba* p = new QuanlyDanhba(name, phone, relationship, d, note);
        int index = TinhIndex(name);
        getvector(index).push_back(p);
        cout << "Them contact vao danh ba thanh cong!\n";
        Hienthisapxep();
    }

    // 2. Xoa contact theo ten + sdt: tra ve true neu da xoa, false neu khong xoa
    bool Xoa() {
        string ten, sdt;

        cout << "Nhap ho ten can xoa: ";
        ten = DocDong();
        while (!TenHopLe(ten)) {
            cout << "Ten khong hop le! Nhap lai: ";
            ten = DocDong();
        }

        cout << "Nhap SDT can xoa (dung 10 so va bat dau bang 0): ";
        sdt = DocDong();
        while (!SDTHopLe(sdt)) {
            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0)! Nhap lai: ";
            sdt = DocDong();
        }

        string tenTim = ten;
        transform(tenTim.begin(), tenTim.end(), tenTim.begin(), ::tolower);

        // tim nguoi khop ca ten va sdt
        for (int i = 0; i < 26; i++) {
            for (size_t j = 0; j < getvector(i).size(); j++) {
                string tenCu = ChuanHoa(getvector(i)[j]->GetName());
                transform(tenCu.begin(), tenCu.end(), tenCu.begin(), ::tolower);

                if (tenCu == tenTim && ChuanHoa(getvector(i)[j]->GetPhone()) == sdt) {
                    cout << "---------------------------\n";
                    cout << "Tim thay: " << "\n";
                    cout << "Ho ten : " << getvector(i)[j]->GetName() << "\n";
                    cout << "SDT    : " << getvector(i)[j]->GetPhone() << "\n";
                    cout << "---------------------------\n";

                    if (XacNhan("Ban co chac chan muon xoa nguoi nay khong?")) {
                        delete getvector(i)[j];
                        getvector(i).erase(getvector(i).begin() + j);
                        cout << "Xoa contact thanh cong!\n";
                        Hienthisapxep();
                        return true;
                    }
                    else {
                        cout << "Da huy thao tac xoa.\n";
                        return false;
                    }
                }
            }
        }

        cout << "Khong tim thay nguoi nao co ten va SDT nay trong danh sach!\n";
        return false;
    }

    // 3. Sua contact theo sdt: tra ve true neu da sua, false neu khong sua
    bool Sua() {
        string sdt;
        do {
            cout << "Nhap SDT can sua (dung 10 so va bat dau bang 0): ";
            sdt = DocDong();

            if (!SDTHopLe(sdt)) {
                cout << "SDT khong hop le!\n";
            }
        } while (!SDTHopLe(sdt));

        // tim nguoi co sdt nay
        QuanlyDanhba* target = nullptr;
        int oldI = -1;
        int oldJ = -1;
        for (int i = 0; i < 26; i++) {
            for (size_t j = 0; j < getvector(i).size(); j++) {
                if (ChuanHoa(getvector(i)[j]->GetPhone()) == sdt) {
                    target = getvector(i)[j];
                    oldI = i;
                    oldJ = (int)j;
                    break;
                }
            }

            if (target != nullptr)
                break;
        }

        if (target == nullptr) {
            cout << "Khong tim thay nguoi nao co SDT nay trong danh sach!\n";
            return false;
        }

        cout << "---------------------------\n";
        cout << "Tim thay: " << "\n";
        cout << "Ho ten : " << target->GetName() << "\n";
        cout << "SDT    : " << target->GetPhone() << "\n";
        cout << "---------------------------\n";

        if (!XacNhan("Ban co chac chan muon sua nguoi nay khong?")) {
            cout << "Da huy thao tac sua.\n";
            return false;
        }

        // nhap thong tin moi
        string ten, sdtMoi, quanhe, ghichu, ngaysinhStr, chon;
        bool daSua = false;

        do {
            // menu chon muc can sua
            cout << "\n===== CHON MUC BAN MUON SUA =====\n";
            cout << "1. Sua ho ten     (hien tai: " << target->GetName() << ")\n";
            cout << "2. Sua SDT        (hien tai: " << target->GetPhone() << ")\n";
            cout << "3. Sua quan he    (hien tai: " << target->GetRelationship() << ")\n";
            cout << "4. Sua ngay sinh  (hien tai: " << target->GetBirthday().DateToString() << ")\n";
            cout << "5. Sua ghi chu    (hien tai: " << target->GetNote() << ")\n";
            cout << "6. Sua tat ca\n";
            cout << "0. Hoan tat\n";
            cout << "Nhap lua chon: ";
            chon = DocDong();

            while (chon != "0" && chon != "1" && chon != "2" && chon != "3" &&
                chon != "4" && chon != "5" && chon != "6") {
                cout << "Lua chon khong hop le! Vui long nhap lai (0-6): ";
                chon = DocDong();
            }

            if (chon == "1" || chon == "6") {
                cout << "Nhap ho ten: ";
                ten = DocDong();

                while (!TenHopLe(ten)) {
                    cout << "Ten khong hop le! Nhap lai: ";
                    ten = DocDong();
                }

                if (KiemTraTrungTen(ten, target)) {
                    cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)" << endl;
                }
                target->SetName(ten);
                daSua = true;
            }

            if (chon == "2" || chon == "6") {
                cout << "Nhap SDT moi (dung 10 so va bat dau bang 0): ";
                sdtMoi = DocDong();

                while (!SDTHopLe(sdtMoi) || KiemTraTrungSDT(sdtMoi, target)) {
                    if (SDTHopLe(sdtMoi) && KiemTraTrungSDT(sdtMoi, target)) {
                        cout << "SDT da ton tai! Nhap lai: ";
                    }
                    else {
                        cout << "SDT khong hop le! Nhap lai: ";
                    }
                    sdtMoi = DocDong();
                }
                target->SetPhone(sdtMoi);
                daSua = true;
            }

            if (chon == "3" || chon == "6") {
                cout << "Nhap quan he moi: ";
                quanhe = DocDong();
                while (!QuanHeHopLe(quanhe)) {
                    cout << "Quan he khong hop le! Nhap lai: ";
                    quanhe = DocDong();
                }
                target->SetRelationship(quanhe);
                daSua = true;
            }

            if (chon == "4" || chon == "6") {
                Date d;
                cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
                ngaysinhStr = DocDong();
                while (ngaysinhStr.empty() || !d.FromString(ngaysinhStr) || !d.IsValidDate()) {
                    cout << "Ngay sinh khong hop le! Nhap lai: ";
                    ngaysinhStr = DocDong();
                }
                target->SetBirthday(d);
                daSua = true;
            }

            if (chon == "5" || chon == "6") {
                cout << "Nhap ghi chu moi: ";
                ghichu = DocDong();
                while (!GhiChuHopLe(ghichu)) {
                    cout << "Nhap lai ghi chu: ";
                    ghichu = DocDong();
                }
                target->SetNote(ghichu);
                daSua = true;
            }

            if (chon == "6") {
                chon = "0"; // sua tat ca xong thi thoat
            }
        } while (chon != "0");

        if (!daSua) {
            cout << "Ban chua sua gi ca.\n";
            return false;
        }

        // neu doi chu cai dau thi chuyen sang vector khac
        int newI = TinhIndex(target->GetName());
        if (newI != oldI) {
            getvector(oldI).erase(getvector(oldI).begin() + oldJ);
            getvector(newI).push_back(target);
        }

        cout << "Sua thong tin contact thanh cong!\n";
        Hienthisapxep();
        return true;
    }

    // Loc theo nhom quan he
    void LocTheoTenNhom() {
        string findRelation;

        if (!XacNhan("Ban co chac chan muon loc lien lac theo nhom quan he khong?")) {
            cout << "Da huy thao tac loc.\n";
            return;
        }

        cout << "Nhap ten nhom quan he can loc: ";
        findRelation = DocDong();

        while (!QuanHeHopLe(findRelation)) {
            cout << "Ten nhom quan he khong hop le! Nhap lai: ";
            findRelation = DocDong();
        }
        cout << endl;

        // doi het ve chu thuong de so sanh
        transform(findRelation.begin(), findRelation.end(), findRelation.begin(), ::tolower);

        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                string relationship = nhom[j]->GetRelationship();
                transform(relationship.begin(), relationship.end(), relationship.begin(), ::tolower);

                if (relationship.find(findRelation) != string::npos) {
                    cout << "| " << left << setw(24) << nhom[j]->GetName()
                        << " | " << setw(13) << nhom[j]->GetPhone()
                        << " | " << setw(15) << nhom[j]->GetRelationship()
                        << " | " << setw(15) << nhom[j]->GetBirthday().DateToString()
                        << " | " << setw(34) << nhom[j]->GetNote() << " |\n";
                }
            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }

    // Danh sach sap sinh nhat trong nam
    void DanhSachSapSinhNhat() {
        if (!XacNhan("Ban co chac chan muon xem danh sach lien lac sap sinh nhat khong?")) {
            cout << "Da huy thao tac xem.\n";
            return;
        }

        vector<QuanlyDanhba*> danhsach;

        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                if (nhom[j]->GetBirthday().DemSoNgayDenSinhNhatTrongNam() >= 0) {
                    danhsach.push_back(nhom[j]);
                }
            }
        }

        // sap xep noi bot theo so ngay den sinh nhat tang dan
        for (size_t i = 0; i + 1 < danhsach.size(); i++) {
            for (size_t j = 0; j + 1 < danhsach.size() - i; j++) {
                int ngay1 = danhsach[j]->GetBirthday().DemSoNgayDenSinhNhatTrongNam();
                int ngay2 = danhsach[j + 1]->GetBirthday().DemSoNgayDenSinhNhatTrongNam();
                if (ngay1 > ngay2) {
                    QuanlyDanhba* tam = danhsach[j];
                    danhsach[j] = danhsach[j + 1];
                    danhsach[j + 1] = tam;
                }
            }
        }

        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (size_t i = 0; i < danhsach.size(); i++) {
            cout << "| " << left << setw(24) << danhsach[i]->GetName()
                << " | " << setw(13) << danhsach[i]->GetPhone()
                << " | " << setw(15) << danhsach[i]->GetRelationship()
                << " | " << setw(15) << danhsach[i]->GetBirthday().DateToString()
                << " | " << setw(34) << danhsach[i]->GetNote() << " |\n";
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }
};
