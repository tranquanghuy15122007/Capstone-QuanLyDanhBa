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

    // 26 vector tu a den z: mangDanhBa[0] la a, mangDanhBa[25] la z
    vector<QuanlyDanhba*> mangDanhBa[26];// nếu hỏi sao ở đây không khái báo như trước thì nó dựa vào hàm tinhindex nhe

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
            for (int j = 0; j < mangDanhBa[i].size(); j++) {
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
            for (int j = 0; j < mangDanhBa[i].size(); j++) {
                cout << "| " << left << setw(24) << mangDanhBa[i][j]->GetName()
                    << " | " << setw(13) << mangDanhBa[i][j]->GetPhone()
                    << " | " << setw(15) << mangDanhBa[i][j]->GetRelationship()
                    << " | " << setw(15) << mangDanhBa[i][j]->GetBirthday().DateToString()
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
            for (int j = (int)mangDanhBa[i].size() - 1; j >= 0; j--) {
                cout << "| " << left << setw(24) << mangDanhBa[i][j]->GetName()
                    << " | " << setw(13) << mangDanhBa[i][j]->GetPhone()
                    << " | " << setw(15) << mangDanhBa[i][j]->GetRelationship()
                    << " | " << setw(15) << mangDanhBa[i][j]->GetBirthday().DateToString()
                    << " | " << setw(34) << mangDanhBa[i][j]->GetNote() << " |\n";
            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }
};