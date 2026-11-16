#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include "date.h"
#include "quanlydanhba.h"
#include "GetLastName.h"

using namespace std;

class ChucNang : public QuanlyDanhba
{
protected:
    // Luu noi dung cac lan tim kiem theo ten và SST.
    vector<string> lichSuTimKiem;

    // tinh xem ten bat dau bang chu nao thi vao vector so may
    int TinhIndex(string ten) {
        size_t viTri = ten.rfind(' ');
        string tenChinh = ten;
        if (viTri != string::npos) {
            tenChinh = ten.substr(viTri + 1);
        }
        if (tenChinh.empty()) {
            return 0;
        }

        char c = tenChinh[0];
        int index = 0;
        if (c >= 'a' && c <= 'z') {
            index = c - 'a';
        }
        else if (c >= 'A' && c <= 'Z') {
            index = c - 'A';
        }
        return index;
    }

public:
    ChucNang(string _name = "", string _sdt = "", string _quanhe = "", Date _ngaysinh = Date(), string _ghichu = "")
        : QuanlyDanhba(_name, _sdt, _quanhe, _ngaysinh, _ghichu) {
    }

    // hoi yes/no, tra ve true neu yes, false neu no
    bool XacNhan(const string& cauHoi) {
        cout << cauHoi << " (yes/no): ";
        string s = DocDong(cin);
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        while (s != "yes" && s != "no") {
            cout << "Lua chon khong hop le! Vui long nhap lai (yes/no): ";
            s = DocDong(cin);
            transform(s.begin(), s.end(), s.begin(), ::tolower);
        }
        return s == "yes";
    }

    // hoi cach hien thi a-z hoac z-a
    void Hienthisapxep() {
        string arrange;
        cout << "\nNhap cach hien thi (a-z hoac z-a): ";
        arrange = DocDong(cin);

        while (arrange != "a-z" && arrange != "a-Z" && arrange != "A-z" && arrange != "A-Z" &&
            arrange != "z-a" && arrange != "z-A" && arrange != "Z-a" && arrange != "Z-A") {
            cout << "Lua chon khong hop le! Vui long nhap lai (a-z hoac z-a): ";
            arrange = DocDong(cin);
        }

        if (arrange == "z-a" || arrange == "z-A" || arrange == "Z-a" || arrange == "Z-A")
        {
            Display_DESC();
        }
        else {
            Display();
        }
    }

    // kiem tra trung ten
    // boQua: bo qua nguoi dang sua, neu khong khi sua "nguyen van a" thanh "nguyen van a" van bi bao trung
    bool KiemTraTrungTen(string tenMoi, QuanlyDanhba* boQua = nullptr) {
        string t = ChuanHoa(tenMoi);
        transform(t.begin(), t.end(), t.begin(), ::tolower);

        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);

