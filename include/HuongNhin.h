#pragma once

#include <string>
using namespace std;

enum HuongNhin {
    TRAI = 0,
    PHAI = 1,
    TREN = 2,
    DUOI = 3
};

string TenHuong(HuongNhin huong);
HuongNhin HuongDoiDien(HuongNhin huong);
