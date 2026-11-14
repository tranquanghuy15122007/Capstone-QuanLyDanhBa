#pragma once
#include "DanhBaYeuThich.h"

// Lop con CUOI CUNG: giao dien menu + xu ly lua chon.
// Ke thua tiep: QuanlyDanhba -> ChucNang -> HotroHienthi -> NoteDB -> DanhBaYeuThich -> MenuDisplay
// Vi la lop con nen goi thang duoc Display(), ThemYeuThich(), ThemNote()... cua cac lop cha
class MenuDisplay : public DanhBaYeuThich
{
public:
    // In tieu de menu
    void InTieuDe() {
        cout << "\n====================================\n"
             << "     QUẢN LÝ DANH BẠ ĐIỆN THOẠI\n"
             << "====================================\n"
             << "Hiển thị từ (A - Z)\n";
    }

    // In cac lua chon chuc nang
    void InLuaChon() {
        cout << "1. Hiển thị danh bạ (Z - A)\n"
             << "\n----- DANH BẠ YÊU THÍCH -----\n"
             << "2. Thêm yêu thích\n"
             << "3. Hiển thị danh bạ yêu thích\n"
             << "4. Xóa yêu thích\n"
             << "\n----- QUẢN LÝ GHI CHÚ -----\n"
             << "5. Thêm ghi chú (Note)\n"
             << "6. Xóa ghi chú (Note)\n"
             << "\n----- SỐ ĐIỆN THOẠI KHẨN CẤP -----\n"
             << "7. Thêm số khẩn cấp\n"
             << "8. Hiển thị số khẩn cấp\n"
             << "9. Gọi nhanh\n"
             << "\n0. Thoát chương trình\n"
             << "====================================\n";
    }

    // Nhap lua chon, tra ve so nguoi dung chon (-1 neu nhap sai)
    int NhapLuaChon() {
        int choice;
        cout << "Nhập lựa chọn của bạn: ";
        cin >> choice;

        // Go chu thay vi so -> cin bi loi, phai xoa loi, neu khong menu se lap vo tan
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            return -1; // roi vao default: "Lua chon khong hop le"
        }
        return choice;
    }

    void InThoat()      { cout << "\nĐã thoát chương trình!\n"; }
    void InLuaChonSai() { cout << "\nLựa chọn không hợp lệ!\nVui lòng chọn lại.\n"; }

    // ================= MENU CHUC NANG =================
    // Chon so nao thi goi ham do (cac ham cau 8, 9, 10 lay tu lop cha)
    void Menu(string tenFile) {
        int choice;

        do {
            InTieuDe();
            Display();               // in danh ba A-Z (ham cua lop cha)
            InLuaChon();
            choice = NhapLuaChon();  // -1 neu nguoi dung go sai

            switch (choice) {
            case 1: Display_DESC(); break;

            // ===== Cau 8: Danh ba yeu thich =====
            case 2: ThemYeuThich(); LuuYeuThich("yeuthich.txt"); break;
            case 3: HienThiYeuThich(); break;
            case 4: XoaYeuThich();  LuuYeuThich("yeuthich.txt"); break;

            // ===== Cau 9: Them/Xoa Note =====
            case 5: ThemNote(); Capnhatfilekhithem(tenFile); break;
            case 6: XoaNote();  Capnhatfilekhithem(tenFile); break;

            // ===== Cau 10: So khan cap =====
            case 7: ThemKhanCap(); LuuKhanCap("khancap.txt"); break;
            case 8: HienThiKhanCap(); break;
            case 9: GoiNhanh(); break;

            case 0:  InThoat(); break;
            default: InLuaChonSai(); break;
            }

            // Dung lai cho nguoi dung doc ket qua, neu khong menu + bang danh ba
            // in lai ngay lam troi mat thong bao (vd: "Da them ... vao yeu thich!")
            if (choice != 0) {
                cout << endl;      // endl = xuong dong + day het chu ra man hinh truoc khi pause
                system("pause");
            }
        } while (choice != 0);
    }
};
