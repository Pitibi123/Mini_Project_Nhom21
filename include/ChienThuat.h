#pragma once

#include "BanDo.h"
#include "KieuDuLieu.h"
#include "ViTri.h"

#include <vector>
using namespace std;

class De;
class NguoiBat;

class ChienThuatDe {
public:
    virtual ~ChienThuatDe() {}
    virtual QuyetDinhDe chonhanhdong(const BanDo& bando, De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const = 0;
    virtual int layChuKyKhaoSat() const {
        return 0;
    }
};

class ChienThuatNguoiBat {
public:
    virtual ~ChienThuatNguoiBat() {}
    virtual vitri chonodedi(
        const BanDo& bando,
        const NguoiBat& nguoiBat,
        const vector<vitri>& dsVitriDeTheoAmThanh,
        const vector<SuKienVaCham>& dsSuKienVaChamDangBiet
    ) const = 0;
};
