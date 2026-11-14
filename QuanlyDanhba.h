#pragma once
#include <iostream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include "date.h"
#include <limits>//cho getline

using namespace std;

class QuanlyDanhba
{
private:
    string Name;
    string Phone;
    string Relationship;//quanhe
    Date Birthday;
    string Note;

    vector<QuanlyDanhba*> a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z;

    friend istream& operator>>(istream& is, QuanlyDanhba& t);

public:
    QuanlyDanhba(string _name = "", string _phone = "", string _Relationship = "", Date _birth = Date(), string _note = "")
        : Name(_name), Phone(_phone), Relationship(_Relationship), Birthday(_birth), Note(_note)
    {
    }

    string GetName() const { return Name; }
    void SetName(string _name) { Name = _name; }
    string GetPhone() const { return Phone; }
    void SetPhone(string _phone) { Phone = _phone; }
    string GetRelationship() const { return Relationship; }
    void SetRelationship(string _Relationship) { Relationship = _Relationship; }
    string GetNote() const { return Note; }
    void SetNote(string _note) { Note = _note; }
    Date GetBirthday() const { return Birthday; }
    void SetBirthday(Date _birth) { Birthday = _birth; }

    // Hàm getvector trả về tham chiếu vector<QuanlyDanhba*>&
    vector<QuanlyDanhba*>& getvector(int index) {
        if (index < 0 || index > 25) {
            throw out_of_range("Index phai tu 0 den 25!");
        }

        vector<QuanlyDanhba*>* danhsach[] = {
           &a, &b, &c, &d, &e, &f, &g, &h, &i, &j, &k, &l, &m,
           &n, &o, &p, &q, &r, &s, &t, &u, &v, &w, &x, &y, &z
        };
        return *danhsach[index];
    }

    virtual ~QuanlyDanhba() {
        for (int i = 0; i < 26; i++) {
            for (auto ptr : getvector(i)) {
                delete ptr;
            }
            getvector(i).clear();
        }
    }

    void Display() {
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
                cout << "| " << left << setw(24) << nguoi->GetName()
                    << " | " << setw(13) << nguoi->GetPhone()
                    << " | " << setw(15) << nguoi->GetRelationship()
                    << " | " << setw(15) << nguoi->GetBirthday().DateToString()
                    << " | " << setw(34) << nguoi->GetNote() << " |\n";
            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }

    void Display_DESC() {
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int idx = 25; idx >= 0; idx--) {
            vector<QuanlyDanhba*>& nhom = getvector(idx);

            for (int i = static_cast<int>(nhom.size()) - 1; i >= 0; i--)
            {
                const auto& nguoi = nhom[i];
                cout << "| " << left << setw(24) << nguoi->GetName()
                    << " | " << setw(13) << nguoi->GetPhone()
                    << " | " << setw(15) << nguoi->GetRelationship()
                    << " | " << setw(15) << nguoi->GetBirthday().DateToString()
                    << " | " << setw(34) << nguoi->GetNote() << " |\n";
            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Hàm kiểm tra chỉ riêng Tên (để báo lưu ý)
    bool KiemTraTrungTen(const string& tenMoi) {
        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = getvector(idx);
            for (const auto& nguoi : nhom) {
                if (nguoi->GetName() == tenMoi) {
                    return true;
                }
            }
        }
        return false;
    }

    // Hàm kiểm tra trùng full cả Tên và SĐT (để chặn)
    bool KiemTraTrungFull(const string& tenMoi, const string& sdtMoi) {
        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = getvector(idx);
            for (const auto& nguoi : nhom) {
                if (nguoi->GetName() == tenMoi && nguoi->GetPhone() == sdtMoi) {
                    return true;
                }
            }
        }
        return false;
    }
};


istream& operator>>(istream& is, QuanlyDanhba& p) {

    cout << "Nhap ho ten: ";
    getline(is, p.Name);

    // Thông báo cảnh báo ngay khi nhập xong tên (cho phép trùng tên nhưng lưu ý SĐT)
    if (p.KiemTraTrungTen(p.Name)) {
        cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)!\n";
    }

    while (p.Name.empty() || p.Name.length() < 3)
    {
        cout << "Nhap lai ho ten: ";
        getline(is, p.Name);
    }

    cout << "Nhap SDT (dung 10 so va bat dau bang 0): ";
    getline(is, p.Phone);

    while (p.Phone.empty() || p.Phone.length() != 10 || p.Phone[0] != '0' || p.KiemTraTrungFull(p.Name, p.Phone))
    {
        if (p.KiemTraTrungFull(p.Name, p.Phone)) {
            cout << "Ten va SDT bi trung trong danh sach! Nhap lai SDT khac: ";
        }
        else 
        {
            cout << "Nhap lai SDT (dung 10 so va bat dau bang 0): ";
        }
        getline(is, p.Phone); // Nhập SĐT
    }

    cout << "Nhap quan he: ";
    getline(is, p.Relationship); // Nhập quan hệ đúng vào đây
    while (p.Relationship.empty() || p.Relationship.length() < 2)
    {
        cout << "Nhap quan he: ";
        getline(is, p.Relationship); // Nhập quan hệ đúng vào đây
    }

    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    string dateStr;
    getline(is, dateStr);
    p.Birthday.FromString(dateStr);

    // Vòng lặp kiểm tra: Nếu trống, hoặc chuỗi không phân tích được, hoặc ngày không hợp lệ thì bắt nhập lại
    while (p.Birthday.IsEmpty() || !p.Birthday.FromString(dateStr) || !p.Birthday.IsValidDate())
    {
        cout << "Ngay sinh khong hop le hoac sai dinh dang! Nhap lai: ";
        getline(is, dateStr);
        p.Birthday.FromString(dateStr); // <--- THIẾU DÒNG NÀY ĐÂY! Phải gọi lại để nó cập nhật giá trị mới
    }

    while (p.Note.empty())
    {
        cout << "Nhap ghi chu: ";
        is.ignore();
        getline(is, p.Note); // Nhập ghi chú (hoặc email) đúng vào đây
    }
    return is;
}