#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include "date.h"
#include "quanlydanhba.h"

using namespace std;

class ChucNang : public QuanlyDanhba
{
private:
    // Hàm phụ nội bộ để tính nhanh index (0-25) dựa vào tên chính
    int TinhIndex(const string& ten) const {
        size_t last_space = ten.rfind(' ');
        string tenChinh = (last_space != string::npos) ? ten.substr(last_space + 1) : ten;

        unsigned char c1 = tenChinh[0];
        int index = 0;
        if (c1 >= 'a' && c1 <= 'z') {
            index = c1 - 'a';
        }
        else if (c1 >= 'A' && c1 <= 'Z') {
            index = tolower(c1) - 'a';
        }
        if (index < 0 || index > 25) index = 0;
        return index;
    }

public:
    ChucNang(string _name = "", string _sdt = "", string _quanhe = "", Date _ngaysinh = Date(), string _ghichu = "")
        : QuanlyDanhba(_name, _sdt, _quanhe, _ngaysinh, _ghichu) {
    }

    // 4. Hàm hiển thị theo lựa chọn a-z hoặc z-a (có bắt lỗi nhập sai)
    void Hienthisapxep() {
        string arrange = "";
        cout << "\nNhap cach hien thi (a-z hoac z-a): ";
        cin >> arrange;

        while (arrange != "a-z" && arrange != "z-a") {
            cout << "Lua chon khong hop le! Vui long nhap lai (a-z hoac z-a): ";
            cin >> arrange;
        }

        if (arrange == "z-a") {
            Display_DESC();
        }
        else {
            Display();
        }
    }

