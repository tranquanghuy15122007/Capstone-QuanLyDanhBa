#include <iostream>
#include <vector>
#include <string>
#include "date.h"
#include "quanlydanhba.h"
#include "HotroHienthiCSVFILE.h"

using namespace std;

int main() {
    system("chcp 65001 > nul");
    HotroHienthi qlDanhBa;

    string tenFile = "danhba.csv";
    cout << "Dang tien hanh doc file: " << tenFile << "...\n\n";
    qlDanhBa.docFileDanhBa(tenFile);

    qlDanhBa.Display();
    cout << "Sắp xếp từ Z đến A:" << endl;
    qlDanhBa.Display_DESC();

    qlDanhBa.Them();
    qlDanhBa.Capnhatfilekhithem(tenFile);

    if(qlDanhBa.Xoa() == true)
    {
        qlDanhBa.Capnhatfilekhithem(tenFile);
    }

    // Sua cung tu hoi hien bang ben trong
    if (qlDanhBa.Sua() == true)
    {
        qlDanhBa.Capnhatfilekhithem(tenFile);
    }


    qlDanhBa.LocTheoTenNhom();
    qlDanhBa.DanhSachSapSinhNhat();

    cout << "\nChuong trinh chay hoan tat. Bo nho tren Heap se tu dong duoc giai phong!\n";
    return 0;
}