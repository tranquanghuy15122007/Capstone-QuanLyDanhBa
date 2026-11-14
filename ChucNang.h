#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "date.h"
#include "quanlydanhba.h"

using namespace std;

class ChucNang : public QuanlyDanhba
{
private:
    // Lưu nội dung các lần tìm kiếm theo tên và SĐT.
    vector<string> lichSuTimKiem;

    // Lưu thời điểm tương ứng với từng lần tìm kiếm.
    vector<time_t> thoiGianTimKiem;

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
    // 1. Hàm Thêm
    void Them(QuanlyDanhba* p) {
        int index = TinhIndex(p->GetName());
        getvector(index).push_back(p);
    }

    // 2. Hàm Xóa (Bắt nhập lại nếu sai yes/no, lặp lại nếu không tìm thấy)
    void Xoa() {
        string luachon;

        while (true) {
            cout << "Ban co muon xoa contact nao khong? (yes/no): ";
            cin >> luachon;

            if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs" || luachon == "no" || luachon == "NO" || luachon == "No") {
                break;
            }
            cout << "Lua chon khong hop le! Vui long nhap lai.\n";
        }

        if (luachon == "yes" || luachon == "YES" || luachon == "Yes" || luachon == "YEs") 
        {
            bool daXoa = false;

            while (!daXoa) 
            {
                string tenCanXoa, sdtCanXoa;
                cout << "Nhap ten can xoa: ";
                cin.ignore();
                getline(cin, tenCanXoa);

                cout << "Nhap sdt can xoa: ";
                cin >> sdtCanXoa;

                int index = TinhIndex(tenCanXoa);
                vector<QuanlyDanhba*>& nhom = getvector(index);

                for (auto it = nhom.begin(); it != nhom.end(); ) {
                    if ((*it)->GetName() == tenCanXoa || (*it)->GetPhone() == sdtCanXoa) {
                        delete* it;
                        it = nhom.erase(it);
                        daXoa = true;
                    }
                    else {
                        ++it;
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
    //Hiển thị danh sách liên hệ tìm kiếm theo tên
    void TimTheoTen()
    {
        string findName;
        cout << "Nhap ten lien he can tim: ";
        //cin.ignore(); nếu dùng khi tìm kiếm 4.3 sẽ bị mất ký tự đầu
        getline(cin, findName);
        cout << endl;

        // Tạo bản sao từ khóa để lưu lịch sử.
        string keyword = findName;

        // Chuyển từ khóa về chữ thường.
        transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);

        // Lưu lịch sử tìm kiếm theo tên.
        lichSuTimKiem.push_back("Ten: " + keyword);

        // Lưu thời điểm tìm kiếm.
        thoiGianTimKiem.push_back(time(0));

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

                string name = nguoi->GetName();
                transform(name.begin(), name.end(), name.begin(), ::tolower);

                transform(findName.begin(), findName.end(), findName.begin(), ::tolower);

                if (name.find(findName) != string::npos)
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


    //Hiển thị danh sách liên hệ tìm kiếm theo số điện thoại
    void TimTheoSDT()
    {
        string findPhone;
        cout << "Nhap so dien thoai can tim: ";
        //cin.ignore(); nếu dùng khi tìm kiếm 4.3 sẽ bị mất ký tự đầu
        getline(cin, findPhone);
        cout << endl;

        // Lưu từ khóa tìm kiếm theo SĐT.
        lichSuTimKiem.push_back("SDT: " + findPhone);

        // Lưu thời điểm tìm kiếm.
        thoiGianTimKiem.push_back(time(0));

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

                string phone = nguoi->GetPhone();
                transform(phone.begin(), phone.end(), phone.begin(), ::tolower);

                transform(findPhone.begin(), findPhone.end(), findPhone.begin(), ::tolower);

                if (phone.find(findPhone) != string::npos)
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


    // 4.3 Hiển thị lịch sử tìm kiếm theo thời gian gần nhất.
    void HienThiLichSuTimKiem()
    {
        if (lichSuTimKiem.empty())
        {
            cout << "Chua co lich su tim kiem!\n";
            return;
        }

        cout << "Lich su tim kiem"<<endl;

        cout << "+" << string(6, '-')
            << "+" << string(27, '-')
            << "+" << string(22, '-') << "+\n";

        cout << "| " << left << setw(4) << "STT"
            << " | " << setw(25) << "Tu khoa tim kiem"
            << " | " << setw(20) << "Thoi gian" << " |\n";

        cout << "+" << string(6, '-')
            << "+" << string(27, '-')
            << "+" << string(22, '-') << "+\n";

        int stt = 1;

        for (int i = (int)lichSuTimKiem.size() - 1; i >= 0; i--)
        {
            // Chuyển thời điểm tìm kiếm sang ngày giờ.
            tm ngayGio = {};
            localtime_s(&ngayGio, &thoiGianTimKiem[i]);

            cout << "| " << left << setw(4) << stt
                << " | " << setw(25) << lichSuTimKiem[i]
                << " | " << put_time(&ngayGio, "%d/%m/%Y %H:%M:%S")
                << " |\n";

            stt++;
        }

        cout << "+" << string(6, '-')
            << "+" << string(27, '-')
            << "+" << string(22, '-') << "+\n";
    }


    //Hiển thị danh sách liên hệ lọc theo tên nhóm quan hệ
    void LocTheoTenNhom()// hàm kh trả về giá trị
    {
        string findRelation;// tạo biến có tên find
        cout << "Nhap ten nhom quan he can loc: ";
        cin.ignore();//bỏ ký tự tiếp theo trong bộ đệm nhập
        getline(cin, findRelation);// lấy cả khoảng trắng "ban hoc"
        cout << endl;
        //in ra 26 cái - ngăn cách vởi 1 dấu +
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"// độ rộng tối thiểu
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int idx = 0; idx < 26; idx++) {//Để "nhom" sử dụng chính vector gốc, không tạo ra một bản sao của cả vector
            vector<QuanlyDanhba*>& nhom = getvector(idx);//tham chiếu "nhom" đến vector, lấy getvector tương ứng
            for (const auto& nguoi : nhom) {                 // ví dụ idx = 0 thì sẽ bàng A
                //Lần lượt lấy từng phần tử của vector nhom, đặt tên là nguoi, rồi xử lý người đó
                   //auto	Để C++ tự suy ra kiểu dữ liệu
                   //const	Không cho sửa phần tử con trỏ thông qua tham chiếu này
                   //:	Hiểu là “trong”
                string relationship = nguoi->GetRelationship();
                //tạo 1 biến gắn con trỏ người vào
                transform(relationship.begin(), relationship.end(), relationship.begin(), ::tolower);
                //begin bắt đầu duyệt chuỗi đến end, begin t2 ghi lại chiuỗi và tolower chuyển sang ký tự thường
                transform(findRelation.begin(), findRelation.end(), findRelation.begin(), ::tolower);
                //"ban hoc".find("ban") != string::npos
                //!= nghĩa là khác
                //C++ sẽ tìm chuỗi "ban" trong "ban hoc"
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
    

    
    //Hiển thị danh sách liên hệ sắp sinh nhật trong năm
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