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

    // Gọi hàm display() để in toàn bộ danh sách ra màn hình dạng bảng chuẩn chỉnh
    qlDanhBa.Display();
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

    //Menu Chức năng
                case 0:
                    break;

    int luachon;
    do
    {
        cout << endl;
        cout << string(50, '=') << endl;
        cout << "| " << setw(16) << " " << " MENU QUAN LY " << setw(16) << " " << " |" << endl;;
        cout << string(50, '=') << endl;
        cout << "[1]. Sap xep danh ba:" << endl;
        cout << "[2]. Them lien lac" << endl;
        cout << "[3]. Tim kiem lien lac" << endl;
        cout << "[4]. Sua lien lac" << endl;
        cout << "[5]. Xoa lien lac" << endl;
        cout << "[6]. Trich loc cac lien lac theo nhom quan he." << endl;
        cout << "[7]. Danh ba yeu thich" << endl;
        cout << "[8]. Lien lac khan cap" << endl;
        cout << "[9]. Danh sach lien lac sap den sinh nhat." << endl;
        cout << "[0]. Quit" << endl;
        cout << string(50, '=') << endl;
        cout << "Lua chon cua ban: ";
        cin >> luachon;

        switch (luachon)
        {
        case 1:
            int luachonsapxep;
            do
            {
                cout << endl;
                cout << string(50, '=') << endl;
                cout << "| " << setw(16) << " " << " MENU SAP XEP " << setw(16) << " " << " |" << endl;;
                cout << string(50, '=') << endl;
                cout << "[1]. A-Z:" << endl;
                cout << "[2]. Z-A" << endl;
                cout << "[0]. Tro ve Menu chinh" << endl;
                cout << string(50, '=') << endl;
                cout << "Lua chon cua ban: ";
                cin >> luachonsapxep;

                switch (luachonsapxep)
                {
                case 1:
                    cout << "Sap xep danh ba A-Z:" << endl;
                    qlDanhBa.Display();
                    break;
                case 2:
                    cout << "Sap xep danh ba Z-A:" << endl;
                    qlDanhBa.Display_DESC();
                    break;
                case 0:
                    break;
                default:
                    cout << "Lua chon khong hop le. Xin moi lua chon lai" << endl;
                }
            } while (luachonsapxep != 0);
            break;
        case 2:
            /*QuanlyDanhba *p = new QuanlyDanhba();
            cin >> *p;
            qlDanhBa.Them(p);
            qlDanhBa.Capnhatfilekhithem(tenFile);
            qlDanhBa.Display();
            delete p;*/
            break;
        case 3:
            break;
        case 4:
            qlDanhBa.Sua();
            qlDanhBa.Capnhatfilekhithem(tenFile);
            qlDanhBa.Display();
            break;
        case 5:
            qlDanhBa.Xoa();
            qlDanhBa.Capnhatfilekhithem(tenFile);
            qlDanhBa.Display();
            break;
        case 6:
            qlDanhBa.LocTheoTenNhom();
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            cout << "Danh sach lien lac sap den sinh nhat." << endl;
            qlDanhBa.DanhSachSapSinhNhat();
            break;
        case 0:
            cout << "Tam biet!" << endl;
            break;
        default:
            cout << "Lua chon khong hop le. Xin moi lua chon lai" << endl;
        }
    } while (luachon != 0);

    cout << "\nChuong trinh chay hoan tat. Bo nho tren Heap se tu dong duoc giai phong!\n";
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