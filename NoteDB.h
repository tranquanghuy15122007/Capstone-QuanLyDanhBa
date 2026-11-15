#pragma once
#include "HotroHienthiCSVFILE.h"
#include <map>

// Cau 10: so khan cap luu vao phim tat 1-9
class NoteDB : public HotroHienthi
{
private:
    map<int, string> phimTat; // key: phim (1-9), value: sdt

    int NhapPhim(string loiNhac) {
        int phim;
        cout << loiNhac;
        cin >> phim;
        if (cin.fail() || phim < 1 || phim > 9) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Phim tat khong hop le!\n";
            return 0;
        }
        return phim;
    }

protected:
    // de protected cho lop con DanhBaYeuThich dung chung
    QuanlyDanhba* TimTheoSDT(const string& sdt) {
        for (int i = 0; i < 26; i++)
            for (QuanlyDanhba* p : getvector(i))
                if (p->GetPhone() == sdt)
                    return p;
        return nullptr;
    }

    QuanlyDanhba* NhapVaTimSDT(string loiNhac) {
        string sdt;
        cout << loiNhac;
        cin >> sdt;
        QuanlyDanhba* p = TimTheoSDT(sdt);
        if (p == nullptr)
            cout << "SDT khong co trong danh ba!\n";
        return p;
    }

    bool LaSo(const string& s) const {
        if (s.empty()) return false;
        for (char c : s)
            if (!isdigit(c)) return false;
        return true;
    }

public:
    void ThemKhanCap() {
        int phim = NhapPhim("Chon phim tat (1-9): ");
        if (phim == 0) return;

        string sdt;
        cout << "Nhap SDT khan cap: ";
        cin >> sdt;
        if (!LaSo(sdt)) {
            cout << "SDT chi duoc chua chu so!\n";
            return;
        }

        if (phimTat.count(phim)) { // phim da co so
            string chon;
            cout << "Phim " << phim << " dang luu so " << phimTat[phim] << ". Ghi de? (y/n): ";
            cin >> chon;
            if (chon != "y" && chon != "Y") return;
        }
        phimTat[phim] = sdt;
        cout << "Da luu so " << sdt << " vao phim " << phim << "!\n";
    }

    void HienThiKhanCap() {
        cout << "\n===== SO KHAN CAP =====\n";
        if (phimTat.empty()) {
            cout << "(trong)\n";
            return;
        }
        map<int, string>::iterator it;
        for (it = phimTat.begin(); it != phimTat.end(); it++) {
            cout << "Phim " << it->first << ": " << it->second;
            QuanlyDanhba* p = TimTheoSDT(it->second);
            if (p != nullptr) cout << " - " << p->GetName();
            cout << "\n";
        }
    }

    void GoiNhanh() {
        int phim = NhapPhim("Bam phim tat (1-9): ");
        if (phim == 0) return;
        if (phimTat.count(phim))
            cout << "Dang goi " << phimTat[phim] << "...\n";
        else
            cout << "Phim " << phim << " chua gan so nao!\n";
    }

    // file luu moi dong: phim,sdt
    void LuuKhanCap(string tenFile) {
        ofstream file(tenFile);
        for (auto it = phimTat.begin(); it != phimTat.end(); it++)
            file << it->first << "," << it->second << "\n";
    }

    void DocKhanCap(string tenFile) {
        ifstream file(tenFile);
        string line, phim, sdt;
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, phim, ',');
            getline(ss, sdt);
            if (LaSo(phim) && stoi(phim) >= 1 && stoi(phim) <= 9)
                phimTat[stoi(phim)] = ChuanHoa(sdt);
        }
    }
};
