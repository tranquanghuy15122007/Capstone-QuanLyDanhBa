#pragma once
#include <iostream>
#include <string>
#include "date.h"


// xoa ky tu xuong dong o cuoi va khoang trang o hai dau
string ChuanHoa(string s) {
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) {
        s.pop_back();
    }

    size_t dau = s.find_first_not_of(" \t");

    if (dau == string::npos) {
        return "";
    }

    size_t cuoi = s.find_last_not_of(" \t");

    return s.substr(dau, cuoi - dau + 1);
}

// doc 1 dong va chuan hoa
string DocDong(istream& is) {
    string s;
    getline(is, s);
    return ChuanHoa(s);
}

