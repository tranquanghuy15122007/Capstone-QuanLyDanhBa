#pragma once
#include "DanhBaYeuThich.h"
#include <map>

class GroupAndBlacklist : public DanhBaYeuThich
{
private:
    map<string, vector<string>> dsNhom;

    vector<string> chuongGa;

    static string ChuThuong(string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

    // tim nhom khong phan biet hoa thuong
    map<string, vector<string>>::iterator TimNhom(const string& ten) {
        string t = ChuThuong(ChuanHoa(ten));
        for (auto it = dsNhom.begin(); it != dsNhom.end(); it++)
            if (ChuThuong(it->first) == t)
                return it;
        return dsNhom.end();
    }

    // go rong -> huy
    map<string, vector<string>>::iterator NhapTenNhomDaCo() {
        if (dsNhom.empty()) {
            cout << "Chua co nhom nao! Hay tao nhom truoc.\n";
            return dsNhom.end();
        }
        HienThiDanhSachNhom();
        cout << "Nhap ten nhom (de trong de huy): ";
        string ten = DocDong(cin);
        if (ten.empty()) return dsNhom.end();

        auto it = TimNhom(ten);
        if (it == dsNhom.end())
            cout << "Khong co nhom \"" << ten << "\"!\n";
        return it;
    }

    string NhapSDT(const string& loiNhac) {
        cout << loiNhac;
        string sdt = DocDong(cin);
        while (!SDTHopLe(sdt)) {
            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0)! Nhap lai: ";
            sdt = DocDong(cin);
        }
        return sdt;
    }

    void InVien() {
        cout << "+" << string(6, '-') << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+\n";
    }

    void InBangSDT(const vector<string>& ds) {
        InVien();
        cout << "| " << left << setw(4) << "STT" << " | " << setw(24) << "Ten"
             << " | " << setw(13) << "SDT" << " | " << setw(15) << "Quan he" << " |\n";
        InVien();
        for (int i = 0; i < (int)ds.size(); i++) {
            QuanlyDanhba* p = TimTheoSDT(ds[i]);
            cout << "| " << setw(4) << i + 1 << " | "
                 << setw(24) << (p ? p->GetName() : "(khong co trong danh ba)")
                 << " | " << setw(13) << ds[i]
                 << " | " << setw(15) << (p ? p->GetRelationship() : "") << " |\n";
        }
        InVien();
    }

public:
    void TaoNhom() {
        cout << "Nhap ten nhom moi: ";
        string ten = DocDong(cin);
        while (ten.empty() || !ChiChuaChuVaKhoangTrang(ten)) {
            cout << "Ten nhom chi duoc chua chu (khong dau) va khoang trang! Nhap lai: ";
            ten = DocDong(cin);
        }
        if (TimNhom(ten) != dsNhom.end()) {
            cout << "Nhom \"" << ten << "\" da ton tai!\n";
            return;
        }
        dsNhom[ten] = vector<string>();
        cout << "Da tao nhom \"" << ten << "\"!\n";
    }

    void XoaNhom() {
        auto it = NhapTenNhomDaCo();
        if (it == dsNhom.end()) return;

        if (!XacNhan("Ban co chac muon xoa nhom \"" + it->first + "\" khong? (lien lac van con trong danh ba)")) {
            cout << "Da huy thao tac xoa nhom.\n";
            return;
        }
        cout << "Da xoa nhom \"" << it->first << "\"!\n";
        dsNhom.erase(it);
    }

    void ThemVaoNhom() {
        auto it = NhapTenNhomDaCo();
        if (it == dsNhom.end()) return;

        string sdt = NhapSDT("Nhap SDT muon them vao nhom: ");
        QuanlyDanhba* p = TimTheoSDT(sdt);
        if (p == nullptr) {
            cout << "SDT khong co trong danh ba!\n";
            return;
        }
        vector<string>& tv = it->second;
        if (find(tv.begin(), tv.end(), sdt) != tv.end()) {
            cout << p->GetName() << " da o trong nhom nay roi!\n";
            return;
        }
        if (LaChan(sdt))
            cout << "Luu y: " << p->GetName() << " dang bi nhot trong chuong ga.\n";

        tv.push_back(sdt);
        cout << "Da them " << p->GetName() << " vao nhom \"" << it->first << "\"!\n";
    }

