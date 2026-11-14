#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "date.h"
#include "quanlydanhba.h"
#include <cctype>// cho isdigit

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
        if (tenChinh.empty())
        {
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
    bool CoKyTuCoDau(const string& s) {
        for (unsigned char c : s) {
            if (c > 127)
                return true;
        }
        return false;
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

    bool ChiChuaChuVaKhoangTrang(const string& s) {
        for (char c : s) {
            if (!isalpha(static_cast<unsigned char>(c))
                && c != ' ')
                return false;
        }

        return true;
    }

    bool TenHopLe(const string& ten) {
        if (ten.length() < 2)
            return false;

        if (CoKyTuCoDau(ten))
            return false;

        if (!ChiChuaChuVaKhoangTrang(ten))
            return false;

        size_t viTri = ten.rfind(' ');
        string tenChinh = ten;

        if (viTri != string::npos)
            tenChinh = ten.substr(viTri + 1);

        if (tenChinh.empty())
            return false;

        if (!isalpha(
            static_cast<unsigned char>(tenChinh[0])))
            return false;

        return true;
    }

    bool QuanHeHopLe(const string& qh) {
        if (qh.length() < 2)
            return false;

        if (CoKyTuCoDau(qh))
            return false;

        if (!ChiChuaChuVaKhoangTrang(qh))
            return false;

        return true;
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

        while ( luachon != "yes" && luachon != "YES" && luachon != "Yes" && luachon != "YEs" &&
            luachon != "no" && luachon != "NO" && luachon != "No") {
            cout << "Lua chon khong hop le! Vui long nhap lai (yes/no): ";
            getline(cin, luachon);
        }

        if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs") {
            string arrange;
            cout << "\nNhap cach hien thi (a-z hoac z-a): ";
            getline(cin, arrange);

            while (arrange != "a-z" && arrange != "z-a") {
                cout << "Lua chon khong hop le! Vui long nhap lai (a-z hoac z-a): ";
                getline(cin, arrange);
            }

            if (arrange == "z-a") {
                Display_DESC();
            }
            else {
                Display();
            }
        }
    }

    string ChuanHoa(string s) {
        while (!s.empty() &&
            (s.back() == '\r' || s.back() == '\n')) {
            s.pop_back();
        }

        size_t dau = s.find_first_not_of(" \t");

        if (dau == string::npos) {
            return "";
        }

        size_t cuoi = s.find_last_not_of(" \t");

        return s.substr(dau, cuoi - dau + 1);
    }

    // kiem tra trung ten  // bỏ qua ở đây là kiểu nếu khi sửa lúc sửa á chưa có cập nhật mà đổi tên nguyễn văn a thành nguyễn văn a thì nó vẫn sẽ báo trùng
    // nên mới cần thêm tham số bỏ qua
    bool KiemTraTrungTen(string tenMoi,
        QuanlyDanhba* boQua = nullptr) {

        string t = ChuanHoa(tenMoi);

        transform(
            t.begin(),
            t.end(),
            t.begin(),
            ::tolower);

        for (int i = 0; i < 26; i++) {

            vector<QuanlyDanhba*>& nhom =
                getvector(i);

            for (size_t j = 0; j < nhom.size(); j++) {

                string tenCu =
                    ChuanHoa(
                        nhom[j]->GetName());

                transform(
                    tenCu.begin(),
                    tenCu.end(),
                    tenCu.begin(),
                    ::tolower);

                if (nhom[j] != boQua
                    && tenCu == t)
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

        // kiem tra sdt: du 10 ky tu, bat dau bang 0, toan la chu so
        while (!SDTHopLe(sdt)) {
            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0)! Nhap lai: ";
            getline(cin, sdt);
            sdt = ChuanHoa(sdt);
        }

        for (int i = 0; i < 26; i++) {
            for (size_t j = 0; j < getvector(i).size(); j++) {
                if (ChuanHoa(getvector(i)[j]->GetPhone()) == sdt) {
                    // in thong tin nguoi tim thay
                    cout << "---------------------------\n";
                    cout << "Tim thay: " << "\n";
                    cout << "Ho ten : " << getvector(i)[j]->GetName() << "\n";
                    cout << "SDT    : " << getvector(i)[j]->GetPhone() << "\n";
                    cout << "---------------------------\n";

                    // hoi xac nhan
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

                    if (xacNhan == "yes" || xacNhan == "YES" || xacNhan == "Yes") {
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

        // hoi xac nhan
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
            for (size_t j = 0; j + 1 < danhsach.size() - i; j++) 
            {
                
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