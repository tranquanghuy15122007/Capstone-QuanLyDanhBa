#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "date.h"
#include "Contact.h"

using namespace std;

class QuanlyDanhba
{
    // 26 vector tu a den z: mangDanhBa[0] la a, mangDanhBa[25] la z
    vector<Contact*> mangDanhBa[26];// nếu hỏi sao ở đây không khái báo như trước thì nó dựa vào hàm tinhindex nhe
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
public:
    QuanlyDanhba(){}

    // tra ve vector thu index (0 den 25)
    vector<Contact*>& getvector(int index) {
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