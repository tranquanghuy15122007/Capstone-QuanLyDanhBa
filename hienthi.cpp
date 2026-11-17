#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

#include "date.h"
#include "quanlydanhba.h"
#include "HotroHienthiCSVFILE.h"
#include "NoteDB.h"
#include "DanhBaYeuThich.h"
#include "GroupAndBlacklist.h"

using namespace std;

// Nhap 1 so lua chon. Go chu thay vi so -> tra ve -1 (tranh menu lap vo tan)
int NhapLuaChon()
{
    int chon;
    cout << "Lua chon cua ban: ";
    cin >> chon;
    if (cin.fail())
    {
        cin.clear();
        chon = -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return chon;
}

void InTieuDe(string tieuDe)
{
    cout << endl;
    cout << string(50, '=') << endl;
    int le = (48 - (int)tieuDe.size()) / 2;
    cout << "|" << string(le, ' ') << tieuDe << string(48 - le - tieuDe.size(), ' ') << "|" << endl;
    cout << string(50, '=') << endl;
}

int main()
{
    // (QuanlyDanhba -> ChucNang -> HotroHienthi -> NoteDB -> DanhBaYeuThich -> GroupAndBlacklist)
    // -> 1 doi tuong dung duoc tat ca chuc nang tren CUNG 1 danh ba
    GroupAndBlacklist qlDanhBa;

    string tenFile = "danhba.csv";
    string fileYeuThich = "yeuthich.txt";
    string fileKhanCap = "khancap.txt";
    string fileNhom = "nhom.txt";
    string fileDanhSachChan = "danhsachchan.txt";

    cout << "Dang tien hanh doc file: " << tenFile << "...\n\n";

    qlDanhBa.docFileDanhBa(tenFile);
    qlDanhBa.DocYeuThich(fileYeuThich);
    qlDanhBa.DocKhanCap(fileKhanCap);
    qlDanhBa.DocNhom(fileNhom);
    qlDanhBa.DocDanhSachChan(fileDanhSachChan);

    qlDanhBa.Display();
    int luachon;

    do
    {
        InTieuDe("MENU QUAN LY");
        cout << "[1]. Xem danh ba" << endl;
        cout << "[2]. Them lien lac" << endl;
        cout << "[3]. Sua lien lac" << endl;
        cout << "[4]. Xoa lien lac" << endl;
        cout << "[5]. Loc theo nhom quan he" << endl;
        cout << "[6]. Tim kiem lien lac" << endl;
        cout << "[7]. Danh ba yeu thich" << endl;
        cout << "[8]. So khan cap (phim tat)" << endl;
        cout << "[9]. Danh sach lien lac sap den sinh nhat." << endl;
        cout << "[10]. Quan ly nhom (group)" << endl;
        cout << "[11]. Danh sach chan (blacklist)" << endl;
        cout << "[0]. Thoat" << endl;
        cout << string(50, '=') << endl;

        luachon = NhapLuaChon();

        switch (luachon)
        {
        case 1:
            qlDanhBa.Hienthisapxep();
            break;
        case 2:
            qlDanhBa.Them();
            qlDanhBa.Capnhatfilekhithem(tenFile);
            break;
        case 3:
            if (qlDanhBa.Sua())
                qlDanhBa.Capnhatfilekhithem(tenFile);
            break;
        case 4:
            if (qlDanhBa.Xoa())
                qlDanhBa.Capnhatfilekhithem(tenFile);
            break;
        case 5:
            qlDanhBa.LocTheoTenNhom();
            break;
        case 6:
            int chonTK;
            do
            {
                InTieuDe("MENU TIM KIEM");
                cout << "[1]. Tim kiem theo ten" << endl;
                cout << "[2]. Tim kiem theo SDT" << endl;
                cout << "[3]. Lich su tim kiem" << endl;
                cout << "[0]. Tro ve menu chinh" << endl;
                cout << string(50, '=') << endl;
                chonTK = NhapLuaChon();

                switch (chonTK)
                {
                case 1:
                    qlDanhBa.TimTheoTen();
                    break;
                case 2:
                    qlDanhBa.TimTheoSoSDT();
                    break;
                case 3:
                    qlDanhBa.HienThiLichSuTimKiem();
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chonTK != 0);
            break;
        case 7:
            int chonYT;
            do
            {
                InTieuDe("MENU DANH BA YEU THICH");
                cout << "[1]. Hien thi danh ba yeu thich" << endl;
                cout << "[2]. Them yeu thich" << endl;
                cout << "[3]. Xoa yeu thich" << endl;
                cout << "[0]. Tro ve menu chinh" << endl;
                cout << string(50, '=') << endl;
                chonYT = NhapLuaChon();

                switch (chonYT)
                {
                case 1:
                    qlDanhBa.HienThiYeuThich();
                    break;
                case 2:
                    qlDanhBa.ThemYeuThich();
                    qlDanhBa.LuuYeuThich(fileYeuThich);
                    break;
                case 3:
                    qlDanhBa.XoaYeuThich();
                    qlDanhBa.LuuYeuThich(fileYeuThich);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chonYT != 0);
            break;
        case 8:
            int chonKC;
            do
            {
                InTieuDe("MENU SO KHAN CAP");
                cout << "[1]. Hien thi so khan cap" << endl;
                cout << "[2]. Them so khan cap vao phim tat" << endl;
                cout << "[3]. Goi nhanh" << endl;
                cout << "[0]. Tro ve menu chinh" << endl;
                cout << string(50, '=') << endl;
                chonKC = NhapLuaChon();

                switch (chonKC)
                {
                case 1:
                    qlDanhBa.HienThiKhanCap();
                    break;
                case 2:
                    qlDanhBa.ThemKhanCap();
                    qlDanhBa.LuuKhanCap(fileKhanCap);
                    break;
                case 3:
                    qlDanhBa.GoiNhanh();
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chonKC != 0);
            break;        
        case 9:
            cout << "Danh sach lien lac sap den sinh nhat." << endl;
            qlDanhBa.DanhSachSapSinhNhat();
            break;
        case 10:
            int chonNhom;
            do
            {
                InTieuDe("MENU QUAN LY NHOM");
                cout << "[1]. Xem danh sach nhom" << endl;
                cout << "[2]. Xem thanh vien 1 nhom" << endl;
                cout << "[3]. Tao nhom moi" << endl;
                cout << "[4]. Them lien lac vao nhom" << endl;
                cout << "[5]. Xoa lien lac khoi nhom" << endl;
                cout << "[6]. Xoa nhom" << endl;
                cout << "[0]. Tro ve menu chinh" << endl;
                cout << string(50, '=') << endl;
                chonNhom = NhapLuaChon();

                switch (chonNhom)
                {
                case 1:
                    qlDanhBa.HienThiDanhSachNhom();
                    break;
                case 2:
                    qlDanhBa.HienThiThanhVienNhom();
                    break;
                case 3:
                    qlDanhBa.TaoNhom();
                    qlDanhBa.LuuNhom(fileNhom);
                    break;
                case 4:
                    qlDanhBa.ThemVaoNhom();
                    qlDanhBa.LuuNhom(fileNhom);
                    break;
                case 5:
                    qlDanhBa.XoaKhoiNhom();
                    qlDanhBa.LuuNhom(fileNhom);
                    break;
                case 6:
                    qlDanhBa.XoaNhom();
                    qlDanhBa.LuuNhom(fileNhom);
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chonNhom != 0);
            break;
        case 11:
            int chonChan;
            do
            {
                InTieuDe("MENU DANH SACH CHAN (BLACKLIST)");
                cout << "[1]. Xem danh sach chan" << endl;
                cout << "[2]. Chan 1 so dien thoai" << endl;
                cout << "[3]. Bo chan 1 so dien thoai" << endl;
                cout << "[4]. Gia lap cuoc goi den" << endl;
                cout << "[0]. Tro ve menu chinh" << endl;
                cout << string(50, '=') << endl;
                chonChan = NhapLuaChon();

                switch (chonChan)
                {
                case 1:
                    qlDanhBa.HienThiDanhSachChan();
                    break;
                case 2:
                    qlDanhBa.ThemVaoDanhSachChan();
                    qlDanhBa.LuuDanhSachChan(fileDanhSachChan);
                    break;
                case 3:
                    qlDanhBa.XoaKhoiDanhSachChan();
                    qlDanhBa.LuuDanhSachChan(fileDanhSachChan);
                    break;
                case 4:
                    qlDanhBa.GiaLapCuocGoiDen();
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                }
            } while (chonChan != 0);
            break;
        case 0:
            cout << "Tam biet!\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (luachon != 0);

    return 0;
}
