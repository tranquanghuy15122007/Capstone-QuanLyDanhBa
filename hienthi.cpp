#include <iostream>
#include <vector>
#include <string>
#include "date.h"
#include "quanlydanhba.h"
#include "HotroHienthiCSVFILE.h" // Nhớ đảm bảo file này đã kết nối đúng với lớp dẫn xuất đọc file

using namespace std;

int main() {
    // Thiết lập hiển thị tiếng Việt trên console (nếu cần)
    system("chcp 65001 > nul");
    // Khởi tạo đối tượng quản lý danh bạ chi tiết (kế thừa từ QuanlyDanhba)
    HotroHienthi qlDanhBa;

    string tenFile = "danhba.csv";
    cout << "Dang tien hanh doc file: " << tenFile << "...\n\n";

    // Gọi hàm đọc file (hàm này sẽ tự động phân loại các contact vào 26 vector a-z)
    qlDanhBa.docFileDanhBa(tenFile);

    // Gọi hàm display() để in toàn bộ danh sách ra màn hình dạng bảng chuẩn chỉnh
    qlDanhBa.Display();
    cout << "Sắp xếp từ Z đến A:" << endl;
    qlDanhBa.Display_DESC();
    cout << "\nChuong trinh chay hoan tat. Bo nho tren Heap se tu dong duoc giai phong!\n";

    qlDanhBa.Them();
    qlDanhBa.Capnhatfilekhithem(tenFile);
    qlDanhBa.Hienthisapxep();

    qlDanhBa.Xoa();
    qlDanhBa.Capnhatfilekhithem(tenFile);
    qlDanhBa.Hienthisapxep();

    qlDanhBa.Sua();
    qlDanhBa.Capnhatfilekhithem(tenFile);
    qlDanhBa.Hienthisapxep();

    qlDanhBa.LocTheoTenNhom();
    qlDanhBa.DanhSachSapSinhNhat();

    return 0;
}