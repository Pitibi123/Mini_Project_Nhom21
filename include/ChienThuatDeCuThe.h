#pragma once

#include "ChienThuat.h"
using namespace std;

class ChienThuatDe_Cach1 : public ChienThuatDe {
public:
    QuyetDinhDe chonhanhdong(const BanDo& bando, De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const override;
};

class ChienThuatDe_Cach2 : public ChienThuatDe {
private:
    void ChonLaiCheDoCach2TuBoNho(De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const;

public:
    int layChuKyKhaoSat() const override;
    QuyetDinhDe chonhanhdong(const BanDo& bando, De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const override;
};

class ChienThuatDe_Cach3 : public ChienThuatDe {
public:
    int layChuKyKhaoSat() const override;
    QuyetDinhDe chonhanhdong(const BanDo& bando, De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const override;
};
