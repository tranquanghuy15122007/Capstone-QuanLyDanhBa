#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "date.h"
#include "quanlydanhba.h"
#include "GetLastName.h"

using namespace std;

class ChucNang : public QuanlyDanhba
{
protected:
    // Luu noi dung cac lan tim kiem theo ten và SST.
    vector<string> lichSuTimKiem;

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

    // hoi co muon hien bang khong, neu yes thi hoi a-z hoac z-a
    void Hienthisapxep() {
        string luachon;
        cout << "\nBan co muon hien bang danh ba khong? (yes/no): ";
        getline(cin, luachon);

        while (luachon != "yes" && luachon != "YES" && luachon != "Yes" && luachon != "YEs" &&
            luachon != "no" && luachon != "NO" && luachon != "No") {
            cout << "Lua chon khong hop le! Vui long nhap lai (yes/no): ";
            getline(cin, luachon);
        }

        if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs") {
            string arrange;
            cout << "\nNhap cach hien thi (a-z hoac z-a): ";
            getline(cin, arrange);

            while (arrange != "a-z" && arrange != "a-Z" && arrange != "A-z" && arrange != "A-Z" &&
                arrange != "z-a" && arrange != "z-A" && arrange != "Z-a" && arrange != "Z-A") {
                cout << "Lua chon khong hop le! Vui long nhap lai (a-z hoac z-a): ";
                getline(cin, arrange);
            }

            if (arrange == "z-a" || arrange == "z-A" || arrange == "Z-a" || arrange == "Z-A") 
            {
                Display_DESC();
            }
            else {
                Display();
            }
        }
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
        cout << "Nhap ho ten: ";
        getline(cin, name);
        name = ChuanHoa(name);

        while (!TenHopLe(name)) {
            cout << "Ten khong hop le! Nhap lai: ";
            getline(cin, name);
            name = ChuanHoa(name);
        }

