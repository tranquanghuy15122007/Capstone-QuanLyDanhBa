#include <iostream>
#include <vector>
#include <string>

#include "date.h"
#include "quanlydanhba.h"
#include "ChucNang.h"

using namespace std;

int main()
{
   
    ChucNang qlDanhBa;

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
        cout << "| " << setw(16) << " " << " MENU QUAN LY " << setw(16) << " " << " |" << endl;;
        cout << string(50, '=') << endl;
        cout << "[1]. Xem danh ba:" << endl;
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            break;
        case 4:
            if(qlDanhBa.Sua())
                qlDanhBa.Capnhatfilekhithem(tenFile);
            break;
        case 5:
            if(qlDanhBa.Xoa())
                qlDanhBa.Capnhatfilekhithem(tenFile);
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

    return 0;
}