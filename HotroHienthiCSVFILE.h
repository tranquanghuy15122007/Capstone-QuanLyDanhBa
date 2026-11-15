#pragma once
#include "ChucNang.h"
#include "date.h"
#include <fstream>
#include <sstream>

class HotroHienthi : public ChucNang {
public:
    HotroHienthi(string _name = "", string _sdt = "", string _quanhe = "", Date _ngaysinh = Date(), string _ghichu = "")
        : ChucNang(_name, _sdt, _quanhe, _ngaysinh, _ghichu) {
    }

    // doc file csv vao danh ba
    void docFileDanhBa(const string& danhba) {
        ifstream file(danhba);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << danhba << " (Hay kiem tra lai vi tri file csv trong thu muc goc project!)\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            stringstream ss(line);
            string ten, sdt, quanhe, ngaysinhStr, ghichu;

            // thu tu: ten, sdt, quan he, ngay sinh, ghi chu
            getline(ss, ten, ',');
            getline(ss, sdt, ',');
            getline(ss, quanhe, ',');
            getline(ss, ngaysinhStr, ',');
            getline(ss, ghichu);

            if (!KiemTraTrungSDT(sdt)) //Kiem tra co trung SDT nao trong danh ba hien co khong? Neu ton tai thi bo qua thong tin lien lac dang doc.
            {
                // xoa khoang trang thua va ky tu \r
                ten = ChuanHoa(ten);
                sdt = ChuanHoa(sdt);
                quanhe = ChuanHoa(quanhe);
                ngaysinhStr = ChuanHoa(ngaysinhStr);
                ghichu = ChuanHoa(ghichu);

                Date ngaysinh;
                ngaysinh.FromString(ngaysinhStr);

                // tao contact roi bo vao vector dung chu cai (dung lai TinhIndex)
                QuanlyDanhba* newItem = new QuanlyDanhba(ten, sdt, quanhe, ngaysinh, ghichu);
                getvector(TinhIndex(ten)).push_back(newItem);
            }
        }

        file.close();
        cout << "Load file vao class con thanh cong!\n\n";
    }

    // ghi lai toan bo danh ba ra file csv
    void Capnhatfilekhithem(const string& danhba) {
        ofstream file(danhba);
        if (!file.is_open()) {
            cout << "Khong the mo file de ghi: " << danhba << "\n";
            return;
        }

        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);
            for (int j = 0; j < static_cast<int>(nhom.size()); j++) {
                file << nhom[j]->GetName() << ","
                    << nhom[j]->GetPhone() << ","
                    << nhom[j]->GetRelationship() << ","
                    << nhom[j]->GetBirthday().DateToString() << ","
                    << nhom[j]->GetNote() << "\n";
            }
        }

        file.close();
        cout << "Da cap nhat va luu lai file CSV thanh cong!\n";
    }
};