    // Hàm chuẩn hóa chuỗi dùng chung (xóa khoảng trắng thừa và ký tự ẩn)
    string ChuanHoa(string s) const {
        while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) s.pop_back();
        size_t start = s.find_first_not_of(" \t");
        if (start == string::npos) return "";
        size_t end = s.find_last_not_of(" \t");
        return s.substr(start, end - start + 1);
    }

    // Hàm kiểm tra riêng Tên
    bool KiemTraTrungTen(const string& tenMoi) const {
        string tMoi = ChuanHoa(tenMoi);
        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = const_cast<ChucNang*>(this)->getvector(idx);
            for (const auto& nguoi : nhom) {
                if (ChuanHoa(nguoi->GetName()) == tMoi) return true;
            }
        }
        return false;
    }

    // Hàm kiểm tra trùng full (Tên + SĐT), hỗ trợ loại trừ con trỏ hiện tại khi Sửa
    bool KiemTraTrungFull(const string& tenMoi, const string& sdtMoi, const QuanlyDanhba* excludePtr = nullptr) const {
        string tMoi = ChuanHoa(tenMoi);
        string sMoi = ChuanHoa(sdtMoi);
        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = const_cast<ChucNang*>(this)->getvector(idx);
            for (const auto& nguoi : nhom) {
                if (nguoi != excludePtr && ChuanHoa(nguoi->GetName()) == tMoi && ChuanHoa(nguoi->GetPhone()) == sMoi) return true;
            }
        }
        return false;
    }

    // 1. Hàm Thêm (Nhập liệu trực tiếp và kiểm tra trùng SĐT/Tên ngay lập tức)
    void Them() {
  

        while (true) {
            string name, phone, relationship, dateStr, note;

            // 1. Nhập Tên
            cout << "Nhap ho ten: ";
            getline(cin, name);

            while (name.empty() || name.length() < 2) {
                cout << "Nhap sai dinh dang ten (khong duoc de trong hoac co do dai chu < 2)!\n";
                cout << "Nhap lai ho ten: ";
                getline(cin, name);
            }

            // Cảnh báo nếu trùng tên
            if (KiemTraTrungTen(name)) {
                cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)!\n";
            }

            // 2. Nhập SĐT và CHẶN TRÙNG FULL NGAY LẬP TỨC
            cout << "Nhap SDT (dung 10 so va bat dau bang 0): ";
            getline(cin, phone);

            while (phone.empty() || phone.length() != 10 || phone[0] != '0' || KiemTraTrungFull(name, phone)) {
                if (KiemTraTrungFull(name, phone)) {
                    cout << "Loi: Ten va SDT nay da ton tai trong danh sach! Vui long nhap lai SDT khac: ";
                }
                else {
                    cout << "SDT khong hop le (phai du 10 so va bat dau bang 0)! Nhap lai: ";
                }
                getline(cin, phone);
            }

            // 3. Nhập Quan hệ
            cout << "Nhap quan he: ";
            getline(cin, relationship);
            while (relationship.empty() || relationship.length() < 2) {
                cout << "Nhap lai quan he (khong duoc de trong hoac < 2 ky tu): ";
                getline(cin, relationship);
            }

            // 4. Nhập Ngày sinh
            cout << "Nhap ngay sinh (dd/mm/yyyy): ";
            getline(cin, dateStr);
            Date d;
            d.FromString(dateStr);

            while (d.IsEmpty() || !d.FromString(dateStr) || !d.IsValidDate()) {
                cout << "Ngay sinh khong hop le hoac sai dinh dang! Nhap lai: ";
                getline(cin, dateStr);
                d.FromString(dateStr);
            }

            // 5. Nhập Ghi chú
            cout << "Nhap ghi chu: ";
            getline(cin, note);
            while (note.empty()) {
                cout << "Nhap lai ghi chu: ";
                getline(cin, note);
            }

            // Tạo đối tượng và đẩy vào vector a-z tương ứng
            QuanlyDanhba* p = new QuanlyDanhba(name, phone, relationship, d, note);
            int index = TinhIndex(p->GetName());
            getvector(index).push_back(p);
            cout << "Them contact vao danh ba thanh cong!\n";
            break;
        }
    }

    // 2. Hàm Xóa (Bắt nhập lại nếu sai yes/no, quét toàn bộ 26 vector, lặp lại nếu không tìm thấy)
    void Xoa() {
        string luachon;

        while (true) {
            cout << "Ban co muon xoa contact nao khong? (yes/no): ";
            cin >> luachon;

            if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs" ||
                luachon == "no" || luachon == "NO" || luachon == "No") {
                break;
            }
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }

        if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs")
        {
            bool daXoa = false;
            // Dọn bộ đệm MỘT LẦN duy nhất trước khi vào vòng lặp nhập tên/SĐT
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (!daXoa)
            {
                string tenCanXoa, sdtCanXoa;
                cout << "Nhap ten can xoa: ";
                getline(cin, tenCanXoa);

                cout << "Nhap sdt can xoa: ";
                getline(cin, sdtCanXoa);

                for (int idx = 0; idx < 26; idx++) {
                    vector<QuanlyDanhba*>& nhom = getvector(idx);
                    for (auto it = nhom.begin(); it != nhom.end(); ) {
                        if (ChuanHoa((*it)->GetName()) == ChuanHoa(tenCanXoa) || ChuanHoa((*it)->GetPhone()) == ChuanHoa(sdtCanXoa)) {
                            delete* it;
                            it = nhom.erase(it);
                            daXoa = true;
                        }
                        else {
                            ++it;
                        }
                    }
                }

                if (daXoa) {
                    cout << "Xoa contact thanh cong!\n";
                }
                else {
                    cout << "Khong tim thay contact nao khop thong tin! Vui long nhap lai.\n";
                }
            }
        }
        else {
            cout << "Bo qua thao tac xoa.\n";
        }
    }

    // 3. Hàm Sửa (Được làm chuẩn hóa, bắt lỗi định dạng và tự động chuyển đổi vector nếu đổi tên)
    void Sua() {
        string luachon;

        while (true) {
            cout << "Ban co muon sua contact nao khong? (yes/no): ";
            cin >> luachon;

            if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs" ||
                luachon == "no" || luachon == "NO" || luachon == "No") {
                break;
            }
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }

        if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs") {
            bool daSua = false;
            // Dọn bộ đệm MỘT LẦN duy nhất trước khi vào vòng lặp nhập tên/SĐT cần sửa
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (!daSua) {
                string tenCanSua, sdtCanSua;
                cout << "Nhap ten can sua: ";
                getline(cin, tenCanSua);

                cout << "Nhap sdt can sua: ";
                getline(cin, sdtCanSua);

                QuanlyDanhba* target = nullptr;
                int oldIndex = -1;

                // Tìm kiếm contact trong tất cả các vector
                for (int idx = 0; idx < 26; idx++) {
                    vector<QuanlyDanhba*>& nhom = getvector(idx);
                    for (auto it = nhom.begin(); it != nhom.end(); ++it) {
                        if (ChuanHoa((*it)->GetName()) == ChuanHoa(tenCanSua) || ChuanHoa((*it)->GetPhone()) == ChuanHoa(sdtCanSua)) {
                            target = *it;
                            oldIndex = idx;
                            break;
                        }
                    }
                    if (target) break;
                }

                if (target) {
                    cout << "\nDa tim thay! Nhap thong tin moi:\n";

                    string newName, newPhone, newRel, newNote, newDateStr;

                    // 1. Nhập và kiểm tra Tên mới
                    cout << "Nhap ho ten moi: ";
                    getline(cin, newName);

                    while (newName.empty() || newName.length() < 2) {
                        cout << "Nhap sai dinh dang ten (khong duoc de trong hoac co do dai chu < 2)!\n";
                        cout << "Nhap lai ho ten moi: ";
                        getline(cin, newName);
                    }

                    if (KiemTraTrungTen(newName)) {
                        cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)!\n";
                    }

                    // 2. Nhập và kiểm tra SĐT mới (Chặn trùng full, loại trừ chính target đang sửa)
                    cout << "Nhap SDT moi (dung 10 so va bat dau bang 0): ";
                    getline(cin, newPhone);

                    while (newPhone.empty() || newPhone.length() != 10 || newPhone[0] != '0' || KiemTraTrungFull(newName, newPhone, target)) {
                        if (KiemTraTrungFull(newName, newPhone, target)) {
                            cout << "Ten va SDT bi trung trong danh sach! Nhap lai SDT khac: ";
                        }
                        else {
                            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0)! Nhap lai: ";
                        }
                        getline(cin, newPhone);
                    }

                    // 3. Nhập Quan hệ mới
                    cout << "Nhap quan he moi: ";
                    getline(cin, newRel);
                    while (newRel.empty() || newRel.length() < 2) {
                        cout << "Nhap lai quan he moi: ";
                        getline(cin, newRel);
                    }

                    // 4. Nhập Ngày sinh mới
                    cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
                    getline(cin, newDateStr);
                    Date d;
                    d.FromString(newDateStr);

                    while (d.IsEmpty() || !d.FromString(newDateStr) || !d.IsValidDate()) {
                        cout << "Ngay sinh khong hop le hoac sai dinh dang! Nhap lai: ";
                        getline(cin, newDateStr);
                        d.FromString(newDateStr);
                    }

                    // 5. Nhập Ghi chú mới
                    cout << "Nhap ghi chu moi: ";
                    getline(cin, newNote);
                    while (newNote.empty()) {
                        cout << "Nhap lai ghi chu moi: ";
                        getline(cin, newNote);
                    }

                    // Cập nhật thông tin vào đối tượng
                    target->SetName(newName);
                    target->SetPhone(newPhone);
                    target->SetRelationship(newRel);
                    target->SetBirthday(d);
                    target->SetNote(newNote);

                    // Nếu đổi tên dẫn đến thay đổi nhóm (a-z), tiến hành di chuyển con trỏ sang vector mới
                    int newIndex = TinhIndex(newName);
                    if (newIndex != oldIndex) {
                        vector<QuanlyDanhba*>& oldNhom = getvector(oldIndex);
                        oldNhom.erase(remove(oldNhom.begin(), oldNhom.end(), target), oldNhom.end());
                        getvector(newIndex).push_back(target);
                    }

                    daSua = true;
                    cout << "Sua thong tin contact thanh cong!\n";
                }
                else {
                    cout << "Khong tim thay contact nao khop thong tin! Vui long nhap lai.\n";
                }
            }
        }
        else {
            cout << "Bo qua thao tac sua.\n";
        }
    }

    // Hiển thị danh sách liên hệ lọc theo tên nhóm quan hệ
    void LocTheoTenNhom()
    {
        string findRelation;
        cout << "Nhap ten nhom quan he can loc: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, findRelation);
        cout << endl;

        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = getvector(idx);
            for (const auto& nguoi : nhom) {

                string relationship = nguoi->GetRelationship();
                transform(relationship.begin(), relationship.end(), relationship.begin(), ::tolower);
                transform(findRelation.begin(), findRelation.end(), findRelation.begin(), ::tolower);

                if (relationship.find(findRelation) != string::npos)
                {
                    cout << "| " << left << setw(24) << nguoi->GetName()
                        << " | " << setw(13) << nguoi->GetPhone()
                        << " | " << setw(15) << nguoi->GetRelationship()
                        << " | " << setw(15) << nguoi->GetBirthday().DateToString()
                        << " | " << setw(34) << nguoi->GetNote() << " |\n";
                }
            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }

    // Hiển thị danh sách liên hệ sắp sinh nhật trong năm
    void DanhSachSapSinhNhat()
    {
        vector<QuanlyDanhba*> danhsach;
        for (int idx = 0; idx < 26; idx++) {
            vector<QuanlyDanhba*>& nhom = getvector(idx);
            for (const auto& nguoi : nhom) {
                if (nguoi->GetBirthday().DemSoNgayDenSinhNhatTrongNam() >= 0)
                {
                    danhsach.push_back(nguoi);
                }
            }
        }

        sort(danhsach.begin(), danhsach.end(), [](const QuanlyDanhba* ng1, const QuanlyDanhba* ng2) {
            return ng1->GetBirthday().DemSoNgayDenSinhNhatTrongNam() < ng2->GetBirthday().DemSoNgayDenSinhNhatTrongNam();
            });

        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (const auto& nguoi : danhsach) {
            cout << "| " << left << setw(24) << nguoi->GetName()
                << " | " << setw(13) << nguoi->GetPhone()
                << " | " << setw(15) << nguoi->GetRelationship()
                << " | " << setw(15) << nguoi->GetBirthday().DateToString()
                << " | " << setw(34) << nguoi->GetNote() << " |\n";
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }
};