            for (size_t j = 0; j < nhom.size(); j++) {
                string tenCu = ChuanHoa(nhom[j]->GetName());
                transform(tenCu.begin(), tenCu.end(), tenCu.begin(), ::tolower);

                if (nhom[j] != boQua && tenCu == t)
                    return true;
            }
        }

        return false;
    }

    // kiem tra trung SDT (bo qua nguoi dang sua)
    bool KiemTraTrungSDT(string sdtMoi, QuanlyDanhba* boQua = nullptr) {
        string s = ChuanHoa(sdtMoi);
        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                if (nhom[j] != boQua && ChuanHoa(nhom[j]->GetPhone()) == s) {
                    return true;
                }
            }
        }
        return false;
    }

    // 1. Them contact
    void Them() {
        QuanlyDanhba* p = new QuanlyDanhba();
        cin >> *p;

        if (KiemTraTrungTen(p->GetName())) {
            cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)" << endl;
        }

        while (KiemTraTrungSDT(p->GetPhone()))
        {
            string phone;
            cout << "Loi: SDT nay da ton tai trong danh sach! Vui long nhap lai SDT khac: ";
            phone = DocDong(cin);
            p->SetPhone(phone);
        }

        if (!XacNhan("Ban co chac chan muon them lien lac nay khong?")) {
            delete p;
            cout << "Da huy thao tac them.\n";
            return;
        }

        int index = TinhIndex(p->GetName());
        getvector(index).push_back(p);
        cout << "Them contact vao danh ba thanh cong!\n";
        Hienthisapxep();
    }

    // 2. Xoa contact theo ten + sdt: tra ve true neu da xoa, false neu khong xoa
    bool Xoa() {
        string ten, sdt;

        cout << "Nhap ho ten can xoa: ";
        ten = DocDong(cin);
        while (!TenHopLe(ten)) {
            cout << "Ten khong hop le! Nhap lai: ";
            ten = DocDong(cin);
        }

        cout << "Nhap SDT can xoa (dung 10 so va bat dau bang 0): ";
        sdt = DocDong(cin);
        while (!SDTHopLe(sdt)) {
            cout << "SDT khong hop le (phai du 10 so va bat dau bang 0)! Nhap lai: ";
            sdt = DocDong(cin);
        }

        string tenTim = ten;
        transform(tenTim.begin(), tenTim.end(), tenTim.begin(), ::tolower);

        // dua vao chu cai dau cua ten chinh (tu cuoi cung) de biet nam o vector nao
        int index = TinhIndex(ten);
        vector<QuanlyDanhba*>& nhom = getvector(index);

        for (size_t j = 0; j < nhom.size(); j++) {
            string tenCu = ChuanHoa(nhom[j]->GetName());
            transform(tenCu.begin(), tenCu.end(), tenCu.begin(), ::tolower);

            // so sanh ten tu phai sang trai, chi den dau cach
            // vd nhap "huy" hoac "quang huy" deu khop "Tran Quang Huy"
            bool khopTen = false;
            if (tenCu.length() >= tenTim.length()) {
                size_t viTri = tenCu.length() - tenTim.length();
                if (tenCu.compare(viTri, tenTim.length(), tenTim) == 0 &&
                    (viTri == 0 || tenCu[viTri - 1] == ' ')) {
                    khopTen = true;
                }
            }

            if (khopTen && ChuanHoa(nhom[j]->GetPhone()) == sdt) {
                cout << "---------------------------\n";
                cout << "Tim thay: " << "\n";
                cout << "Ho ten : " << nhom[j]->GetName() << "\n";
                cout << "SDT    : " << nhom[j]->GetPhone() << "\n";
                cout << "---------------------------\n";

                if (XacNhan("Ban co chac chan muon xoa nguoi nay khong?")) {
                    delete nhom[j];
                    nhom.erase(nhom.begin() + j);
                    cout << "Xoa contact thanh cong!\n";
                    Hienthisapxep();
                    return true;
                }
                else {
                    cout << "Da huy thao tac xoa.\n";
                    return false;
                }
            }
        }

        cout << "Khong tim thay nguoi nao co ten va SDT nay trong danh sach!\n";
        return false;
    }

    // 3. Sua contact theo sdt: tra ve true neu da sua, false neu khong sua
    bool Sua() {
        string sdt;
        do {
            cout << "Nhap SDT can sua (dung 10 so va bat dau bang 0): ";
            sdt = DocDong(cin);

            if (!SDTHopLe(sdt)) {
                cout << "SDT khong hop le!\n";
            }
        } while (!SDTHopLe(sdt));

        // tim nguoi co sdt nay
        QuanlyDanhba* target = nullptr;
        int oldI = -1;
        int oldJ = -1;
        for (int i = 0; i < 26; i++) {
            for (size_t j = 0; j < getvector(i).size(); j++) {
                if (ChuanHoa(getvector(i)[j]->GetPhone()) == sdt) {
                    target = getvector(i)[j];
                    oldI = i;
                    oldJ = (int)j;
                    break;
                }
            }

            if (target != nullptr)
                break;
        }

        if (target == nullptr) {
            cout << "Khong tim thay nguoi nao co SDT nay trong danh sach!\n";
            return false;
        }

        cout << "---------------------------\n";
        cout << "Tim thay: " << "\n";
        cout << "Ho ten : " << target->GetName() << "\n";
        cout << "SDT    : " << target->GetPhone() << "\n";
        cout << "---------------------------\n";

        if (!XacNhan("Ban co chac chan muon sua nguoi nay khong?")) {
            cout << "Da huy thao tac sua.\n";
            return false;
        }

        // nhap thong tin moi
        string ten, sdtMoi, quanhe, ghichu, ngaysinhStr, chon;
        bool daSua = false;

        do {
            // menu chon muc can sua
            cout << "\n===== CHON MUC BAN MUON SUA =====\n";
            cout << "1. Sua ho ten     (hien tai: " << target->GetName() << ")\n";
            cout << "2. Sua SDT        (hien tai: " << target->GetPhone() << ")\n";
            cout << "3. Sua quan he    (hien tai: " << target->GetRelationship() << ")\n";
            cout << "4. Sua ngay sinh  (hien tai: " << target->GetBirthday().DateToString() << ")\n";
            cout << "5. Sua ghi chu    (hien tai: " << target->GetNote() << ")\n";
            cout << "6. Sua tat ca\n";
            cout << "0. Hoan tat\n";
            cout << "Nhap lua chon: ";
            chon = DocDong(cin);

            while (chon != "0" && chon != "1" && chon != "2" && chon != "3" &&
                chon != "4" && chon != "5" && chon != "6") {
                cout << "Lua chon khong hop le! Vui long nhap lai (0-6): ";
                chon = DocDong(cin);
            }

            if (chon == "1" || chon == "6") {
                cout << "Nhap ho ten: ";
                ten = DocDong(cin);

                while (!TenHopLe(ten)) {
                    cout << "Ten khong hop le! Nhap lai: ";
                    ten = DocDong(cin);
                }

                if (KiemTraTrungTen(ten, target)) {
                    cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)" << endl;
                }
                target->SetName(ten);
                daSua = true;
            }

            if (chon == "2" || chon == "6") {
                cout << "Nhap SDT moi (dung 10 so va bat dau bang 0): ";
                sdtMoi = DocDong(cin);

                while (!SDTHopLe(sdtMoi) || KiemTraTrungSDT(sdtMoi, target)) {
                    if (SDTHopLe(sdtMoi) && KiemTraTrungSDT(sdtMoi, target)) {
                        cout << "SDT da ton tai! Nhap lai: ";
                    }
                    else {
                        cout << "SDT khong hop le! Nhap lai: ";
                    }
                    sdtMoi = DocDong(cin);
                }
                target->SetPhone(sdtMoi);
                daSua = true;
            }

            if (chon == "3" || chon == "6") {
                cout << "Nhap quan he moi: ";
                quanhe = DocDong(cin);

                while (!QuanHeHopLe(quanhe)) {
                    cout << "Quan he khong hop le! Nhap lai: ";
                    quanhe = DocDong(cin);
                }
                target->SetRelationship(quanhe);
                daSua = true;
            }

            if (chon == "4" || chon == "6") {
                Date d;
                cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
                ngaysinhStr = DocDong(cin);
                while (ngaysinhStr.empty() || !d.FromString(ngaysinhStr) || !d.IsValidDate()) {
                    cout << "Ngay sinh khong hop le! Nhap lai: ";
                    ngaysinhStr = DocDong(cin);
                }
                target->SetBirthday(d);
                daSua = true;
            }

            if (chon == "5" || chon == "6") {
                cout << "Nhap ghi chu moi: ";
                ghichu = DocDong(cin);
                while (!GhiChuHopLe(ghichu)) {
                    cout << "Nhap lai ghi chu: ";
                    ghichu = DocDong(cin);
                }
                target->SetNote(ghichu);
                daSua = true;
            }

            if (chon == "6") {
                chon = "0"; // sua tat ca xong thi thoat
            }
        } while (chon != "0");

        if (!daSua) {
            cout << "Ban chua sua gi ca.\n";
            return false;
        }

        // neu doi chu cai dau thi chuyen sang vector khac
        int newI = TinhIndex(target->GetName());
        if (newI != oldI) {
            getvector(oldI).erase(getvector(oldI).begin() + oldJ);
            getvector(newI).push_back(target);
        }

        cout << "Sua thong tin contact thanh cong!\n";
        Hienthisapxep();
        return true;
    }

    //Hien thi danh sach lien he tim kiem theo ten
    void TimTheoTen()
    {
        string findName;
        cout << "Nhap ten lien he can tim: ";
        getline(cin, findName);
        cout << endl;

        string keyword = findName;
        transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
        lichSuTimKiem.push_back("Ten: " + keyword);
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

                string name = GetLastName(nguoi->GetName());
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


    //Hien thi danh sach lien he tim kiem theo so dien thoai
    void TimTheoSoSDT()
    {
        string findPhone;
        cout << "Nhap so dien thoai can tim: ";
        getline(cin, findPhone);
        cout << endl;
        lichSuTimKiem.push_back("SDT: " + findPhone);
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


    // Hien thi lich su tim kiem tu moi nhat den cu nhat.
    void HienThiLichSuTimKiem()
    {
        if (lichSuTimKiem.empty())
        {
            cout << "Chua co lich su tim kiem!\n";
            return;
        }

        cout << "+" << string(32, '-') << "+\n";
        cout << "| " << left << setw(30) << "Lich su tim kiem" << " |\n";
        cout << "+" << string(32, '-') << "+\n";

        for (int i = (int)lichSuTimKiem.size() - 1; i >= 0; i--)
        {
            cout << "| " << left << setw(30) << lichSuTimKiem[i] << " |\n";
        }

        cout << "+" << string(32, '-') << "+\n";
    }

    // Loc theo nhom quan he
    void LocTheoTenNhom() {
        string findRelation;

        if (!XacNhan("Ban co chac chan muon loc lien lac theo nhom quan he khong?")) {
            cout << "Da huy thao tac loc.\n";
            return;
        }

        cout << "Nhap ten nhom quan he can loc: ";
        findRelation = DocDong(cin);

        while (!QuanHeHopLe(findRelation)) {
            cout << "Ten nhom quan he khong hop le! Nhap lai: ";
            findRelation = DocDong(cin);
        }
        cout << endl;

        // doi het ve chu thuong de so sanh
        transform(findRelation.begin(), findRelation.end(), findRelation.begin(), ::tolower);

        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                string relationship = nhom[j]->GetRelationship();
                transform(relationship.begin(), relationship.end(), relationship.begin(), ::tolower);

                if (relationship.find(findRelation) != string::npos) {
                    Date dBirth = nhom[j]->GetBirthday();
                    string strBirth = dBirth.IsValidDateNoWarning() ? dBirth.DateToString() : "";
                    cout << "| " << left << setw(24) << nhom[j]->GetName()
                        << " | " << setw(13) << nhom[j]->GetPhone()
                        << " | " << setw(15) << nhom[j]->GetRelationship()
                        << " | " << setw(15) << strBirth
                        << " | " << setw(34) << nhom[j]->GetNote() << " |\n";
                }
            }
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }

    // Danh sach sap sinh nhat trong nam
    void DanhSachSapSinhNhat() {
        if (!XacNhan("Ban co chac chan muon xem danh sach lien lac sap sinh nhat khong?")) {
            cout << "Da huy thao tac xem.\n";
            return;
        }

        vector<QuanlyDanhba*> danhsach;

        for (int i = 0; i < 26; i++) {
            vector<QuanlyDanhba*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                if (nhom[j]->GetBirthday().IsValidDateNoWarning() && nhom[j]->GetBirthday().DemSoNgayDenSinhNhatTrongNam() >= 0) {
                    danhsach.push_back(nhom[j]);
                }
            }
        }

        // sap xep noi bot theo so ngay den sinh nhat tang dan
        for (size_t i = 0; i + 1 < danhsach.size(); i++) {
            for (size_t j = 0; j + 1 < danhsach.size() - i; j++) {
                int ngay1 = danhsach[j]->GetBirthday().DemSoNgayDenSinhNhatTrongNam();
                int ngay2 = danhsach[j + 1]->GetBirthday().DemSoNgayDenSinhNhatTrongNam();
                if (ngay1 > ngay2) {
                    QuanlyDanhba* tam = danhsach[j];
                    danhsach[j] = danhsach[j + 1];
                    danhsach[j + 1] = tam;
                }
            }
        }

        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
        cout << "| " << left << setw(24) << "Ten"
            << " | " << setw(13) << "SDT"
            << " | " << setw(15) << "Quan He"
            << " | " << setw(15) << "Ngay Sinh"
            << " | " << setw(34) << "Ghi Chu" << " |\n";
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

        for (size_t i = 0; i < danhsach.size(); i++) {
            cout << "| " << left << setw(24) << danhsach[i]->GetName()
                << " | " << setw(13) << danhsach[i]->GetPhone()
                << " | " << setw(15) << danhsach[i]->GetRelationship()
                << " | " << setw(15) << danhsach[i]->GetBirthday().DateToString()
                << " | " << setw(34) << danhsach[i]->GetNote() << " |\n";
        }
        cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
    }
};
