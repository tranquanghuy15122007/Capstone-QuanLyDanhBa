#pragma once
#include "HotroHienthiCSVFILE.h"
#include <fstream>

// Cau 8, 9, 10: Danh ba yeu thich - Note - So khan cap (phim tat)
// Ke thua tiep: QuanlyDanhba -> ChucNang -> HotroHienthi -> DanhBaYeuThich
class DanhBaYeuThich : public HotroHienthi
{
private:
    vector<string> dsYeuThich; // Cau 8: chi luu SDT cua lien lac yeu thich
    string phimTat[10];        // Cau 10: phimTat[1..9] = SDT khan cap, "" = phim trong

    // ===== Ham phu dung chung =====

    // Tim lien lac theo SDT trong ca 26 vector. Khong thay -> tra ve nullptr
    QuanlyDanhba* TimTheoSDT(const string& sdt) {
        for (int i = 0; i < 26; i++) {
            for (QuanlyDanhba* nguoi : getvector(i)) {
                if (nguoi->GetPhone() == sdt)
                    return nguoi;
            }
        }
        return nullptr;
    }

    // Vi tri cua sdt trong dsYeuThich. Khong co -> tra ve -1
    int ViTriYeuThich(const string& sdt) const {
        for (int i = 0; i < (int)dsYeuThich.size(); i++) {
            if (dsYeuThich[i] == sdt)
                return i;
        }
        return -1;
    }

    // Kiem tra chuoi chi gom chu so
    bool LaSo(const string& s) const {
        if (s.empty()) return false;
        for (char ch : s) {
            if (ch < '0' || ch > '9')
                return false;
        }
        return true;
    }

public:
    // ================= CAU 8: DANH BA YEU THICH =================

