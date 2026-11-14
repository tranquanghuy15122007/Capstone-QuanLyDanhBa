#include <iostream>
#include <vector>
#include <string>
#include "date.h"
#include "quanlydanhba.h"
#include "HotroHienthiCSVFILE.h" // Nhớ đảm bảo file này đã kết nối đúng với lớp dẫn xuất đọc file
#include "DanhBaYeuThich.h"      // Câu 8, 9, 10 (lớp con của HotroHienthi)

using namespace std;

int main() {
    // Thiết lập hiển thị tiếng Việt trên console (nếu cần)
    system("chcp 65001 > nul");
    // Khởi tạo đối tượng quản lý danh bạ chi tiết (kế thừa từ QuanlyDanhba)
    // Dùng DanhBaYeuThich (lớp con cuối cùng) để có đủ chức năng của mọi lớp cha
    DanhBaYeuThich qlDanhBa;

    string tenFile = "danhba.csv";
    cout << "Dang tien hanh doc file: " << tenFile << "...\n\n";

    // Gọi hàm đọc file (hàm này sẽ tự động phân loại các contact vào 26 vector a-z)
    qlDanhBa.docFileDanhBa(tenFile);

    // Gọi hàm display() để in toàn bộ danh sách ra màn hình dạng bảng chuẩn chỉnh
    qlDanhBa.Display();
    cout << "Sắp xếp từ Z đến A:" << endl;
    qlDanhBa.Display_DESC();
    cout << "\nChuong trinh chay hoan tat. Bo nho tren Heap se tu dong duoc giai phong!\n";


    QuanlyDanhba* p = new QuanlyDanhba();
    cin >> *p;
    qlDanhBa.Them(p);
    qlDanhBa.Capnhatfilekhithem(tenFile);
    qlDanhBa.Hienthisapxep();

    qlDanhBa.Xoa();
    qlDanhBa.Capnhatfilekhithem(tenFile);
    qlDanhBa.Hienthisapxep();

    qlDanhBa.Sua();
    qlDanhBa.Capnhatfilekhithem(tenFile);
    qlDanhBa.Hienthisapxep();

    // ===== Câu 8: Danh bạ yêu thích =====
    qlDanhBa.DocYeuThich("yeuthich.txt");
    qlDanhBa.ThemYeuThich();
    qlDanhBa.HienThiYeuThich();
    qlDanhBa.XoaYeuThich();
    qlDanhBa.LuuYeuThich("yeuthich.txt");

    // ===== Câu 9: Thêm/Xóa Note =====
    qlDanhBa.ThemNote();
    qlDanhBa.XoaNote();
    qlDanhBa.Capnhatfilekhithem(tenFile); // note nằm trong danh bạ nên lưu lại file csv
    qlDanhBa.Display();

    // ===== Câu 10: Số khẩn cấp lưu vào phím tắt =====
    qlDanhBa.DocKhanCap("khancap.txt");
    qlDanhBa.ThemKhanCap();
    qlDanhBa.HienThiKhanCap();
    qlDanhBa.GoiNhanh();
    qlDanhBa.LuuKhanCap("khancap.txt");

    return 0;
}