        if (KiemTraTrungTen(name)) {
            cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)" << endl;
        }

        cout << "Nhap SDT (dung 10 so va bat dau bang 0): ";
        getline(cin, phone);
        phone = ChuanHoa(phone);

        while (!SDTHopLe(phone) || KiemTraTrungSDT(phone)) {
            if (SDTHopLe(phone) && KiemTraTrungSDT(phone)) {
                cout << "Loi: SDT nay da ton tai trong danh sach! Vui long nhap lai SDT khac: ";
            }
            else {
                cout << "SDT khong hop le (phai du 10 so va bat dau bang 0 va chi duoc chua chu so)! Nhap lai: ";
            }

            getline(cin, phone);
            phone = ChuanHoa(phone);
        }

        cout << "Nhap quan he: ";
        getline(cin, relationship);
        relationship = ChuanHoa(relationship);
        while (!QuanHeHopLe(relationship)) {
            cout << "Quan he khong hop le! Nhap lai: ";
            getline(cin, relationship);
            relationship = ChuanHoa(relationship);
        }

        Date d;
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(cin, dateStr);
        dateStr = ChuanHoa(dateStr);
        while (dateStr.empty() || !d.FromString(dateStr) || !d.IsValidDate()) {
            cout << "Ngay sinh khong hop le hoac sai dinh dang! Nhap lai: ";
            getline(cin, dateStr);
            dateStr = ChuanHoa(dateStr);
        }

        cout << "Nhap ghi chu: ";
        getline(cin, note);
        note = ChuanHoa(note);
        while (!GhiChuHopLe(note)) {
            cout << "Nhap lai ghi chu: ";
            getline(cin, note);
            note = ChuanHoa(note);
        }

        QuanlyDanhba* p = new QuanlyDanhba(name, phone, relationship, d, note);
        int index = TinhIndex(name);
        getvector(index).push_back(p);
        cout << "Them contact vao danh ba thanh cong!\n";
        Hienthisapxep();
    }

    // 2. Xoa contact theo sdt: tra ve true neu da xoa, false neu khong xoa
    bool Xoa() {
        string sdt;
        cout << "Nhap SDT can xoa (dung 10 so va bat dau bang 0): ";
        getline(cin, sdt);
        sdt = ChuanHoa(sdt);

        while (!SDTHopLe(sdt)) {
            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0)! Nhap lai: ";
            getline(cin, sdt);
            sdt = ChuanHoa(sdt);
        }

        for (int i = 0; i < 26; i++) {
            for (size_t j = 0; j < getvector(i).size(); j++) {
                if (ChuanHoa(getvector(i)[j]->GetPhone()) == sdt) {
                    cout << "---------------------------\n";
                    cout << "Tim thay: " << "\n";
                    cout << "Ho ten : " << getvector(i)[j]->GetName() << "\n";
                    cout << "SDT    : " << getvector(i)[j]->GetPhone() << "\n";
                    cout << "---------------------------\n";

                    string xacNhan;
                    cout << "Ban co chac chan muon xoa nguoi nay khong? (yes/no): ";
                    getline(cin, xacNhan);
                    xacNhan = ChuanHoa(xacNhan);
                    while (xacNhan != "yes" && xacNhan != "YES" && xacNhan != "Yes" && xacNhan != "YEs" &&
                        xacNhan != "no" && xacNhan != "NO" && xacNhan != "No") {
                        cout << "Lua chon khong hop le! Vui long nhap lai (yes/no): ";
                        getline(cin, xacNhan);
                        xacNhan = ChuanHoa(xacNhan);
                    }

                    if (xacNhan == "yes" || xacNhan == "YES" || xacNhan == "Yes" || xacNhan == "YEs") {
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

        cout << "Khong tim thay nguoi nao co SDT nay trong danh sach!\n";
        return false;
    }

    // 3. Sua contact theo sdt: tra ve true neu da sua, false neu khong sua
    bool Sua() {
        string sdt;
        do {
            cout << "Nhap SDT can sua (dung 10 so va bat dau bang 0): ";
            getline(cin, sdt);
            sdt = ChuanHoa(sdt);

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

        string xacNhan;
        cout << "Ban co chac chan muon sua nguoi nay khong? (yes/no): ";
        getline(cin, xacNhan);
        xacNhan = ChuanHoa(xacNhan);
        while (xacNhan != "yes" && xacNhan != "YES" && xacNhan != "Yes" && xacNhan != "YEs" &&
            xacNhan != "no" && xacNhan != "NO" && xacNhan != "No") {
            cout << "Lua chon khong hop le! Vui long nhap lai (yes/no): ";
            getline(cin, xacNhan);
            xacNhan = ChuanHoa(xacNhan);
        }
        if (xacNhan == "no" || xacNhan == "NO" || xacNhan == "No") {
            cout << "Da huy thao tac sua.\n";
            return false;
        }

        // nhap thong tin moi
        string ten, sdtMoi, quanhe, ghichu, ngaysinhStr;
        cout << "Nhap ho ten: ";
        getline(cin, ten);
        ten = ChuanHoa(ten);

        while (!TenHopLe(ten)) {
            cout << "Ten khong hop le! Nhap lai: ";
            getline(cin, ten);
            ten = ChuanHoa(ten);
        }

        if (KiemTraTrungTen(ten, target)) {
            cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)" << endl;
        }

        cout << "Nhap SDT moi (dung 10 so va bat dau bang 0): ";
        getline(cin, sdtMoi);
        sdtMoi = ChuanHoa(sdtMoi);

        while (!SDTHopLe(sdtMoi) || KiemTraTrungSDT(sdtMoi, target)) {
            if (SDTHopLe(sdtMoi) && KiemTraTrungSDT(sdtMoi, target)) {
                cout << "SDT da ton tai! Nhap lai: ";
            }
            else {
                cout << "SDT khong hop le! Nhap lai: ";
            }

            getline(cin, sdtMoi);
            sdtMoi = ChuanHoa(sdtMoi);
        }

        cout << "Nhap quan he moi: ";
        getline(cin, quanhe);
        quanhe = ChuanHoa(quanhe);
        while (!QuanHeHopLe(quanhe)) {
            cout << "Quan he khong hop le! Nhap lai: ";
            getline(cin, quanhe);
            quanhe = ChuanHoa(quanhe);
        }

        Date d;
        cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
        getline(cin, ngaysinhStr);
        ngaysinhStr = ChuanHoa(ngaysinhStr);
        while (ngaysinhStr.empty() || !d.FromString(ngaysinhStr) || !d.IsValidDate()) {
            cout << "Ngay sinh khong hop le! Nhap lai: ";
            getline(cin, ngaysinhStr);
            ngaysinhStr = ChuanHoa(ngaysinhStr);
        }

        cout << "Nhap ghi chu moi: ";
        getline(cin, ghichu);
        ghichu = ChuanHoa(ghichu);
        while (!GhiChuHopLe(ghichu)) {
            cout << "Nhap lai ghi chu: ";
            getline(cin, ghichu);
            ghichu = ChuanHoa(ghichu);
        }

        // cap nhat thong tin
        target->SetName(ten);
        target->SetPhone(sdtMoi);
        target->SetRelationship(quanhe);
        target->SetBirthday(d);
        target->SetNote(ghichu);

        // neu doi chu cai dau thi chuyen sang vector khac
        int newI = TinhIndex(ten);
        if (newI != oldI) {
            getvector(oldI).erase(getvector(oldI).begin() + oldJ);
            getvector(newI).push_back(target);
        }

        cout << "Sua thong tin contact thanh cong!\n";
        Hienthisapxep();
        return true;
    }

    //Hien thi danh sach lien he tim kiem theo ten
    void TimTheoTen()
    {
        string findName;
        cout << "Nhap ten lien he can tim: ";
        getline(cin, findName);
        cout << endl;

        string keyword = findName;
        transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
        lichSuTimKiem.push_back("Ten: " + keyword);
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = getvector(idx);
            for (const auto& nguoi : nhom) {

                string name = GetLastName(nguoi->GetName());
                transform(name.begin(), name.end(), name.begin(), ::tolower);

                transform(findName.begin(), findName.end(), findName.begin(), ::tolower);

                if (name.find(findName) != string::npos)
                {
                    cout << "| " << left << setw(24) << nguoi->GetName()
                        << " | " << setw(13) << nguoi->GetPhone()
                        << " | " << setw(15) << nguoi->GetRelationship()
                        << " | " << setw(15) << nguoi->GetBirthday().DateToString()
                        << " | " << setw(34) << nguoi->GetNote() << " |\n";
                }

            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }


    //Hien thi danh sach lien he tim kiem theo so dien thoai
    void TimTheoSDT()
    {
        string findPhone;
        cout << "Nhap so dien thoai can tim: ";
        getline(cin, findPhone);
        cout << endl;
        lichSuTimKiem.push_back("SDT: " + findPhone);
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = getvector(idx);
            for (const auto& nguoi : nhom) {

                string phone = nguoi->GetPhone();
                transform(phone.begin(), phone.end(), phone.begin(), ::tolower);

                transform(findPhone.begin(), findPhone.end(), findPhone.begin(), ::tolower);

                if (phone.find(findPhone) != string::npos)
                {
                    cout << "| " << left << setw(24) << nguoi->GetName()
                        << " | " << setw(13) << nguoi->GetPhone()
                        << " | " << setw(15) << nguoi->GetRelationship()
                        << " | " << setw(15) << nguoi->GetBirthday().DateToString()
                        << " | " << setw(34) << nguoi->GetNote() << " |\n";
                }

            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }


    // Hien thi lich su tim kiem tu moi nhat den cu nhat.
    void HienThiLichSuTimKiem()
    {
        if (lichSuTimKiem.empty())
        {
            cout << "Chua co lich su tim kiem!\n";
            return;
        }

        cout << "+" << string(32, '-') << "+\n";
        cout << "| " << left << setw(30) << "Lich su tim kiem" << " |\n";
        cout << "+" << string(32, '-') << "+\n";

        for (int i = (int)lichSuTimKiem.size() - 1; i >= 0; i--)
        {
            cout << "| " << left << setw(30) << lichSuTimKiem[i] << " |\n";
        }

        cout << "+" << string(32, '-') << "+\n";
    }

    // Loc theo nhom quan he
    void LocTheoTenNhom() {
        string findRelation;
        cout << "Nhap ten nhom quan he can loc: ";

        getline(cin, findRelation);
        findRelation = ChuanHoa(findRelation);
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