    // 8.1 Them SDT vao yeu thich (SDT phai co trong danh ba)
    void ThemYeuThich() {
        string sdt;
        cout << "Nhap SDT muon them vao yeu thich: ";
        cin >> sdt;

        QuanlyDanhba* nguoi = TimTheoSDT(sdt);
        if (nguoi == nullptr) {
            cout << "SDT khong co trong danh ba!\n";
            return;
        }
        if (ViTriYeuThich(sdt) != -1) {
            cout << "SDT nay da nam trong danh ba yeu thich roi!\n";
            return;
        }

        dsYeuThich.push_back(sdt);
        cout << "Da them " << nguoi->GetName() << " vao danh ba yeu thich!\n";
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

    void HienThiYeuThich() {
        cout << "\n===== DANH BA YEU THICH =====\n";
        if (dsYeuThich.empty()) {
            cout << "(trong)\n";
            return;
        }
        for (int i = 0; i < (int)dsYeuThich.size(); i++) {
            QuanlyDanhba* nguoi = TimTheoSDT(dsYeuThich[i]);
            cout << i + 1 << ". " << left << setw(15) << dsYeuThich[i];
            if (nguoi != nullptr)
                cout << nguoi->GetName();
            else
                cout << "(lien lac nay da bi xoa khoi danh ba)";
            cout << "\n";
        }
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
        while (getline(file, sdt)) {
            if (!sdt.empty())
                dsYeuThich.push_back(sdt);
        }
        file.close();
    }

    // ================= CAU 9: THEM / XOA NOTE =================

    void ThemNote() {
        string sdt;
        cout << "Nhap SDT can them note: ";
        cin >> sdt;

        QuanlyDanhba* nguoi = TimTheoSDT(sdt);
        if (nguoi == nullptr) {
            cout << "SDT khong co trong danh ba!\n";
            return;
        }

        if (nguoi->GetNote().empty())
            cout << "Note hien tai: (trong)\n";
        else
            cout << "Note hien tai: " << nguoi->GetNote() << "\n";

        string note;
        cout << "Nhap note moi: ";
        cin.ignore();          // bo ky tu '\n' con sot lai sau cin >> sdt
        getline(cin, note);    // getline de nhap duoc ca khoang trang

        // File CSV dung dau ',' de ngan cot -> note co dau ',' se lam hong file
        if (note.find(',') != string::npos) {
            cout << "Note khong duoc chua dau phay!\n";
            return;
        }

        nguoi->SetNote(note);
        cout << "Da cap nhat note cho " << nguoi->GetName() << "!\n";
    }

    void XoaNote() {
        string sdt;
        cout << "Nhap SDT can xoa note: ";
        cin >> sdt;

        QuanlyDanhba* nguoi = TimTheoSDT(sdt);
        if (nguoi == nullptr) {
            cout << "SDT khong co trong danh ba!\n";
            return;
        }
        if (nguoi->GetNote().empty()) {
            cout << "Lien lac nay chua co note!\n";
            return;
        }

        nguoi->SetNote("");
        cout << "Da xoa note cua " << nguoi->GetName() << "!\n";
    }

    // ============ CAU 10: SO KHAN CAP LUU VAO PHIM TAT ============
    // SDT khan cap KHONG can co trong danh ba (vd: 113, 114, 115)

    void ThemKhanCap() {
        int phim;
        cout << "Chon phim tat (1-9): ";
        cin >> phim;
        if (cin.fail() || phim < 1 || phim > 9) {
            cin.clear();             // xoa trang thai loi neu nguoi dung go chu
            cin.ignore(1000, '\n');  // bo phan nhap sai
            cout << "Phim tat khong hop le!\n";
            return;
        }

        string sdt;
        cout << "Nhap SDT khan cap: ";
        cin >> sdt;
        if (!LaSo(sdt)) {
            cout << "SDT chi duoc chua chu so!\n";
            return;
        }

        if (phimTat[phim] != "") {
            string chon;
            cout << "Phim " << phim << " dang luu so " << phimTat[phim] << ". Ghi de? (yes/no): ";
            cin >> chon;
            if (chon != "yes" && chon != "YES" && chon != "Yes") {
                cout << "Giu nguyen phim tat cu.\n";
                return;
            }
        }

        phimTat[phim] = sdt;
        cout << "Da luu so " << sdt << " vao phim tat " << phim << "!\n";
    }

    void HienThiKhanCap() {
        cout << "\n===== SO KHAN CAP (PHIM TAT) =====\n";
        for (int i = 1; i <= 9; i++) {
            cout << "Phim " << i << ": ";
            if (phimTat[i] == "") {
                cout << "(trong)\n";
                continue;
            }
            cout << phimTat[i];
            QuanlyDanhba* nguoi = TimTheoSDT(phimTat[i]);
            if (nguoi != nullptr)
                cout << " - " << nguoi->GetName(); // co trong danh ba thi hien them ten
            cout << "\n";
        }
    }

    // Bam phim tat -> "goi" so da luu
    void GoiNhanh() {
        int phim;
        cout << "Bam phim tat (1-9): ";
        cin >> phim;
        if (cin.fail() || phim < 1 || phim > 9) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Phim tat khong hop le!\n";
            return;
        }
        if (phimTat[phim] == "") {
            cout << "Phim " << phim << " chua duoc gan so nao!\n";
            return;
        }
        cout << "Dang goi " << phimTat[phim] << "...\n";
    }

    // Luu / doc file khan cap: moi dong "phim,sdt"
    void LuuKhanCap(string tenFile) {
        ofstream file(tenFile);
        if (!file.is_open()) return;
        for (int i = 1; i <= 9; i++) {
            if (phimTat[i] != "")
                file << i << "," << phimTat[i] << "\n";
        }
        file.close();
    }

    void DocKhanCap(string tenFile) {
        ifstream file(tenFile);
        if (!file.is_open()) return;
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string phimStr, sdt;
            getline(ss, phimStr, ',');
            getline(ss, sdt, ',');
            if (!LaSo(phimStr)) continue;
            int phim = stoi(phimStr);
            if (phim >= 1 && phim <= 9)
                phimTat[phim] = sdt;
        }
        file.close();
    }
};
