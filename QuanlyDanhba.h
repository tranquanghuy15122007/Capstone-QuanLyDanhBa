#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "date.h"

using namespace std;

class QuanlyDanhba
{
private:
    string Name;
    string Phone;
    string Relationship; // quanhe
    Date Birthday;
    string Note;

protected:
    // 26 vector tu a den z: mangDanhBa[0] la a, mangDanhBa[25] la z
    vector<QuanlyDanhba*> mangDanhBa[26];// nếu hỏi sao ở đây không khái báo như trước thì nó dựa vào hàm tinhindex nhe

    static bool SDTHopLe(const string& phone) {
        if (phone.length() != 10 || phone[0] != '0')
            return false;

        for (char c : phone) {
            if (!isdigit(static_cast<unsigned char>(c)))
                return false;
        }

        return true;
    }

    // chi cho phep chu cai (khong dau) va khoang trang
    static bool ChiChuaChuVaKhoangTrang(const string& s) {
        for (char c : s) {
            if (!isalpha(static_cast<unsigned char>(c)) && c != ' ')
                return false;
        }

        return true;
    }

    static bool TenHopLe(const string& ten) {
        return ten.length() >= 2 && ChiChuaChuVaKhoangTrang(ten);
    }

    static bool QuanHeHopLe(const string& qh) {
        return qh.length() >= 2 && ChiChuaChuVaKhoangTrang(qh);
    }

    static bool GhiChuHopLe(const string& note) {
        return !note.empty();
    }

public:
    QuanlyDanhba(string _name = "", string _phone = "", string _Relationship = "", Date _birth = Date(), string _note = "")
        : Name(_name), Phone(_phone), Relationship(_Relationship), Birthday(_birth), Note(_note)
    {
    }

    const string& GetName() const { return Name; }
    void SetName(const string& _name) { Name = _name; }
    const string& GetPhone() const { return Phone; }
    void SetPhone(const string& _phone) { Phone = _phone; }
    const string& GetRelationship() const { return Relationship; }
    void SetRelationship(const string& _Relationship) { Relationship = _Relationship; }
    const string& GetNote() const { return Note; }
    void SetNote(const string& _note) { Note = _note; }
    const Date& GetBirthday() const { return Birthday; }
    void SetBirthday(const Date& _birth) { Birthday = _birth; }

    // tra ve vector thu index (0 den 25)
    vector<QuanlyDanhba*>& getvector(int index) {
        if (index < 0 || index > 25) {
            throw out_of_range("Index phai tu 0 den 25!");
        }
        return mangDanhBa[index];
    }

    // xoa het cac contact con trong 26 vector
    virtual ~QuanlyDanhba() {
        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < static_cast<int>(mangDanhBa[i].size()); j++) {
                delete mangDanhBa[i][j];
            }
            mangDanhBa[i].clear();
        }
    }

    // hien thi tu a den z
    void Display() {
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int i = 0; i < 26; i++) {
            for (int j = 0; j < static_cast<int>(mangDanhBa[i].size()); j++) {
                Date dBirth = mangDanhBa[i][j]->GetBirthday();
                string strBirth = dBirth.IsValidDateNoWarning() ? dBirth.DateToString() : "";
                cout << "| " << left << setw(24) << mangDanhBa[i][j]->GetName()
                    << " | " << setw(13) << mangDanhBa[i][j]->GetPhone()
                    << " | " << setw(15) << mangDanhBa[i][j]->GetRelationship()
                    << " | " << setw(15) << strBirth
                    << " | " << setw(34) << mangDanhBa[i][j]->GetNote() << " |\n";
            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }

    // hien thi tu z den a
    void Display_DESC() {
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int i = 25; i >= 0; i--) {
            for (int j = static_cast<int>(mangDanhBa[i].size()) - 1; j >= 0; j--) {
                Date dBirth = mangDanhBa[i][j]->GetBirthday();
                string strBirth = dBirth.IsValidDateNoWarning() ? dBirth.DateToString() : "";
                cout << "| " << left << setw(24) << mangDanhBa[i][j]->GetName()
                    << " | " << setw(13) << mangDanhBa[i][j]->GetPhone()
                    << " | " << setw(15) << mangDanhBa[i][j]->GetRelationship()
                    << " | " << setw(15) << strBirth
                    << " | " << setw(34) << mangDanhBa[i][j]->GetNote() << " |\n";
            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }

    friend istream& operator>>(istream& is, QuanlyDanhba& danhba)
    {
        string name, phone, relationship, dateStr, note;
        Date d;

        cout << "Nhap ho ten: ";
        getline(is, name);

        while (!TenHopLe(name)) {
            cout << "Ten khong hop le! Nhap lai: ";
            getline(is, name);
        }

        cout << "Nhap SDT (dung 10 so va bat dau bang 0): ";
        getline(is, phone);

        while (!SDTHopLe(phone)) {
            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0 va chi duoc chua chu so)! Nhap lai: ";
            getline(is, phone);
        }

        cout << "Nhap quan he: ";
        getline(is, relationship);
        while (!QuanHeHopLe(relationship)) {
            cout << "Quan he khong hop le! Nhap lai: ";
            getline(is, relationship);
        }

        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        getline(is, dateStr);
        while (dateStr.empty() || !d.FromStringNoWarning(dateStr) || !d.IsValidDateNoWarning()) {
            cout << "Ngay sinh khong hop le hoac sai dinh dang! Nhap lai: ";
            getline(is, dateStr);
        }

        cout << "Nhap ghi chu: ";
        getline(is, note);
        while (!GhiChuHopLe(note)) {
            cout << "Nhap lai ghi chu: ";
            getline(is, note);
        }

        danhba.SetName(name);
        danhba.SetPhone(phone);
        danhba.SetRelationship(name);
        danhba.SetBirthday(d);
        danhba.SetNote(note);

        return is;
    }
};