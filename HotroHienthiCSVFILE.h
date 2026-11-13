#pragma once

#include "ChucNang.h"
#include "date.h"
#include <fstream>
#include <sstream>
#include <iomanip>

class HotroHienthi : public ChucNang {
public:
    HotroHienthi(string _name = "", string _sdt = "", string _quanhe = "", Date _ngaysinh = Date(), string _ghichu = "")
        : ChucNang(_name, _sdt, _quanhe, _ngaysinh, _ghichu) {
    }//chỉ dùng khi nào có thuộc tính riêng

    void docFileDanhBa(string danhba) {
        ifstream file(danhba);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << danhba << " (Hay kiem tra lai vi tri file csv trong thu muc goc project!)\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string _name, _sdt, _quanhe, _ngaysinh_str, _ghichu;

            // Đọc đúng theo thứ tự: Tên, SĐT, Quan hệ, Ngày sinh, Ghi chú
            getline(ss, _name, ',');
            getline(ss, _sdt, ',');
            getline(ss, _quanhe, ',');
            getline(ss, _ngaysinh_str, ',');
            getline(ss, _ghichu, ',');

            // Xử lý chuỗi ngày sinh thành Date
            Date _ngaysinh;
            _ngaysinh.FromString(_ngaysinh_str);

            // Cấp phát động đối tượng mới
            QuanlyDanhba* newItem = new QuanlyDanhba(_name, _sdt, _quanhe, _ngaysinh, _ghichu);

            // Tách lấy Tên chính để phân loại vào các vector a-z
            size_t last_space = _name.rfind(' ');
            string tenChinh = _name;

            if (last_space != string::npos) {
                tenChinh = _name.substr(last_space + 1);
            }

            // Lấy ký tự đầu tiên để phân loại đơn giản
            unsigned char c1 = tenChinh[0];
            int index = 0;

            if (c1 >= 'a' && c1 <= 'z') {
                index = c1 - 'a';
            }
            else if (c1 >= 'A' && c1 <= 'Z') {
                index = tolower(c1) - 'a';
            }
            else {
                index = 0;
            }

            if (index < 0 || index > 25) index = 0;

            // Đẩy vào đúng vector nhóm
            getvector(index).push_back(newItem);
        }

        file.close();
        cout << "Load file vao class con thanh cong!\n\n";
    }
    void Capnhatfilekhithem(string danhba) {
        // Mở file ở chế độ ghi (ofstream)
        ofstream file(danhba); // Nếu muốn ghi nối tiếp (không xóa dữ liệu cũ) thì dùng: ofstream file(danhba, ios::app);
        if (!file.is_open()) {
            cout << "Khong the mo file de ghi: " << danhba << "\n";
            return;
        }

        // Duyệt qua cả 26 vector từ a đến z để lấy dữ liệu ghi ra file
        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = getvector(idx);
            for (const auto& nguoi : nhom) {
                file << nguoi->GetName() << ","
                    << nguoi->GetPhone() << ","
                    << nguoi->GetRelationship() << ","
                    << nguoi->GetBirthday().DateToString() << ","
                    << nguoi->GetNote() << "\n";
            }
        }

        file.close();
        cout << "Da cap nhat va luu lai file CSV thanh cong!\n";
    }
};