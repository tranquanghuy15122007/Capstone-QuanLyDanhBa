#pragma once
#include "NoteDB.h"

class DanhBaYeuThich : public NoteDB
{
private:
    vector<string> dsYeuThich;

public:
    void ThemYeuThich() {
        QuanlyDanhba* p = NhapVaTimSDT("Nhap SDT muon them vao yeu thich: ");
        if (p == nullptr) return;

        if (find(dsYeuThich.begin(), dsYeuThich.end(), p->GetPhone()) != dsYeuThich.end()) {
            cout << "SDT nay da co trong yeu thich!\n";
            return;
        }
        dsYeuThich.push_back(p->GetPhone());
        cout << "Da them " << p->GetName() << " vao yeu thich!\n";
    }

    void XoaYeuThich() {
        if (dsYeuThich.empty()) {
            cout << "Danh ba yeu thich dang trong!\n";
            return;
        }
        HienThiYeuThich();

        string sdt;
        cout << "Nhap SDT muon xoa khoi yeu thich: ";
        cin >> sdt;

        vector<string>::iterator it = find(dsYeuThich.begin(), dsYeuThich.end(), sdt);
        if (it == dsYeuThich.end()) {
            cout << "SDT nay khong co trong yeu thich!\n";
            return;
        }
        dsYeuThich.erase(it);
        cout << "Da xoa " << sdt << " khoi yeu thich!\n";
    }

    void HienThiYeuThich() {
        cout << "\n===== DANH BA YEU THICH =====\n";
        if (dsYeuThich.empty()) {
            cout << "(trong)\n";
            return;
        }

        string vien = string(85, '-') + "\n";
        cout << vien << left
             << "| " << setw(4) << "STT" << " | " << setw(24) << "Ten" << " | " << setw(13) << "SDT"
             << " | " << setw(15) << "Quan he" << " | " << setw(11) << "Ngay sinh" << " |\n" << vien;

        for (int i = 0; i < (int)dsYeuThich.size(); i++) {
            QuanlyDanhba* p = TimTheoSDT(dsYeuThich[i]);
            cout << "| " << setw(4) << i + 1 << " | ";
            if (p == nullptr) // lien lac da bi xoa khoi danh ba
                cout << setw(24) << "(da bi xoa)" << " | " << setw(13) << dsYeuThich[i]
                     << " | " << setw(15) << "" << " | " << setw(11) << "" << " |\n";
            else
                cout << setw(24) << p->GetName() << " | " << setw(13) << p->GetPhone()
                     << " | " << setw(15) << p->GetRelationship()
                     << " | " << setw(11) << p->GetBirthday().DateToString() << " |\n";
        }
        cout << vien;
    }

    // file luu moi dong 1 SDT
    void LuuYeuThich(string tenFile) {
        ofstream file(tenFile);
        for (string sdt : dsYeuThich)
            file << sdt << "\n";
    }

    void DocYeuThich(string tenFile) {
        ifstream file(tenFile);
        string sdt;
        dsYeuThich.clear();
        while (getline(file, sdt)) {
            sdt = ChuanHoa(sdt);
            if (!sdt.empty()) dsYeuThich.push_back(sdt);
        }
    }
};
