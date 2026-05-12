#pragma once

#include "ChienThuat.h"
#include "KieuDuLieu.h"

#include <string>
using namespace std;

class MoPhong {
public:
    ThongKeMoPhong run(const ChienThuatDe* chienThuatDe, const ChienThuatNguoiBat* chienThuatNguoiBat);
};

void InKetQua(const string& tenChienThuat, const ThongKeMoPhong& ketQua);
