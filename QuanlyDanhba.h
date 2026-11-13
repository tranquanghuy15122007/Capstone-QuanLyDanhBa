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
#include "hotro.h"

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
    // Hàm thêm contact vào đúng vector a-z (nhận vào con trỏ QuanlyDanhba*)

};


 istream& operator>>(istream& is, QuanlyDanhba& p) {
    cout << "Nhap ho ten: ";
    getline(is, p.Name);

    cout << "Nhap SDT: ";
    is >> p.Phone; // Nhập SĐT đúng vào đây

    cout << "Nhap quan he: ";
    is.ignore();
    getline(is, p.Relationship); // Nhập quan hệ đúng vào đây

    cout << "Nhap ngay sinh (dd/mm/yyyy): ";
    string dateStr;
    is >> dateStr;
    p.Birthday.FromString(dateStr); // Nhập ngày sinh đúng vào đây

    cout << "Nhap ghi chu: ";
    is.ignore();
    getline(is, p.Note); // Nhập ghi chú (hoặc email) đúng vào đây

    return is;
}