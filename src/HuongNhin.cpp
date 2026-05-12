#include "HuongNhin.h"
using namespace std;

string TenHuong(HuongNhin huong) {
    if (huong == TRAI) return "TRAI";
    if (huong == PHAI) return "PHAI";
    if (huong == TREN) return "TREN";
    return "DUOI";
}

HuongNhin HuongDoiDien(HuongNhin huong) {
    if (huong == TRAI) return PHAI;
    if (huong == PHAI) return TRAI;
    if (huong == TREN) return DUOI;
    return TREN;
}
