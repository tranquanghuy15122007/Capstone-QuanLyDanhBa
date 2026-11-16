#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cctype>
#include <fstream>
#include <sstream>
#include "date.h"
#include "quanlydanhba.h"
#include "HoTroInput.h"

using namespace std;

class ChucNang : public QuanlyDanhba
{
protected:

    bool SDTHopLe(const string& phone) {
        if (phone.length() != 10 || phone[0] != '0')
            return false;

        for (char c : phone) {
            if (!isdigit(static_cast<unsigned char>(c)))
                return false;
        }

        return true;
    }

    // chi cho phep chu cai (khong dau) va khoang trang
    bool ChiChuaChuVaKhoangTrang(const string& s) {
        for (char c : s) {
            if (!isalpha(static_cast<unsigned char>(c)) && c != ' ')
                return false;
        }

        return true;
    }

    bool TenHopLe(const string& ten) {
        return ten.length() >= 2 && ChiChuaChuVaKhoangTrang(ten);
    }

    bool QuanHeHopLe(const string& qh) {
        return qh.length() >= 2 && ChiChuaChuVaKhoangTrang(qh);
    }

    bool GhiChuHopLe(const string& note) {
        return !note.empty();
    }

public:
    ChucNang() {}

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
    bool KiemTraTrungTen(string tenMoi, Contact* boQua = nullptr) {
        string t = ChuanHoa(tenMoi);
        transform(t.begin(), t.end(), t.begin(), ::tolower);

        for (int i = 0; i < 26; i++) {
            vector<Contact*>& nhom = getvector(i);

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
    bool KiemTraTrungSDT(string sdtMoi, Contact* boQua = nullptr) {
        string s = ChuanHoa(sdtMoi);
        for (int i = 0; i < 26; i++) {
            vector<Contact*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                if (nhom[j] != boQua && ChuanHoa(nhom[j]->GetPhone()) == s) {
                    return true;
                }
            }
        }
        return false;
    }

    // doc file csv vao danh ba
    void docFileDanhBa(const string& danhba) {
        ifstream file(danhba);
        if (!file.is_open()) {
            cout << "Khong the mo file: " << danhba << " (Hay kiem tra lai vi tri file csv trong thu muc goc project!)\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            stringstream ss(line);
            string ten, sdt, quanhe, ngaysinhStr, ghichu;

            // thu tu: ten, sdt, quan he, ngay sinh, ghi chu
            getline(ss, ten, ',');
            getline(ss, sdt, ',');
            getline(ss, quanhe, ',');
            getline(ss, ngaysinhStr, ',');
            getline(ss, ghichu);

            // xoa khoang trang thua va ky tu \r
            ten = ChuanHoa(ten);
            sdt = ChuanHoa(sdt);
            quanhe = ChuanHoa(quanhe);
            ngaysinhStr = ChuanHoa(ngaysinhStr);
            ghichu = ChuanHoa(ghichu);

            Date ngaysinh;
            ngaysinh.FromString(ngaysinhStr);

            // tao contact roi bo vao vector dung chu cai (dung lai TinhIndex)
            Contact* newItem = new Contact(ten, sdt, quanhe, ngaysinh, ghichu);
            getvector(TinhIndex(ten)).push_back(newItem);
        }

        file.close();
        cout << "Load file vao class con thanh cong!\n\n";
    }

    // ghi lai toan bo danh ba ra file csv
    void Capnhatfilekhithem(const string& danhba) {
        ofstream file(danhba);
        if (!file.is_open()) {
            cout << "Khong the mo file de ghi: " << danhba << "\n";
            return;
        }

        for (int i = 0; i < 26; i++) {
            vector<Contact*>& nhom = getvector(i);
            for (int j = 0; j < static_cast<int>(nhom.size()); j++) {
                file << nhom[j]->GetName() << ","
                    << nhom[j]->GetPhone() << ","
                    << nhom[j]->GetRelationship() << ","
                    << nhom[j]->GetBirthday().DateToString() << ","
                    << nhom[j]->GetNote() << "\n";
            }
        }

        file.close();
        cout << "Da cap nhat va luu lai file CSV thanh cong!\n";
    }

    // 1. Them contact
    void Them() {
        string name, phone, relationship, dateStr, note;
        Date d;

        cout << "Nhap ho ten: ";
        name = DocDong(cin);

        while (!TenHopLe(name)) {
            cout << "Ten khong hop le! Nhap lai: ";
            name = DocDong(cin);
        }

        if (KiemTraTrungTen(name)) {
            cout << "Ten ban da trung ten trong danh sach (luu y co the trung ten nhung sdt khong duoc giong nhau)" << endl;
        }

        cout << "Nhap SDT (dung 10 so va bat dau bang 0): ";
        phone = DocDong(cin);

        while (!SDTHopLe(phone) || KiemTraTrungSDT(phone)) {
            if (SDTHopLe(phone) && KiemTraTrungSDT(phone)) {
                cout << "Loi: SDT nay da ton tai trong danh sach! Vui long nhap lai SDT khac: ";
            }
            else {
                cout << "SDT khong hop le (phai du 10 so va bat dau bang 0 va chi duoc chua chu so)! Nhap lai: ";
            }
            phone = DocDong(cin);
        }

        cout << "Nhap quan he: ";
        relationship = DocDong(cin);
        while (!QuanHeHopLe(relationship)) {
            cout << "Quan he khong hop le! Nhap lai: ";
            relationship = DocDong(cin);
        }

        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        dateStr = DocDong(cin);
        while (dateStr.empty() || !d.FromString(dateStr) || !d.IsValidDate()) {
            cout << "Ngay sinh khong hop le hoac sai dinh dang! Nhap lai: ";
            dateStr = DocDong(cin);
        }

        cout << "Nhap ghi chu: ";
        note = DocDong(cin);
        while (!GhiChuHopLe(note)) {
            cout << "Nhap lai ghi chu: ";
            note = DocDong(cin);
        }

        if (!XacNhan("Ban co chac chan muon them lien lac nay khong?")) {
            cout << "Da huy thao tac them.\n";
            return;
        }

        Contact* contact = new Contact(name, phone, relationship, d, note);
        int index = TinhIndex(contact->GetName());
        getvector(index).push_back(contact);
        cout << "Them contact vao danh ba thanh cong!\n";
        Hienthisapxep();
    }

    // 2. Xoa contact theo ten + sdt: tra ve true neu da xoa, false neu khong xoa
    bool Xoa() {
        int luachon;
        cout << endl;
        cout << string(50, '=') << endl;
        cout << "| " << setw(16) << " " << " XOA LIEN LAC " << setw(16) << " " << " |" << endl;;
        cout << string(50, '=') << endl;
        cout << "[1]. Xoa theo ten:" << endl;
        cout << "[2]. Xoa theo SDT:" << endl;
        cout << "[0]. Quit" << endl;
        cout << string(50, '=') << endl;
        cout << "Lua chon cua ban: ";
        cin >> luachon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string find_name;
        string find_phone;
        string find_name_tmp;

        vector<Contact*> danhsach; //danh sach phone tim duoc sau khi nhap ten/sdt can tim.

        switch (luachon)
        {
        case 1:
            cout << "Nhap ten can xoa: ";
            find_name = DocDong(cin);

            find_name_tmp = find_name;
            transform(find_name.begin(), find_name.end(), find_name.begin(), ::tolower);
            
            for (int i = 0; i < 26; i++) {
                vector<Contact*>& nhom = getvector(i);

                for (size_t j = 0; j < nhom.size(); j++) {
                    string name = ChuanHoa(nhom[j]->GetName());
                    transform(name.begin(), name.end(), name.begin(), ::tolower);

                    if (name.find(find_name) != string::npos)
                    {
                        danhsach.push_back(nhom[j]);
                    }
                }
            }

            if (static_cast<int>(danhsach.size()) > 0)
            {
                cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
                cout << "| " << left << setw(10) << "STT"
                    << " | " << setw(24) << "Ten"
                    << " | " << setw(13) << "SDT"
                    << " | " << setw(15) << "Quan He"
                    << " | " << setw(15) << "Ngay Sinh"
                    << " | " << setw(34) << "Ghi Chu" << " |\n";
                cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

                for (size_t i = 0; i < danhsach.size(); i++) {
                    cout << "| " << left << setw(10) << (i + 1)
                        << " | " << setw(24) << danhsach[i]->GetName()
                        << " | " << setw(13) << danhsach[i]->GetPhone()
                        << " | " << setw(15) << danhsach[i]->GetRelationship()
                        << " | " << setw(15) << danhsach[i]->GetBirthday().DateToString()
                        << " | " << setw(34) << danhsach[i]->GetNote() << " |\n";
                }
                cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

                int luachon_stt;
                cout << "Nhap stt cua ten can xoa. Nhap 0 de thoat: ";
                cin >> luachon_stt;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (luachon_stt < 0 || luachon_stt > static_cast<int>(danhsach.size()))
                {
                    cout << "STT Nhap khong ton tai. Hoac nhap 0 de thoat: ";
                    cin >> luachon_stt;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (luachon_stt == 0)
                {
                    break;
                }
                else
                {
                    Contact* it_xoa = danhsach[luachon_stt - 1];
                    for (int i = 0; i < 26; i++)
                    {
                        vector<Contact*>& nhom = getvector(i);

                        for (size_t j = 0; j < nhom.size(); j++)
                        {
                            if (ChuanHoa(nhom[j]->GetPhone()) == ChuanHoa(it_xoa->GetPhone()))
                            {
                                if (XacNhan("Ban co chac chan muon xoa nguoi nay khong?")) {
                                    delete nhom[j];
                                    nhom.erase(nhom.begin() + j);
                                    cout << "Xoa contact thanh cong!\n";
                                    return true;
                                }
                                else {
                                    cout << "Da huy thao tac xoa.\n";
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                cout << "Khong tim thay nguoi nao co ten " << find_name_tmp << " trong danh sach!\n";
            }            

            break;
        case 2:
            cout << "Nhap SDT can xoa: ";
            find_phone = DocDong(cin);

            for (int i = 0; i < 26; i++) {
                vector<Contact*>& nhom = getvector(i);

                for (size_t j = 0; j < nhom.size(); j++) {
                    string phone = ChuanHoa(nhom[j]->GetPhone());

                    if (phone.find(find_phone) != string::npos)
                    {
                        danhsach.push_back(nhom[j]);
                    }
                }
            }

            if (static_cast<int>(danhsach.size()) > 0)
            {
                cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";
                cout << "| " << left << setw(10) << "STT"
                    << " | " << setw(24) << "Ten"
                    << " | " << setw(13) << "SDT"
                    << " | " << setw(15) << "Quan He"
                    << " | " << setw(15) << "Ngay Sinh"
                    << " | " << setw(34) << "Ghi Chu" << " |\n";
                cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

                for (size_t i = 0; i < danhsach.size(); i++) {
                    cout << "| " << left << setw(10) << (i + 1)
                        << " | " << setw(24) << danhsach[i]->GetName()
                        << " | " << setw(13) << danhsach[i]->GetPhone()
                        << " | " << setw(15) << danhsach[i]->GetRelationship()
                        << " | " << setw(15) << danhsach[i]->GetBirthday().DateToString()
                        << " | " << setw(34) << danhsach[i]->GetNote() << " |\n";
                }
                cout << "+" << string(26, '-') << "+" << string(15, '-') << "+" << string(17, '-') << "+" << string(17, '-') << "+" << string(36, '-') << "+\n";

                int luachon_stt;
                cout << "Nhap stt cua sdt can xoa. Nhap 0 de thoat: ";
                cin >> luachon_stt;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                while (luachon_stt < 0 || luachon_stt > static_cast<int>(danhsach.size()))
                {
                    cout << "STT Nhap khong ton tai. Hoac nhap 0 de thoat: ";
                    cin >> luachon_stt;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (luachon_stt == 0)
                {
                    break;
                }
                else
                {
                    Contact* it_xoa = danhsach[luachon_stt - 1];
                    for (int i = 0; i < 26; i++)
                    {
                        vector<Contact*>& nhom = getvector(i);

                        for (size_t j = 0; j < nhom.size(); j++)
                        {
                            if (ChuanHoa(nhom[j]->GetPhone()) == ChuanHoa(it_xoa->GetPhone()))
                            {
                                if (XacNhan("Ban co chac chan muon xoa nguoi nay khong?")) {
                                    delete nhom[j];
                                    nhom.erase(nhom.begin() + j);
                                    cout << "Xoa contact thanh cong!\n";
                                    return true;
                                }
                                else {
                                    cout << "Da huy thao tac xoa.\n";
                                    return false;
                                }
                            }
                        }
                    }
                    delete it_xoa;
                }
            }
            else
            {
                cout << "Khong tim thay nguoi nao co sdt " << find_phone << " trong danh sach!\n";
            }

            break;
        case 0:
            break;
        default:
            break;
        };

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
        Contact* target = nullptr;
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
            vector<Contact*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                string relationship = nhom[j]->GetRelationship();
                transform(relationship.begin(), relationship.end(), relationship.begin(), ::tolower);

                if (relationship.find(findRelation) != string::npos) {
                    cout << "| " << left << setw(24) << nhom[j]->GetName()
                        << " | " << setw(13) << nhom[j]->GetPhone()
                        << " | " << setw(15) << nhom[j]->GetRelationship()
                        << " | " << setw(15) << nhom[j]->GetBirthday().DateToString()
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

        vector<Contact*> danhsach;

        for (int i = 0; i < 26; i++) {
            vector<Contact*>& nhom = getvector(i);
            for (size_t j = 0; j < nhom.size(); j++) {
                if (nhom[j]->GetBirthday().DemSoNgayDenSinhNhatTrongNam() >= 0) {
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
                    Contact* tam = danhsach[j];
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
