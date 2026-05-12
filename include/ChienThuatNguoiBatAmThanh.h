#pragma once

#include "ChienThuat.h"

#include <vector>
using namespace std;

class ChienThuatNguoiBat_AmThanh : public ChienThuatNguoiBat {
private:
    double laytiledoandung(int khoangCachNganNhat) const;
    vector<HuongNhin> laycacHuongCoMucTieu(const BanDo& bando, const vitri& viTriNguoiBat, const vector<vitri>& dsMucTieu) const;
    vector<HuongNhin> laycacHuongDungNhat(const BanDo& bando, const vitri& viTriNguoiBat, const vector<vitri>& dsMucTieu, int& kcGanNhat) const;
    HuongNhin layhuongngaunhien(const vector<HuongNhin>& dsHuong) const;
    vector<HuongNhin> truhuong(const vector<HuongNhin>& dsTatCa, const vector<HuongNhin>& dsLoaiRa) const;
    vitri dichuyenTheoCoXacSuat(const BanDo& bando, const vitri& viTriNguoiBat, const vector<vitri>& dsMucTieu, bool batBuocTheoDungMucTieuGanNhat) const;

public:
    vitri chonodedi(
        const BanDo& bando,
        const NguoiBat& nguoiBat,
        const vector<vitri>& dsVitriDeTheoAmThanh,
        const vector<SuKienVaCham>& dsSuKienVaChamDangBiet
    ) const override;
};
