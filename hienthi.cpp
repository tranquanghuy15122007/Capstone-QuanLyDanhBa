#include <iostream>
#include <vector>
#include <string>

#include "date.h"
#include "quanlydanhba.h"
#include "HotroHienthiCSVFILE.h"

using namespace std;

int main()
{
    system("chcp 65001 > nul");

    HotroHienthi qlDanhBa;

    string tenFile = "danhba.csv";

    cout << "Dang tien hanh doc file: "
        << tenFile << "...\n\n";

    qlDanhBa.docFileDanhBa(tenFile);

    int luachon;

    do
    {
        cout << endl;
        cout << string(50, '=') << endl;
        cout << "|"
            << setw(20) << " "
            << "MENU QUAN LY"
            << setw(18) << " "
            << "|" << endl;
        cout << string(50, '=') << endl;

        cout << "[1]. Hien thi danh ba" << endl;
        cout << "[2]. Them lien lac" << endl;
        cout << "[3]. Sua lien lac" << endl;
        cout << "[4]. Xoa lien lac" << endl;
        cout << "[5]. Loc theo nhom quan he" << endl;
        cout << "[6]. Danh sach sap sinh nhat" << endl;
        cout << "[0]. Thoat" << endl;

        cout << string(50, '=') << endl;
        cout << "Lua chon cua ban: ";

        cin >> luachon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

                cout << "Lua chon: ";
                cin >> sapxep;
                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n');

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
            {
                qlDanhBa.Capnhatfilekhithem(tenFile);
            }
            break;

        case 4:
            if (qlDanhBa.Xoa())
            {
                qlDanhBa.Capnhatfilekhithem(tenFile);
            }
            break;

        case 5:
            qlDanhBa.LocTheoTenNhom();
            break;

        case 6:
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