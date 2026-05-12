#include "De.h"

#include "NguoiBat.h"

#include <algorithm>
using namespace std;

De::De(int ma, const ChienThuatDe* chienThuatDe) : NhanVat(ma, "De") {
    chienThuat = chienThuatDe;
}

void De::ganChienThuat(const ChienThuatDe* chienThuatDe) {
    chienThuat = chienThuatDe;
}

int De::layChuKyKhaoSat() const {
    if (chienThuat == nullptr) return 0;
    return chienThuat->layChuKyKhaoSat();
}

QuyetDinhDe De::layhanhdong(const BanDo& bando, const vector<De>& dsDe, const NguoiBat& nguoiBat) {
    if (chienThuat == nullptr) {
        QuyetDinhDe qd;
        qd.viTriMoi = viTriHienTai;
        qd.huongMoi = huongNhin;
        return qd;
    }
    return chienThuat->chonhanhdong(bando, *this, dsDe, nguoiBat);
}

HuongNhin De::gethuongnhin() const {
    return huongNhin;
}

void De::sethuongnhin(HuongNhin huongMoi) {
    huongNhin = huongMoi;
}

int De::getsoluotconbistun() const {
    return soLuotConBiStun;
}

bool De::dangbistun() const {
    return soLuotConBiStun > 0;
}

void De::setstun(int soLuot) {
    soLuotConBiStun = soLuot;
}

void De::giamstunsau1luot() {
    if (soLuotConBiStun > 0) soLuotConBiStun--;
}

void De::resetTrangThaiChienThuat(int tongSoDe, int chuKyKhaoSat) {
    soLuotConBiStun = 0;

    boNhoViTriDe.assign(tongSoDe, vitri());
    boNhoHopLeDe.assign(tongSoDe, false);
    boNhoHopLeNguoiBat = false;

    dangKhaoSat = false;
    dsHuongCanKhaoSat.clear();
    chiSoHuongKhaoSatTiepTheo = 0;
    daThayDeTrongDotKhaoSat.assign(tongSoDe, false);
    daThayNguoiBatTrongDotKhaoSat = false;
    demLuotConLaiDenLanKhaoSat = chuKyKhaoSat;

    maDeMucTieuCach2 = -1;
    cach2_DangDungCach1 = false;
    cach2_DaChonCheDo = false;
}

void De::capNhatBoNhoDayDu(const vector<De>& dsDe, const NguoiBat& nguoiBat) {
    for (const De& deKhac : dsDe) {
        int idx = deKhac.getmaSo() - 1;
        boNhoViTriDe[idx] = deKhac.getvitri();
        boNhoHopLeDe[idx] = true;
    }
    boNhoViTriNguoiBat = nguoiBat.getvitri();
    boNhoHopLeNguoiBat = true;
}

void De::capNhatBoNhoTuTamNhin(const BanDo& bando, const vector<De>& dsDe, const NguoiBat& nguoiBat) {
    int idxBanThan = maSo - 1;
    if (idxBanThan >= 0 && idxBanThan < (int)boNhoViTriDe.size()) {
        boNhoViTriDe[idxBanThan] = viTriHienTai;
        boNhoHopLeDe[idxBanThan] = true;
        if (dangKhaoSat) daThayDeTrongDotKhaoSat[idxBanThan] = true;
    }

    for (const De& deKhac : dsDe) {
        if (deKhac.getmaSo() == maSo) continue;
        if (bando.nhinthay(viTriHienTai, huongNhin, deKhac.getvitri())) {
            int idx = deKhac.getmaSo() - 1;
            boNhoViTriDe[idx] = deKhac.getvitri();
            boNhoHopLeDe[idx] = true;
            if (dangKhaoSat) daThayDeTrongDotKhaoSat[idx] = true;
        }
    }

    if (bando.nhinthay(viTriHienTai, huongNhin, nguoiBat.getvitri())) {
        boNhoViTriNguoiBat = nguoiBat.getvitri();
        boNhoHopLeNguoiBat = true;
        if (dangKhaoSat) daThayNguoiBatTrongDotKhaoSat = true;
    }
}

