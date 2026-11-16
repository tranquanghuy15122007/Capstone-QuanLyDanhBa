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
    system("chcp 65001 > nul");

    // DanhBaYeuThich la lop con cuoi cung (QuanlyDanhba -> ChucNang -> HotroHienthi -> NoteDB -> DanhBaYeuThich)
    // -> 1 doi tuong dung duoc ca chuc nang danh ba, yeu thich va khan cap tren CUNG 1 danh ba
    DanhBaYeuThich qlDanhBa;

    string tenFile = "danhba.csv";
    string fileYeuThich = "yeuthich.txt";
    string fileKhanCap = "khancap.txt";

    cout << "Dang tien hanh doc file: " << tenFile << "...\n\n";

    qlDanhBa.docFileDanhBa(tenFile);
    qlDanhBa.DocYeuThich(fileYeuThich);
    qlDanhBa.DocKhanCap(fileKhanCap);

    qlDanhBa.Display();
    int luachon;

    do
    {
        InTieuDe("MENU QUAN LY");
        cout << "[1]. Hien thi danh ba" << endl;
        cout << "[2]. Them lien lac" << endl;
        cout << "[3]. Sua lien lac" << endl;
        cout << "[4]. Xoa lien lac" << endl;
        cout << "[5]. Loc theo nhom quan he" << endl;
        cout << "[6]. Danh sach sap sinh nhat" << endl;
        cout << "[7]. Danh ba yeu thich" << endl;
        cout << "[8]. So khan cap (phim tat)" << endl;
        cout << "[9]. Danh sach lien lac sap den sinh nhat." << endl;
        cout << "[0]. Thoat" << endl;
        cout << string(50, '=') << endl;

        luachon = NhapLuaChon();

        switch (luachon)
        {
        case 1:
        {
            int sapxep;
            do
            {
                cout << "\n[1]. A-Z" << endl;
                cout << "[2]. Z-A" << endl;
                cout << "[0]. Quay lai" << endl;
                sapxep = NhapLuaChon();

                switch (sapxep)
                {
                case 1:
                    qlDanhBa.Display();
                    break;
                case 2:
                    qlDanhBa.Display_DESC();
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le!\n";
                }
            } while (sapxep != 0);
            break;
        }

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
            qlDanhBa.DanhSachSapSinhNhat();
            break;

        case 7:
        {
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
        }

        case 8:
        {
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
        }
        
        case 9:
            cout << "Danh sach lien lac sap den sinh nhat." << endl;
            qlDanhBa.DanhSachSapSinhNhat();
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
