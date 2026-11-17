#pragma once
#include "HotroHienthiCSVFILE.h"

// So khan cap: gan SDT vao phim tat 1-9
// Cac ham protected ben duoi duoc DanhBaYeuThich va GroupAndBlacklist ke thua dung lai
class NoteDB : public HotroHienthi
{
private:
    string phimTat[10]; // chi dung phimTat[1] den phimTat[9], chuoi rong la chua gan so

    // tra ve phim 1-9, nhap sai tra ve 0
    int NhapPhim(string loiNhac) {
        cout << loiNhac;
        string s = DocDong(cin);
        if (s.length() != 1 || s[0] < '1' || s[0] > '9') {
            cout << "Phim tat khong hop le!\n";
            return 0;
        }
        return s[0] - '0';
    }

protected:
    QuanlyDanhba* TimTheoSDT(string sdt) {
        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);
            for (int j = 0; j < (int)nhom.size(); j++) {
                if (nhom[j]->GetPhone() == sdt)
                    return nhom[j];
            }
        }
        return NULL;
    }

    // tra ve vi tri cua sdt trong ds, khong co thi tra ve -1
    int TimViTri(vector<string>& ds, string sdt) {
        for (int i = 0; i < (int)ds.size(); i++) {
            if (ds[i] == sdt)
                return i;
        }
        return -1;
    }

    string NhapSDT(string loiNhac) {
        cout << loiNhac;
        string sdt = DocDong(cin);
        while (!SDTHopLe(sdt)) {
            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0)! Nhap lai: ";
            sdt = DocDong(cin);
        }
        return sdt;
    }

    bool LaSo(string s) {
        if (s.empty())
            return false;
        for (int i = 0; i < (int)s.length(); i++) {
            if (s[i] < '0' || s[i] > '9')
                return false;
        }
        return true;
    }

    void InBangSDT(vector<string>& ds) {
        string vien = "+" + string(6, '-') + "+" + string(26, '-') + "+" + string(15, '-') + "+" + string(17, '-') + "+\n";
        cout << vien << left
            << "| " << setw(4) << "STT" << " | " << setw(24) << "Ten"
            << " | " << setw(13) << "SDT" << " | " << setw(15) << "Quan he" << " |\n" << vien;

        for (int i = 0; i < (int)ds.size(); i++) {
            QuanlyDanhba* p = TimTheoSDT(ds[i]);
            cout << "| " << setw(4) << i + 1 << " | ";
            if (p == NULL)
                cout << setw(24) << "(khong co trong danh ba)" << " | " << setw(13) << ds[i] << " | " << setw(15) << "" << " |\n";
            else
                cout << setw(24) << p->GetName() << " | " << setw(13) << ds[i] << " | " << setw(15) << p->GetRelationship() << " |\n";
        }
        cout << vien;
    }

    // file luu moi dong 1 SDT
    void GhiFile(string tenFile, vector<string>& ds) {
        ofstream file(tenFile);
        for (int i = 0; i < (int)ds.size(); i++)
            file << ds[i] << "\n";
    }

    void DocFile(string tenFile, vector<string>& ds) {
        ifstream file(tenFile);
        string sdt;
        ds.clear();
        while (getline(file, sdt)) {
            sdt = ChuanHoa(sdt);
            if (!sdt.empty() && TimViTri(ds, sdt) == -1)
                ds.push_back(sdt);
        }
    }

public:
    // so khan cap co the ngan nhu 113, 115 nen chi kiem tra toan chu so
    void ThemKhanCap() {
        int phim = NhapPhim("Chon phim tat (1-9): ");
        if (phim == 0)
            return;

        cout << "Nhap SDT khan cap: ";
        string sdt = DocDong(cin);
        if (!LaSo(sdt)) {
            cout << "SDT chi duoc chua chu so!\n";
            return;
        }

        if (phimTat[phim] != "") {
            cout << "Phim " << phim << " dang luu so " << phimTat[phim] << ".\n";
            if (!XacNhan("Ban co muon ghi de khong?")) {
                cout << "Da huy.\n";
                return;
            }
        }
        phimTat[phim] = sdt;
        cout << "Da luu so " << sdt << " vao phim " << phim << "!\n";
    }

    void HienThiKhanCap() {
        cout << "\n===== SO KHAN CAP =====\n";
        int dem = 0;
        for (int i = 1; i <= 9; i++) {
            if (phimTat[i] == "")
                continue;
            cout << "Phim " << i << ": " << phimTat[i];
            QuanlyDanhba* p = TimTheoSDT(phimTat[i]);
            if (p != NULL)
                cout << " - " << p->GetName();
            cout << "\n";
            dem++;
        }
        if (dem == 0)
            cout << "(trong)\n";
    }

    void GoiNhanh() {
        int phim = NhapPhim("Bam phim tat (1-9): ");
        if (phim == 0)
            return;
        if (phimTat[phim] != "")
            cout << "Dang goi " << phimTat[phim] << "...\n";
        else
            cout << "Phim " << phim << " chua gan so nao!\n";
    }

    // file luu moi dong: phim,sdt (vd: 1,0905556677)
    void LuuKhanCap(string tenFile) {
        ofstream file(tenFile);
        for (int i = 1; i <= 9; i++) {
            if (phimTat[i] != "")
                file << i << "," << phimTat[i] << "\n";
        }
    }

    void DocKhanCap(string tenFile) {
        ifstream file(tenFile);
        string line;
        for (int i = 0; i < 10; i++)
            phimTat[i] = "";

        while (getline(file, line)) {
            line = ChuanHoa(line);
            // dong hop le: ky tu dau la phim 1-9, ky tu thu 2 la dau phay
            if (line.length() > 2 && line[0] >= '1' && line[0] <= '9' && line[1] == ',')
                phimTat[line[0] - '0'] = ChuanHoa(line.substr(2));
        }
    }
};
