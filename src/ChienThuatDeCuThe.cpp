#include "ChienThuatDeCuThe.h"

#include "Config.h"
#include "De.h"
#include "NguoiBat.h"
#include "Random.h"
#include "ScoreHelper.h"

#include <algorithm>
using namespace std;

QuyetDinhDe ChienThuatDe_Cach1::chonhanhdong(const BanDo& bando, De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const {
    vector<vitri> dsDeDangThay = LayCacDeKhacDangNhinThay(bando, banThan, dsDe);
    vitri viTriNguoiBat = nguoiBat.getvitri();
    return RaQuyetDinhTheoHamScore(
        bando,
        banThan,
        viTriNguoiBat,
        true,
        &viTriNguoiBat,
        dsDeDangThay
    );
}

void ChienThuatDe_Cach2::ChonLaiCheDoCach2TuBoNho(De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const {
    vitri viTriNguoiBat;

    if (banThan.cobonhonguoibat()) viTriNguoiBat = banThan.laybonhonguoibat();
    else viTriNguoiBat = nguoiBat.getvitri();

    int kcMin = banThan.getvitri().khoangcach(viTriNguoiBat);
    vector<int> dsMaDeGanNhat;
    dsMaDeGanNhat.push_back(banThan.getmaSo());

    for (const De& deKhac : dsDe) {
        if (deKhac.getmaSo() == banThan.getmaSo()) continue;

        vitri viTriDeKhac;
        if (banThan.cobonhode(deKhac.getmaSo())) viTriDeKhac = banThan.laybonhode(deKhac.getmaSo());
        else viTriDeKhac = deKhac.getvitri();

        int kc = viTriDeKhac.khoangcach(viTriNguoiBat);
        if (kc < kcMin) {
            kcMin = kc;
            dsMaDeGanNhat.clear();
            dsMaDeGanNhat.push_back(deKhac.getmaSo());
        }
        else if (kc == kcMin) {
            dsMaDeGanNhat.push_back(deKhac.getmaSo());
        }
    }

    bool banThanDangGanNhat = false;
    for (int ma : dsMaDeGanNhat) {
        if (ma == banThan.getmaSo()) {
            banThanDangGanNhat = true;
            break;
        }
    }

    banThan.setcach2DaChonCheDo(true);
    banThan.setdemLuotConLaiDenLanKhaoSat(CHU_KY_KHAO_SAT_CACH_2);

    if (banThanDangGanNhat) {
        banThan.setcach2DangDungCach1(true);
        banThan.setmaDeMucTieuCach2(-1);
        return;
    }

    vector<int> dsMucTieuHopLe;
    for (int ma : dsMaDeGanNhat) {
        if (ma != banThan.getmaSo()) dsMucTieuHopLe.push_back(ma);
    }

    if (dsMucTieuHopLe.empty()) {
        banThan.setcach2DangDungCach1(true);
        banThan.setmaDeMucTieuCach2(-1);
        return;
    }

    int maMucTieu = dsMucTieuHopLe[RandInt(0, (int)dsMucTieuHopLe.size() - 1)];
    banThan.setcach2DangDungCach1(false);
    banThan.setmaDeMucTieuCach2(maMucTieu);
}

int ChienThuatDe_Cach2::layChuKyKhaoSat() const {
    return CHU_KY_KHAO_SAT_CACH_2;
}

QuyetDinhDe ChienThuatDe_Cach2::chonhanhdong(const BanDo& bando, De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const {
    if (!banThan.getcach2DaChonCheDo()) {
        ChonLaiCheDoCach2TuBoNho(banThan, dsDe, nguoiBat);
    }

    if (banThan.getdemLuotConLaiDenLanKhaoSat() == 0 && !banThan.getdangKhaoSat()) {
        banThan.batDau1DotKhaoSatToiUu();
        banThan.capNhatBoNhoTuTamNhin(bando, dsDe, nguoiBat);
    }

    if (banThan.getdangKhaoSat()) {
        if (banThan.dathaytatcaTrongDotKhaoSat()) {
            banThan.ketThuc1DotKhaoSat();
            ChonLaiCheDoCach2TuBoNho(banThan, dsDe, nguoiBat);
        }
        else {
            if (banThan.conhuongKhaoSatTiepTheo()) {
                QuyetDinhDe qd;
                qd.coDoiHuong = true;
                qd.huongMoi = banThan.layhuongKhaoSatTiepTheo();
                qd.viTriMoi = banThan.getvitri();
                return qd;
            }
            else {
                banThan.ketThuc1DotKhaoSat();
                ChonLaiCheDoCach2TuBoNho(banThan, dsDe, nguoiBat);
            }
        }
    }

    if (banThan.getcach2DangDungCach1()) {
        vector<vitri> dsDeDangThay = LayCacDeKhacDangNhinThay(bando, banThan, dsDe);
        vitri viTriNguoiBat = nguoiBat.getvitri();

        return RaQuyetDinhTheoHamScore(
            bando,
            banThan,
            viTriNguoiBat,
            true,
            &viTriNguoiBat,
            dsDeDangThay
        );
    }

    int maMucTieu = banThan.getmaDeMucTieuCach2();
    if (maMucTieu <= 0) {
        vector<vitri> dsDeDangThay = LayCacDeKhacDangNhinThay(bando, banThan, dsDe);
        vitri viTriNguoiBat = nguoiBat.getvitri();

        return RaQuyetDinhTheoHamScore(
            bando,
            banThan,
            viTriNguoiBat,
            true,
            &viTriNguoiBat,
            dsDeDangThay
        );
    }

    vitri viTriDeMucTieu;
    if (bando.nhinthay(banThan.getvitri(), banThan.gethuongnhin(), dsDe[maMucTieu - 1].getvitri())) {
        viTriDeMucTieu = dsDe[maMucTieu - 1].getvitri();
    }
    else if (banThan.cobonhode(maMucTieu)) {
        viTriDeMucTieu = banThan.laybonhode(maMucTieu);
    }
    else {
        viTriDeMucTieu = dsDe[maMucTieu - 1].getvitri();
    }

    vector<vitri> dsDeDangThay = LayCacDeKhacDangNhinThay(bando, banThan, dsDe);

    const vitri* viTriNguyHiem = nullptr;
    vitri viTriNguoiBat;
    if (bando.nhinthay(banThan.getvitri(), banThan.gethuongnhin(), nguoiBat.getvitri())) {
        viTriNguoiBat = nguoiBat.getvitri();
        viTriNguyHiem = &viTriNguoiBat;
    }

    return RaQuyetDinhTheoHamScore(
        bando,
        banThan,
        viTriDeMucTieu,
        true,
        viTriNguyHiem,
        dsDeDangThay
    );
}

int ChienThuatDe_Cach3::layChuKyKhaoSat() const {
    return CHU_KY_KHAO_SAT_CACH_3;
}

QuyetDinhDe ChienThuatDe_Cach3::chonhanhdong(const BanDo& bando, De& banThan, const vector<De>& dsDe, const NguoiBat& nguoiBat) const {
    if (banThan.getdemLuotConLaiDenLanKhaoSat() == 0 && !banThan.getdangKhaoSat()) {
        banThan.batDau1DotKhaoSatToiUu();
        banThan.capNhatBoNhoTuTamNhin(bando, dsDe, nguoiBat);
    }

    if (banThan.getdangKhaoSat()) {
        if (banThan.dathaytatcaTrongDotKhaoSat()) {
            banThan.ketThuc1DotKhaoSat();
            banThan.setdemLuotConLaiDenLanKhaoSat(CHU_KY_KHAO_SAT_CACH_3);
        }
        else {
            if (banThan.conhuongKhaoSatTiepTheo()) {
                QuyetDinhDe qd;
                qd.coDoiHuong = true;
                qd.huongMoi = banThan.layhuongKhaoSatTiepTheo();
                qd.viTriMoi = banThan.getvitri();
                return qd;
            }
            else {
                banThan.ketThuc1DotKhaoSat();
                banThan.setdemLuotConLaiDenLanKhaoSat(CHU_KY_KHAO_SAT_CACH_3);
            }
        }
    }

    vitri viTriNguoiBatDeTinh;
    if (bando.nhinthay(banThan.getvitri(), banThan.gethuongnhin(), nguoiBat.getvitri())) {
        viTriNguoiBatDeTinh = nguoiBat.getvitri();
    }
    else if (banThan.cobonhonguoibat()) {
        viTriNguoiBatDeTinh = banThan.laybonhonguoibat();
    }
    else {
        viTriNguoiBatDeTinh = nguoiBat.getvitri();
    }

    vector<vitri> dsDeKhac = LayCacDeKhacTheoBoNhoChoCach3(bando, banThan, dsDe);

    return RaQuyetDinhTheoHamScore(
        bando,
        banThan,
        viTriNguoiBatDeTinh,
        false,
        &viTriNguoiBatDeTinh,
        dsDeKhac
    );
}
