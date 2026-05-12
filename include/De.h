#pragma once

#include "ChienThuat.h"
#include "NhanVat.h"

#include <vector>
using namespace std;

class NguoiBat;

class De : public NhanVat {
private:
    HuongNhin huongNhin = TRAI;
    int soLuotConBiStun = 0;
    const ChienThuatDe* chienThuat = nullptr;

    vector<vitri> boNhoViTriDe;
    vector<bool> boNhoHopLeDe;
    vitri boNhoViTriNguoiBat;
    bool boNhoHopLeNguoiBat = false;

    bool dangKhaoSat = false;
    vector<HuongNhin> dsHuongCanKhaoSat;
    int chiSoHuongKhaoSatTiepTheo = 0;
    vector<bool> daThayDeTrongDotKhaoSat;
    bool daThayNguoiBatTrongDotKhaoSat = false;
    int demLuotConLaiDenLanKhaoSat = 0;

    int maDeMucTieuCach2 = -1;
    bool cach2_DangDungCach1 = false;
    bool cach2_DaChonCheDo = false;

public:
    De(int ma, const ChienThuatDe* chienThuatDe = nullptr);

    void ganChienThuat(const ChienThuatDe* chienThuatDe);
    int layChuKyKhaoSat() const;
    QuyetDinhDe layhanhdong(const BanDo& bando, const vector<De>& dsDe, const NguoiBat& nguoiBat);

    HuongNhin gethuongnhin() const;
    void sethuongnhin(HuongNhin huongMoi);

    int getsoluotconbistun() const;
    bool dangbistun() const;
    void setstun(int soLuot);
    void giamstunsau1luot();

    void resetTrangThaiChienThuat(int tongSoDe, int chuKyKhaoSat);
    void capNhatBoNhoDayDu(const vector<De>& dsDe, const NguoiBat& nguoiBat);
    void capNhatBoNhoTuTamNhin(const BanDo& bando, const vector<De>& dsDe, const NguoiBat& nguoiBat);

    bool cobonhonguoibat() const;
    vitri laybonhonguoibat() const;
    bool cobonhode(int maDe) const;
    vitri laybonhode(int maDe) const;

    void setdemLuotConLaiDenLanKhaoSat(int soLuot);
    int getdemLuotConLaiDenLanKhaoSat() const;
    void giam1luotChoBoDemKhaoSat();

    bool getdangKhaoSat() const;
    void batDau1DotKhaoSatToiUu();
    bool dathaytatcaTrongDotKhaoSat() const;
    bool conhuongKhaoSatTiepTheo() const;
    HuongNhin layhuongKhaoSatTiepTheo();
    void ketThuc1DotKhaoSat();

    int getmaDeMucTieuCach2() const;
    void setmaDeMucTieuCach2(int maDe);

    bool getcach2DangDungCach1() const;
    void setcach2DangDungCach1(bool giaTri);

    bool getcach2DaChonCheDo() const;
    void setcach2DaChonCheDo(bool giaTri);
};