    void XoaKhoiNhom() {
        auto it = NhapTenNhomDaCo();
        if (it == dsNhom.end()) return;

        vector<string>& tv = it->second;
        if (tv.empty()) {
            cout << "Nhom nay chua co thanh vien!\n";
            return;
        }
        InBangSDT(tv);

        string sdt = NhapSDT("Nhap SDT muon xoa khoi nhom: ");
        auto viTri = find(tv.begin(), tv.end(), sdt);
        if (viTri == tv.end()) {
            cout << "SDT nay khong co trong nhom!\n";
            return;
        }
        tv.erase(viTri);
        cout << "Da xoa " << sdt << " khoi nhom \"" << it->first << "\"!\n";
    }

    void HienThiDanhSachNhom() {
        cout << "\n===== DANH SACH NHOM =====\n";
        if (dsNhom.empty()) {
            cout << "(trong)\n";
            return;
        }
        int stt = 1;
        for (auto it = dsNhom.begin(); it != dsNhom.end(); it++, stt++)
            cout << stt << ". " << it->first << " (" << it->second.size() << " thanh vien)\n";
    }

    void HienThiThanhVienNhom() {
        auto it = NhapTenNhomDaCo();
        if (it == dsNhom.end()) return;

        cout << "\n===== NHOM: " << it->first << " =====\n";
        if (it->second.empty()) {
            cout << "(chua co thanh vien)\n";
            return;
        }
        InBangSDT(it->second);
    }

    // file nhom.txt, moi dong: tenNhom,sdt1,sdt2,...
    void LuuNhom(string tenFile) {
        ofstream file(tenFile);
        for (auto it = dsNhom.begin(); it != dsNhom.end(); it++) {
            file << it->first;
            for (string sdt : it->second)
                file << "," << sdt;
            file << "\n";
        }
    }

    void DocNhom(string tenFile) {
        ifstream file(tenFile);
        string line, ten, sdt;
        dsNhom.clear();
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, ten, ',');
            ten = ChuanHoa(ten);
            if (ten.empty()) continue;

            vector<string>& tv = dsNhom[ten];
            while (getline(ss, sdt, ',')) {
                sdt = ChuanHoa(sdt);
                if (!sdt.empty()) tv.push_back(sdt);
            }
        }
    }

    bool LaChan(const string& sdt) {
        return find(chuongGa.begin(), chuongGa.end(), sdt) != chuongGa.end();
    }

    // cho phep chan ca so la khong co trong danh ba (vd so spam)
    void ChoRaChuongGa() {
        string sdt = NhapSDT("Nhap SDT muon cho ra chuong ga: ");
        if (LaChan(sdt)) {
            cout << "SDT nay da o trong chuong ga roi!\n";
            return;
        }

        QuanlyDanhba* p = TimTheoSDT(sdt);
        string ten = p ? p->GetName() : sdt;
        if (!XacNhan("Cho " + ten + " ra chuong ga?")) {
            cout << "Da huy.\n";
            return;
        }
        chuongGa.push_back(sdt);
        cout << "Da cho " << ten << " ra chuong ga! Tu gio se khong nhan cuoc goi tu so nay.\n";
    }

    void ThaKhoiChuongGa() {
        if (chuongGa.empty()) {
            cout << "Chuong ga dang trong!\n";
            return;
        }
        HienThiChuongGa();

        string sdt = NhapSDT("Nhap SDT muon tha ra: ");
        auto it = find(chuongGa.begin(), chuongGa.end(), sdt);
        if (it == chuongGa.end()) {
            cout << "SDT nay khong co trong chuong ga!\n";
            return;
        }
        chuongGa.erase(it);
        cout << "Da tha " << sdt << " khoi chuong ga!\n";
    }

    void HienThiChuongGa() {
        cout << "\n===== CHUONG GA (BLACKLIST) =====\n";
        if (chuongGa.empty()) {
            cout << "(trong)\n";
            return;
        }
        InBangSDT(chuongGa);
    }

    void GiaLapCuocGoiDen() {
        string sdt = NhapSDT("Nhap SDT dang goi den: ");
        QuanlyDanhba* p = TimTheoSDT(sdt);
        string ten = p ? p->GetName() + " (" + sdt + ")" : sdt;

        if (LaChan(sdt))
            cout << "Da chan cuoc goi tu " << ten << " - nguoi nay dang o chuong ga!\n";
        else
            cout << "Reng reng... " << ten << " dang goi den.\n";
    }

    // file chuongga.txt, moi dong 1 SDT
    void LuuChuongGa(string tenFile) {
        ofstream file(tenFile);
        for (string sdt : chuongGa)
            file << sdt << "\n";
    }

    void DocChuongGa(string tenFile) {
        ifstream file(tenFile);
        string sdt;
        chuongGa.clear();
        while (getline(file, sdt)) {
            sdt = ChuanHoa(sdt);
            if (!sdt.empty() && !LaChan(sdt)) chuongGa.push_back(sdt);
        }
    }
};
