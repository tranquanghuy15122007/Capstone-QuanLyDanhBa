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
    vector<QuanlyDanhba*> mangDanhBa[26];

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

    // chi cho phep ten co tu 2 ky tu tro len
    static bool TenHopLe(const string& ten) {
        return ten.length() >= 2 && ChiChuaChuVaKhoangTrang(ten);
    }

    static bool QuanHeHopLe(const string& qh) {
        return qh.empty() || (qh.length() >= 1 && ChiChuaChuVaKhoangTrang(qh));
    }

    static bool GhiChuHopLe(const string& note) {
        return note.empty() || (note.length() >= 1 && ChiChuaChuVaKhoangTrang(note));
    }

    // doc 1 dong va chuan hoa
    static string DocDong(istream& is) {
        string s;
        getline(is, s);
        return ChuanHoa(s);
    }

    // xoa ky tu xuong dong o cuoi va khoang trang o hai dau
    static string ChuanHoa(string s) {
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
        name = DocDong(is);

        while (!TenHopLe(name)) {
            cout << "Ten khong hop le! Nhap lai: ";
            name = DocDong(is);
        }

        cout << "Nhap SDT (dung 10 so va bat dau bang 0): ";
        phone = DocDong(is);

        while (!SDTHopLe(phone)) {
            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0 va chi duoc chua chu so)! Nhap lai: ";
            phone = DocDong(is);
        }

        cout << "Nhap quan he: ";
        relationship = DocDong(is);
        while (!QuanHeHopLe(relationship)) {
            cout << "Quan he khong hop le! Nhap lai: ";
            relationship = DocDong(is);
        }

        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        dateStr = DocDong(is);
        while (!dateStr.empty() && (!d.FromStringNoWarning(dateStr) || !d.IsValidDateNoWarning())) {
            cout << "Ngay sinh khong hop le hoac sai dinh dang! Nhap lai: ";
            dateStr = DocDong(is);
        }

        cout << "Nhap ghi chu: ";
        note = DocDong(is);
        while (!GhiChuHopLe(note)) {
            cout << "Nhap lai ghi chu: ";
            note = DocDong(is);
        }

        danhba.SetName(name);
        danhba.SetPhone(phone);
        danhba.SetRelationship(relationship);
        if (dateStr.empty() || !d.IsValidDateNoWarning())
        {
            d.SetDay(0);
            d.SetMonth(0);
            d.SetYear(0);
        }
        danhba.SetBirthday(d);
        danhba.SetNote(note);

        return is;
    }
};