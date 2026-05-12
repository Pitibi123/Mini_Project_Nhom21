#include "ChienThuatNguoiBatAmThanh.h"

#include "Config.h"
#include "NguoiBat.h"
#include "Random.h"

#include <algorithm>
#include <set>
using namespace std;

double ChienThuatNguoiBat_AmThanh::laytiledoandung(int khoangCachNganNhat) const {
    if (khoangCachNganNhat <= 3) return tile_dung_neu_kc_le_3;
    if (khoangCachNganNhat <= 5) return tile_dung_neu_kc_le_5;
    if (khoangCachNganNhat <= 7) return tile_dung_neu_kc_le_7;
    return -1.0;
}

vector<HuongNhin> ChienThuatNguoiBat_AmThanh::laycacHuongCoMucTieu(const BanDo& bando, const vitri& viTriNguoiBat, const vector<vitri>& dsMucTieu) const {
    set<HuongNhin> tapHuong;
    for (const vitri& mucTieu : dsMucTieu) {
        vector<HuongNhin> huongs = bando.cachuongcohenhinthay(viTriNguoiBat, mucTieu);
        for (HuongNhin h : huongs) tapHuong.insert(h);
    }
    vector<HuongNhin> ketQua(tapHuong.begin(), tapHuong.end());
    return ketQua;
}

vector<HuongNhin> ChienThuatNguoiBat_AmThanh::laycacHuongDungNhat(const BanDo& bando, const vitri& viTriNguoiBat, const vector<vitri>& dsMucTieu, int& kcGanNhat) const {
    kcGanNhat = 1000000000;
    for (const vitri& mucTieu : dsMucTieu) {
        kcGanNhat = min(kcGanNhat, viTriNguoiBat.khoangcach(mucTieu));
    }

    set<HuongNhin> tapHuongDung;
    for (const vitri& mucTieu : dsMucTieu) {
        if (viTriNguoiBat.khoangcach(mucTieu) == kcGanNhat) {
            vector<HuongNhin> huongs = bando.cachuongcohenhinthay(viTriNguoiBat, mucTieu);
            for (HuongNhin h : huongs) tapHuongDung.insert(h);
        }
    }
    vector<HuongNhin> ketQua(tapHuongDung.begin(), tapHuongDung.end());
    return ketQua;
}

HuongNhin ChienThuatNguoiBat_AmThanh::layhuongngaunhien(const vector<HuongNhin>& dsHuong) const {
    return dsHuong[RandInt(0, (int)dsHuong.size() - 1)];
}

vector<HuongNhin> ChienThuatNguoiBat_AmThanh::truhuong(const vector<HuongNhin>& dsTatCa, const vector<HuongNhin>& dsLoaiRa) const {
    vector<HuongNhin> ketQua;
    for (HuongNhin h : dsTatCa) {
        bool biLoai = false;
        for (HuongNhin x : dsLoaiRa) {
            if (x == h) {
                biLoai = true;
                break;
            }
        }
        if (!biLoai) ketQua.push_back(h);
    }
    return ketQua;
}

vitri ChienThuatNguoiBat_AmThanh::dichuyenTheoCoXacSuat(const BanDo& bando, const vitri& viTriNguoiBat, const vector<vitri>& dsMucTieu, bool batBuocTheoDungMucTieuGanNhat) const {
    vector<HuongNhin> dsHuongHopLeTrongBan = bando.cachuongdihople(viTriNguoiBat);
    if (dsHuongHopLeTrongBan.empty()) return viTriNguoiBat;

    vector<HuongNhin> dsHuongCoMucTieu = laycacHuongCoMucTieu(bando, viTriNguoiBat, dsMucTieu);
    if (dsHuongCoMucTieu.empty()) {
        HuongNhin h = layhuongngaunhien(dsHuongHopLeTrongBan);
        return bando.dichuyentheohuong(viTriNguoiBat, h);
    }

    int kcGanNhat = 1000000000;
    vector<HuongNhin> dsHuongDung = laycacHuongDungNhat(bando, viTriNguoiBat, dsMucTieu, kcGanNhat);

    if (!batBuocTheoDungMucTieuGanNhat && kcGanNhat > 7) {
        HuongNhin h = layhuongngaunhien(dsHuongCoMucTieu);
        return bando.dichuyentheohuong(viTriNguoiBat, h);
    }

    double tiLeDung = laytiledoandung(kcGanNhat);
    if (tiLeDung < 0.0) {
        HuongNhin h = layhuongngaunhien(dsHuongCoMucTieu);
        return bando.dichuyentheohuong(viTriNguoiBat, h);
    }

    bool diDung = RandDouble01() <= tiLeDung;
    if (diDung) {
        HuongNhin h = layhuongngaunhien(dsHuongDung);
        return bando.dichuyentheohuong(viTriNguoiBat, h);
    }

    vector<HuongNhin> dsHuongSai = truhuong(dsHuongCoMucTieu, dsHuongDung);
    if (dsHuongSai.empty()) dsHuongSai = truhuong(dsHuongHopLeTrongBan, dsHuongDung);
    if (dsHuongSai.empty()) dsHuongSai = dsHuongHopLeTrongBan;

    HuongNhin h = layhuongngaunhien(dsHuongSai);
    return bando.dichuyentheohuong(viTriNguoiBat, h);
}

vitri ChienThuatNguoiBat_AmThanh::chonodedi(
    const BanDo& bando,
    const NguoiBat& nguoiBat,
    const vector<vitri>& dsVitriDeTheoAmThanh,
    const vector<SuKienVaCham>& dsSuKienVaChamDangBiet
) const {
    vitri viTriNguoiBat = nguoiBat.getvitri();

    int a = 1000000000;
    for (const vitri& v : dsVitriDeTheoAmThanh) {
        a = min(a, viTriNguoiBat.khoangcach(v));
    }

    bool uuTienVaCham = false;
    vector<vitri> dsMucTieuVaCham;
    int giaTriTotNhat = 1000000000;

    for (const SuKienVaCham& suKien : dsSuKienVaChamDangBiet) {
        int b = min(viTriNguoiBat.khoangcach(suKien.vitriDe1), viTriNguoiBat.khoangcach(suKien.vitriDe2));
        int c = suKien.soLuotConBiStun;
        if (b - c <= a) {
            int doUuTien = b - c;
            if (!uuTienVaCham || doUuTien < giaTriTotNhat) {
                uuTienVaCham = true;
                giaTriTotNhat = doUuTien;
                dsMucTieuVaCham.clear();
                if (viTriNguoiBat.khoangcach(suKien.vitriDe1) <= viTriNguoiBat.khoangcach(suKien.vitriDe2)) {
                    dsMucTieuVaCham.push_back(suKien.vitriDe1);
                }
                else {
                    dsMucTieuVaCham.push_back(suKien.vitriDe2);
                }
            }
        }
    }

    if (uuTienVaCham && !dsMucTieuVaCham.empty()) {
        return dichuyenTheoCoXacSuat(bando, viTriNguoiBat, dsMucTieuVaCham, true);
    }

    return dichuyenTheoCoXacSuat(bando, viTriNguoiBat, dsVitriDeTheoAmThanh, false);
}
