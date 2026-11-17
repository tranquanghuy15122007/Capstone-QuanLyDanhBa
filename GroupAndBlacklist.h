#pragma once
#include "DanhBaYeuThich.h"

struct Nhom
{
    string ten;
    vector<string> dsSDT;
};

class GroupAndBlacklist : public DanhBaYeuThich
{
private:
    vector<Nhom> dsNhom;
    vector<string> dsChan;

    string ChuThuong(string s) {
        for (int i = 0; i < (int)s.length(); i++)
            s[i] = tolower(s[i]);
        return s;
    }

    // tim nhom khong phan biet hoa thuong, khong co thi tra ve -1
    int TimNhom(string ten) {
        ten = ChuThuong(ChuanHoa(ten));
        for (int i = 0; i < (int)dsNhom.size(); i++) {
            if (ChuThuong(dsNhom[i].ten) == ten)
                return i;
        }
        return -1;
    }

    // hien danh sach roi cho nguoi dung chon 1 nhom, go rong hoac sai ten thi tra ve -1
    int ChonNhom() {
        if (dsNhom.empty()) {
            cout << "Chua co nhom nao! Hay tao nhom truoc.\n";
            return -1;
        }
        HienThiDanhSachNhom();
        cout << "Nhap ten nhom (de trong de huy): ";
        string ten = DocDong(cin);
        if (ten.empty())
            return -1;

        int viTri = TimNhom(ten);
        if (viTri == -1)
            cout << "Khong co nhom \"" << ten << "\"!\n";
        return viTri;
    }

public:
    // ===== NHOM =====

    void TaoNhom() {
        cout << "Nhap ten nhom moi: ";
        string ten = DocDong(cin);
        while (ten.empty() || !ChiChuaChuVaKhoangTrang(ten)) {
            cout << "Ten nhom chi duoc chua chu (khong dau) va khoang trang! Nhap lai: ";
            ten = DocDong(cin);
        }
        if (TimNhom(ten) != -1) {
            cout << "Nhom \"" << ten << "\" da ton tai!\n";
            return;
        }
        Nhom n;
        n.ten = ten;
        dsNhom.push_back(n);
        cout << "Da tao nhom \"" << ten << "\"!\n";
    }

    void XoaNhom() {
        int viTri = ChonNhom();
        if (viTri == -1)
            return;

        if (!XacNhan("Ban co chac muon xoa nhom \"" + dsNhom[viTri].ten + "\" khong? (lien lac van con trong danh ba)")) {
            cout << "Da huy thao tac xoa nhom.\n";
            return;
        }
        cout << "Da xoa nhom \"" << dsNhom[viTri].ten << "\"!\n";
        dsNhom.erase(dsNhom.begin() + viTri);
    }

    void ThemVaoNhom() {
        int viTri = ChonNhom();
        if (viTri == -1)
            return;

        string sdt = NhapSDT("Nhap SDT muon them vao nhom: ");
        QuanlyDanhba* p = TimTheoSDT(sdt);
        if (p == NULL) {
            cout << "SDT khong co trong danh ba!\n";
            return;
        }
        if (TimViTri(dsNhom[viTri].dsSDT, sdt) != -1) {
            cout << p->GetName() << " da o trong nhom nay roi!\n";
            return;
        }
        if (LaChan(sdt))
            cout << "Luu y: " << p->GetName() << " dang nam trong danh sach chan.\n";

        dsNhom[viTri].dsSDT.push_back(sdt);
        cout << "Da them " << p->GetName() << " vao nhom \"" << dsNhom[viTri].ten << "\"!\n";
    }

    void XoaKhoiNhom() {
        int viTri = ChonNhom();
        if (viTri == -1)
            return;

        vector<string>& tv = dsNhom[viTri].dsSDT;
        if (tv.empty()) {
            cout << "Nhom nay chua co thanh vien!\n";
            return;
        }
        InBangSDT(tv);

        string sdt = NhapSDT("Nhap SDT muon xoa khoi nhom: ");
        int k = TimViTri(tv, sdt);
        if (k == -1) {
            cout << "SDT nay khong co trong nhom!\n";
            return;
        }
        tv.erase(tv.begin() + k);
        cout << "Da xoa " << sdt << " khoi nhom \"" << dsNhom[viTri].ten << "\"!\n";
    }

