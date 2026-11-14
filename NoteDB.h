#pragma once
#include "HotroHienthiCSVFILE.h"

// Cau 9, 10: Note - So khan cap (phim tat)
// Ke thua tiep: QuanlyDanhba -> ChucNang -> HotroHienthi -> NoteDB -> DanhBaYeuThich
class NoteDB : public HotroHienthi
{
private:
    string phimTat[10]; // Cau 10: phimTat[1..9] = SDT khan cap, "" = phim trong

    // Nhap phim tat 1-9. Nhap sai -> bao loi va tra ve 0
    int NhapPhim(string loiNhac) {
        int phim;
        cout << loiNhac;
        cin >> phim;
        if (cin.fail() || phim < 1 || phim > 9) {
            cin.clear();            // xoa trang thai loi neu nguoi dung go chu
            cin.ignore(1000, '\n'); // bo phan nhap sai
            cout << "Phim tat khong hop le!\n";
            return 0;
        }
        return phim;
    }

protected:
    // protected (khong phai private) de lop con DanhBaYeuThich (cau 8) van goi duoc

    // Tim lien lac theo SDT trong ca 26 vector. Khong thay -> tra ve nullptr
    QuanlyDanhba* TimTheoSDT(const string& sdt) {
        for (int i = 0; i < 26; i++)
            for (QuanlyDanhba* nguoi : getvector(i))
                if (nguoi->GetPhone() == sdt)
                    return nguoi;
        return nullptr;
    }

    // Nhap SDT roi tim trong danh ba. Khong thay -> bao loi va tra ve nullptr
    QuanlyDanhba* NhapVaTimSDT(string loiNhac) {
        string sdt;
        cout << loiNhac;
        cin >> sdt;
        QuanlyDanhba* nguoi = TimTheoSDT(sdt);
        if (nguoi == nullptr)
            cout << "SDT khong co trong danh ba!\n";
        return nguoi;
    }

    // Kiem tra chuoi chi gom chu so
    bool LaSo(const string& s) const {
        if (s.empty()) return false;
        for (char ch : s)
            if (ch < '0' || ch > '9')
                return false;
        return true;
    }

public:
    // ================= CAU 9: THEM / XOA NOTE =================

    void ThemNote() {
        QuanlyDanhba* nguoi = NhapVaTimSDT("Nhap SDT can them note: ");
        if (nguoi == nullptr) return;

        cout << "Note hien tai: " << (nguoi->GetNote().empty() ? "(trong)" : nguoi->GetNote()) << "\n";

        string note;
        cout << "Nhap note moi: ";
        cin.ignore();       // bo ky tu '\n' con sot lai sau cin >> sdt
        getline(cin, note); // getline de nhap duoc ca khoang trang

        // File CSV dung dau ',' de ngan cot -> note co dau ',' se lam hong file
        if (note.find(',') != string::npos) {
            cout << "Note khong duoc chua dau phay!\n";
            return;
        }

        nguoi->SetNote(note);
        cout << "Da cap nhat note cho " << nguoi->GetName() << "!\n";
    }

    void XoaNote() {
        QuanlyDanhba* nguoi = NhapVaTimSDT("Nhap SDT can xoa note: ");
        if (nguoi == nullptr) return;

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
        int phim = NhapPhim("Chon phim tat (1-9): ");
        if (phim == 0) return;

        string sdt;
        cout << "Nhap SDT khan cap: ";
        cin >> sdt;
        if (!LaSo(sdt)) {
            cout << "SDT chi duoc chua chu so!\n";
            return;
        }

        if (!phimTat[phim].empty()) {
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
            if (phimTat[i].empty()) {
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
        int phim = NhapPhim("Bam phim tat (1-9): ");
        if (phim == 0) return;

        if (phimTat[phim].empty())
            cout << "Phim " << phim << " chua duoc gan so nao!\n";
        else
            cout << "Dang goi " << phimTat[phim] << "...\n";
    }

    // Luu / doc file khan cap: moi dong "phim,sdt"
    void LuuKhanCap(string tenFile) {
        ofstream file(tenFile);
        if (!file.is_open()) return;
        for (int i = 1; i <= 9; i++)
            if (!phimTat[i].empty())
                file << i << "," << phimTat[i] << "\n";
        file.close();
    }

    void DocKhanCap(string tenFile) {
        ifstream file(tenFile);
        if (!file.is_open()) return; // chua co file thi bo qua
        string line, phimStr, sdt;
        while (getline(file, line)) {
            stringstream ss(line);
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
