#pragma once
#include "NoteDB.h"

// Cau 8: Danh ba yeu thich (menu nam o lop con MenuDisplay.h)
// Ke thua tiep: QuanlyDanhba -> ChucNang -> HotroHienthi -> NoteDB -> DanhBaYeuThich -> MenuDisplay
class DanhBaYeuThich : public NoteDB
{
private:
    vector<string> dsYeuThich; // Cau 8: chi luu SDT cua lien lac yeu thich

    // Vi tri cua sdt trong dsYeuThich. Khong co -> tra ve -1
    int ViTriYeuThich(const string& sdt) const {
        for (int i = 0; i < (int)dsYeuThich.size(); i++)
            if (dsYeuThich[i] == sdt)
                return i;
        return -1;
    }

public:
    // ================= CAU 8: DANH BA YEU THICH =================

    // 8.1 Them SDT vao yeu thich (SDT phai co trong danh ba)
    void ThemYeuThich() {
        QuanlyDanhba* nguoi = NhapVaTimSDT("Nhap SDT muon them vao yeu thich: ");
        if (nguoi == nullptr) return;

        if (ViTriYeuThich(nguoi->GetPhone()) != -1) {
            cout << "SDT nay da nam trong danh ba yeu thich roi!\n";
            return;
        }
        dsYeuThich.push_back(nguoi->GetPhone());
        cout << "Da them " << nguoi->GetName() << " vao danh ba yeu thich!\n";

        // Them xong -> hoi co muon xem bang yeu thich khong
        string chon;
        cout << "Ban co muon xem bang danh ba yeu thich? (yes/no): ";
        cin >> chon;
        if (chon == "yes" || chon == "YES" || chon == "Yes" || chon == "y" || chon == "Y")
            HienThiYeuThich();
    }

    // 8.2 Xoa SDT khoi yeu thich (SDT phai co trong danh sach yeu thich)
    void XoaYeuThich() {
        if (dsYeuThich.empty()) {
            cout << "Danh ba yeu thich dang trong!\n";
            return;
        }
        HienThiYeuThich();

        string sdt;
        cout << "Nhap SDT muon xoa khoi yeu thich: ";
        cin >> sdt;

        int vt = ViTriYeuThich(sdt);
        if (vt == -1) {
            cout << "SDT nay khong co trong danh ba yeu thich!\n";
            return;
        }
        dsYeuThich.erase(dsYeuThich.begin() + vt);
        cout << "Da xoa SDT " << sdt << " khoi danh ba yeu thich!\n";
    }

    // In bang danh ba yeu thich (cung kieu bang voi Display())
    void HienThiYeuThich() {
        cout << "\n===== DANH BA YEU THICH =====\n";
        if (dsYeuThich.empty()) {
            cout << "(trong)\n";
            return;
        }

        string vien = "+" + string(6, '-') + "+" + string(26, '-') + "+" + string(15, '-') + "+"
                    + string(17, '-') + "+" + string(13, '-') + "+" + string(32, '-') + "+\n";
        cout << vien;
        cout << "| " << left << setw(4) << "STT" << " | " << setw(24) << "Ten" << " | " << setw(13) << "SDT"
             << " | " << setw(15) << "Quan He" << " | " << setw(11) << "Ngay Sinh" << " | " << setw(30) << "Ghi Chu" << " |\n";
        cout << vien;

        for (int i = 0; i < (int)dsYeuThich.size(); i++) {
            QuanlyDanhba* nguoi = TimTheoSDT(dsYeuThich[i]);
            cout << "| " << setw(4) << i + 1 << " | ";
            if (nguoi == nullptr) // lien lac da bi xoa khoi danh ba (cau 6) nhung van con trong yeu thich
                cout << setw(24) << "(da bi xoa khoi danh ba)" << " | " << setw(13) << dsYeuThich[i]
                     << " | " << setw(15) << "" << " | " << setw(11) << "" << " | " << setw(30) << "" << " |\n";
            else
                cout << setw(24) << nguoi->GetName() << " | " << setw(13) << nguoi->GetPhone()
                     << " | " << setw(15) << nguoi->GetRelationship() << " | " << setw(11) << nguoi->GetBirthday().DateToString()
                     << " | " << setw(30) << nguoi->GetNote() << " |\n";
        }
        cout << vien;
    }

    // Luu / doc file yeu thich: moi dong 1 SDT
    void LuuYeuThich(string tenFile) {
        ofstream file(tenFile);
        if (!file.is_open()) return;
        for (const string& sdt : dsYeuThich)
            file << sdt << "\n";
        file.close();
    }

    void DocYeuThich(string tenFile) {
        ifstream file(tenFile);
        if (!file.is_open()) return; // chua co file thi bo qua
        dsYeuThich.clear();
        string sdt;
        while (getline(file, sdt))
            if (!sdt.empty())
                dsYeuThich.push_back(sdt);
        file.close();
    }
};