bool De::cobonhonguoibat() const {
    return boNhoHopLeNguoiBat;
}

vitri De::laybonhonguoibat() const {
    return boNhoViTriNguoiBat;
}

bool De::cobonhode(int maDe) const {
    int idx = maDe - 1;
    if (idx < 0 || idx >= (int)boNhoHopLeDe.size()) return false;
    return boNhoHopLeDe[idx];
}

vitri De::laybonhode(int maDe) const {
    return boNhoViTriDe[maDe - 1];
}

void De::setdemLuotConLaiDenLanKhaoSat(int soLuot) {
    demLuotConLaiDenLanKhaoSat = soLuot;
}

int De::getdemLuotConLaiDenLanKhaoSat() const {
    return demLuotConLaiDenLanKhaoSat;
}

void De::giam1luotChoBoDemKhaoSat() {
    if (demLuotConLaiDenLanKhaoSat > 0) demLuotConLaiDenLanKhaoSat--;
}

bool De::getdangKhaoSat() const {
    return dangKhaoSat;
}

void De::batDau1DotKhaoSatToiUu() {
    dangKhaoSat = true;
    dsHuongCanKhaoSat.clear();
    chiSoHuongKhaoSatTiepTheo = 0;
    daThayDeTrongDotKhaoSat.assign(daThayDeTrongDotKhaoSat.size(), false);
    daThayNguoiBatTrongDotKhaoSat = false;

    if (maSo - 1 >= 0 && maSo - 1 < (int)daThayDeTrongDotKhaoSat.size()) {
        daThayDeTrongDotKhaoSat[maSo - 1] = true;
    }

    HuongNhin huongDoiDien = HuongDoiDien(huongNhin);
    dsHuongCanKhaoSat.push_back(huongDoiDien);

    if (huongNhin == TRAI || huongNhin == PHAI) {
        dsHuongCanKhaoSat.push_back(TREN);
        dsHuongCanKhaoSat.push_back(DUOI);
    }
    else {
        dsHuongCanKhaoSat.push_back(TRAI);
        dsHuongCanKhaoSat.push_back(PHAI);
    }
}

bool De::dathaytatcaTrongDotKhaoSat() const {
    if (!daThayNguoiBatTrongDotKhaoSat) return false;
    for (int i = 0; i < (int)daThayDeTrongDotKhaoSat.size(); i++) {
        if (i == maSo - 1) continue;
        if (!daThayDeTrongDotKhaoSat[i]) return false;
    }
    return true;
}

bool De::conhuongKhaoSatTiepTheo() const {
    return chiSoHuongKhaoSatTiepTheo < (int)dsHuongCanKhaoSat.size();
}

HuongNhin De::layhuongKhaoSatTiepTheo() {
    if (!conhuongKhaoSatTiepTheo()) return huongNhin;
    return dsHuongCanKhaoSat[chiSoHuongKhaoSatTiepTheo++];
}

void De::ketThuc1DotKhaoSat() {
    dangKhaoSat = false;
    dsHuongCanKhaoSat.clear();
    chiSoHuongKhaoSatTiepTheo = 0;
    daThayNguoiBatTrongDotKhaoSat = false;
    daThayDeTrongDotKhaoSat.assign(daThayDeTrongDotKhaoSat.size(), false);
}

int De::getmaDeMucTieuCach2() const {
    return maDeMucTieuCach2;
}

void De::setmaDeMucTieuCach2(int maDe) {
    maDeMucTieuCach2 = maDe;
}

bool De::getcach2DangDungCach1() const {
    return cach2_DangDungCach1;
}

void De::setcach2DangDungCach1(bool giaTri) {
    cach2_DangDungCach1 = giaTri;
}

bool De::getcach2DaChonCheDo() const {
    return cach2_DaChonCheDo;
}

void De::setcach2DaChonCheDo(bool giaTri) {
    cach2_DaChonCheDo = giaTri;
}
