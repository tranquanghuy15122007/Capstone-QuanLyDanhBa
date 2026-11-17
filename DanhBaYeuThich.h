#pragma once
#include "NoteDB.h"

class DanhBaYeuThich : public NoteDB
{
private:
    vector<string> dsYeuThich;

public:
    void ThemYeuThich() {
        string sdt = NhapSDT("Nhap SDT muon them vao yeu thich: ");
        QuanlyDanhba* p = TimTheoSDT(sdt);
        if (p == NULL) {
            cout << "SDT khong co trong danh ba!\n";
            return;
        }
        if (TimViTri(dsYeuThich, sdt) != -1) {
            cout << "SDT nay da co trong yeu thich!\n";
            return;
        }
        dsYeuThich.push_back(sdt);
        cout << "Da them " << p->GetName() << " vao yeu thich!\n";
    }

    void XoaYeuThich() {
        if (dsYeuThich.empty()) {
            cout << "Danh ba yeu thich dang trong!\n";
            return;
        }
        HienThiYeuThich();

        string sdt = NhapSDT("Nhap SDT muon xoa khoi yeu thich: ");
        int viTri = TimViTri(dsYeuThich, sdt);
        if (viTri == -1) {
            cout << "SDT nay khong co trong yeu thich!\n";
            return;
        }
        dsYeuThich.erase(dsYeuThich.begin() + viTri);
        cout << "Da xoa " << sdt << " khoi yeu thich!\n";
    }

    void HienThiYeuThich() {
        cout << "\n===== DANH BA YEU THICH =====\n";
        if (dsYeuThich.empty())
            cout << "(trong)\n";
        else
            InBangSDT(dsYeuThich);
    }

    void LuuYeuThich(string tenFile) {
        GhiFile(tenFile, dsYeuThich);
    }

    void DocYeuThich(string tenFile) {
        DocFile(tenFile, dsYeuThich);
    }
};
