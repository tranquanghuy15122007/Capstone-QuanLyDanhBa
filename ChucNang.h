#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "date.h"
#include "quanlydanhba.h"

using namespace std;

class ChucNang : public QuanlyDanhba
{
private:
    // Hàm phụ nội bộ để tính nhanh index (0-25) dựa vào tên chính
    int TinhIndex(const string& ten) const {
        size_t last_space = ten.rfind(' ');
        string tenChinh = (last_space != string::npos) ? ten.substr(last_space + 1) : ten;

        unsigned char c1 = tenChinh[0];
        int index = 0;
        if (c1 >= 'a' && c1 <= 'z') {
            index = c1 - 'a';
        }
        else if (c1 >= 'A' && c1 <= 'Z') {
            index = tolower(c1) - 'a';
        }
        if (index < 0 || index > 25) index = 0;
        return index;
    }

public:
    ChucNang(string _name = "", string _sdt = "", string _quanhe = "", Date _ngaysinh = Date(), string _ghichu = "")
        : QuanlyDanhba(_name, _sdt, _quanhe, _ngaysinh, _ghichu) {
    }
    // 4. Hàm hiển thị theo lựa chọn a-z hoặc z-a (có bắt lỗi nhập sai)
    void Hienthisapxep() {
        string arrange = "";
        cout << "\nNhap cach hien thi (a-z hoac z-a): ";
        cin >> arrange;

        while (arrange != "a-z" && arrange != "z-a") {
            cout << "Lua chon khong hop le! Vui long nhap lai (a-z hoac z-a): ";
            cin >> arrange;
        }

        if (arrange == "z-a") {
            Display_DESC();
        }
        else {
            Display();
        }
    }
    // 1. Hàm Thêm
    void Them(QuanlyDanhba* p) {
        int index = TinhIndex(p->GetName());
        getvector(index).push_back(p);
    }

    // 2. Hàm Xóa (Bắt nhập lại nếu sai yes/no, lặp lại nếu không tìm thấy)
    void Xoa() {
        string luachon;

        while (true) {
            cout << "Ban co muon xoa contact nao khong? (yes/no): ";
            cin >> luachon;

            if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs" || luachon == "no" || luachon == "NO" || luachon == "No") {
                break;
            }
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }

        if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs") 
        {
            bool daXoa = false;

            while (!daXoa) 
            {
                string tenCanXoa, sdtCanXoa;
                cout << "Nhap ten can xoa: ";
                cin.ignore();
                getline(cin, tenCanXoa);

                cout << "Nhap sdt can xoa: ";
                cin >> sdtCanXoa;

                int index = TinhIndex(tenCanXoa);
                vector<QuanlyDanhba*>& nhom = getvector(index);

                for (auto it = nhom.begin(); it != nhom.end(); ) {
                    if ((*it)->GetName() == tenCanXoa || (*it)->GetPhone() == sdtCanXoa) {
                        delete* it;
                        it = nhom.erase(it);
                        daXoa = true;
                    }
                    else {
                        ++it;
                    }
                }

                if (daXoa) {
                    cout << "Xoa contact thanh cong!\n";
                }
                else {
                    cout << "Khong tim thay contact nao khop thong tin! Vui long nhap lai.\n";
                }
            }
        }
        else {
            cout << "Bo qua thao tac xoa.\n";
        }
    }

    // 3. Hàm Sửa (Viết y hệt form của hàm Xóa: hỏi yes/no, nhập tìm kiếm, không thấy thì lặp lại)
    void Sua() {
        string luachon;

        while (true) {
            cout << "Ban co muon sua contact nao khong? (yes/no): ";
            cin >> luachon;

            if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs" || luachon == "no" || luachon == "NO" || luachon == "No") {
                break;
            }
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }

        if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs") {
            bool daSua = false;

            while (!daSua) {
                string tenCanSua, sdtCanSua;
                cout << "Nhap ten can sua: ";
                cin.ignore();
                getline(cin, tenCanSua);

                cout << "Nhap sdt can sua: ";
                cin >> sdtCanSua;

                int index = TinhIndex(tenCanSua);
                vector<QuanlyDanhba*>& nhom = getvector(index);

                for (auto& nguoi : nhom) {
                    if (nguoi->GetName() == tenCanSua || nguoi->GetPhone() == sdtCanSua) {
                        cout << "\nDa tim thay! Nhap thong tin moi:\n";

                        string newName, newPhone, newRel, newNote, newDateStr;

                        cout << "Nhap ho ten moi: ";
                        cin.ignore();
                        getline(cin, newName);
                        nguoi->SetName(newName);

                        cout << "Nhap SDT moi: ";
                        cin >> newPhone;
                        nguoi->SetPhone(newPhone);

                        cout << "Nhap quan he moi: ";
                        cin.ignore();
                        getline(cin, newRel);
                        nguoi->SetRelationship(newRel);

                        cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
                        cin >> newDateStr;
                        Date d;
                        d.FromString(newDateStr);
                        nguoi->SetBirthday(d);

                        cout << "Nhap ghi chu moi: ";
                        cin.ignore();
                        getline(cin, newNote);
                        nguoi->SetNote(newNote);

                        daSua = true;
                        cout << "Sua thong tin contact thanh cong!\n";
                        break;
                    }
                }

                if (!daSua) {
                    cout << "Khong tim thay contact nao khop thong tin! Vui long nhap lai.\n";
                }
            }
        }
        else {
            cout << "Bo qua thao tac sua.\n";
        }
    }
};