    void HienThiDanhSachNhom() {
        cout << "\n===== DANH SACH NHOM =====\n";
        if (dsNhom.empty()) {
            cout << "(trong)\n";
            return;
        }
        for (int i = 0; i < (int)dsNhom.size(); i++)
            cout << i + 1 << ". " << dsNhom[i].ten << " (" << dsNhom[i].dsSDT.size() << " thanh vien)\n";
    }

    void HienThiThanhVienNhom() {
        int viTri = ChonNhom();
        if (viTri == -1)
            return;

        cout << "\n===== NHOM: " << dsNhom[viTri].ten << " =====\n";
        if (dsNhom[viTri].dsSDT.empty())
            cout << "(chua co thanh vien)\n";
        else
            InBangSDT(dsNhom[viTri].dsSDT);
    }

    // file nhom.txt, moi dong: tenNhom,sdt1,sdt2,...
    void LuuNhom(string tenFile) {
        ofstream file(tenFile);
        for (int i = 0; i < (int)dsNhom.size(); i++) {
            file << dsNhom[i].ten;
            for (int j = 0; j < (int)dsNhom[i].dsSDT.size(); j++)
                file << "," << dsNhom[i].dsSDT[j];
            file << "\n";
        }
    }

    void DocNhom(string tenFile) {
        ifstream file(tenFile);
        string line, sdt;
        dsNhom.clear();
        while (getline(file, line)) {
            stringstream ss(line);
            Nhom n;
            getline(ss, n.ten, ',');
            n.ten = ChuanHoa(n.ten);
            if (n.ten.empty())
                continue;

            while (getline(ss, sdt, ',')) {
                sdt = ChuanHoa(sdt);
                if (!sdt.empty())
                    n.dsSDT.push_back(sdt);
            }
            dsNhom.push_back(n);
        }
    }

    // ===== DANH SACH CHAN =====

    bool LaChan(string sdt) {
        return TimViTri(dsChan, sdt) != -1;
    }

    // cho phep chan ca so khong co trong danh ba (vd so spam)
    void ThemVaoDanhSachChan() {
        string sdt = NhapSDT("Nhap SDT muon chan: ");
        if (LaChan(sdt)) {
            cout << "SDT nay da co trong danh sach chan!\n";
            return;
        }

        QuanlyDanhba* p = TimTheoSDT(sdt);
        string ten = (p != NULL) ? p->GetName() : sdt;
        if (!XacNhan("Ban co chac muon chan " + ten + " khong?")) {
            cout << "Da huy.\n";
            return;
        }
        dsChan.push_back(sdt);
        cout << "Da chan " << ten << "! Tu gio se khong nhan cuoc goi tu so nay.\n";
    }

    void XoaKhoiDanhSachChan() {
        if (dsChan.empty()) {
            cout << "Danh sach chan dang trong!\n";
            return;
        }
        HienThiDanhSachChan();

        string sdt = NhapSDT("Nhap SDT muon bo chan: ");
        int viTri = TimViTri(dsChan, sdt);
        if (viTri == -1) {
            cout << "SDT nay khong co trong danh sach chan!\n";
            return;
        }
        dsChan.erase(dsChan.begin() + viTri);
        cout << "Da bo chan " << sdt << "!\n";
    }

    void HienThiDanhSachChan() {
        cout << "\n===== DANH SACH CHAN (BLACKLIST) =====\n";
        if (dsChan.empty())
            cout << "(trong)\n";
        else
            InBangSDT(dsChan);
    }

    void GiaLapCuocGoiDen() {
        string sdt = NhapSDT("Nhap SDT dang goi den: ");
        QuanlyDanhba* p = TimTheoSDT(sdt);
        string ten = (p != NULL) ? p->GetName() + " (" + sdt + ")" : sdt;

        if (LaChan(sdt))
            cout << "Da chan cuoc goi tu " << ten << " - so nay nam trong danh sach chan!\n";
        else
            cout << "Reng reng... " << ten << " dang goi den.\n";
    }

    void LuuDanhSachChan(string tenFile) {
        GhiFile(tenFile, dsChan);
    }

    void DocDanhSachChan(string tenFile) {
        DocFile(tenFile, dsChan);
    }
};
