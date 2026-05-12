#pragma once

#include "ChienThuat.h"
#include "NhanVat.h"
using namespace std;

class NguoiBat : public NhanVat {
private:
    const ChienThuatNguoiBat* chienThuat = nullptr;

public:
    NguoiBat(int ma, const ChienThuatNguoiBat* chienThuatNguoiBat = nullptr);

    void ganChienThuat(const ChienThuatNguoiBat* chienThuatNguoiBat);
    vitri layvitritoiuu(
        const BanDo& bando,
        const vector<vitri>& dsVitriDeTheoAmThanh,
        const vector<SuKienVaCham>& dsSuKienVaChamDangBiet
    ) const;
};
