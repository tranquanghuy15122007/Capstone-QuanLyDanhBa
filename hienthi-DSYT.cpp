#include <iostream>
#include "MenuDisplay.h" // lop con cuoi cung, da include san moi lop cha

using namespace std;

int main()
{
    system("chcp 65001 > nul"); // hien thi tieng Viet tren console

    MenuDisplay qlDanhBa; // lop con cuoi cung -> co du chuc nang cua moi lop cha
    string tenFile = "danhba.csv";

    // Doc du lieu tu file khi khoi dong
    cout << "Dang doc du lieu danh ba...\n";
    qlDanhBa.docFileDanhBa(tenFile);
    qlDanhBa.DocYeuThich("yeuthich.txt");
    qlDanhBa.DocKhanCap("khancap.txt");

    qlDanhBa.Menu(tenFile); // menu chuc nang (xem MenuDisplay.h)

    return 0;
}
