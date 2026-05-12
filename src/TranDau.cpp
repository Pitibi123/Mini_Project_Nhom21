#include "TranDau.h"

#include "Config.h"
#include "Random.h"

#include <algorithm>
using namespace std;

TranDau::TranDau(const ChienThuatDe* chienThuatDe, const ChienThuatNguoiBat* chienThuatNguoiBat) : nguoiBat(0, chienThuatNguoiBat) {
    chienThuatDeCuaTran = chienThuatDe;
    dsDe.clear();
    for (int i = 0; i < sode; i++) {
        dsDe.push_back(De(i + 1, chienThuatDe));
    }
}

vector<vitri> TranDau::layvitricacde() const {
    vector<vitri> ds;
    for (const De& de : dsDe) ds.push_back(de.getvitri());
    return ds;
}

bool TranDau::trungvitri(const vitri& a, const vector<vitri>& ds) const {
    for (const vitri& x : ds) {
        if (x == a) return true;
    }
    return false;
}

void TranDau::ganhuongnhinbandau() {
    vitri viTriNguoiBat = nguoiBat.getvitri();
    for (De& de : dsDe) {
        HuongNhin huongMoi = bando.chonhuongnhintoimuctieu(de.getvitri(), viTriNguoiBat, de.gethuongnhin());
        de.sethuongnhin(huongMoi);
    }
}

vector<int> TranDau::laydanhsachdebiBat() const {
    vector<int> dsChiSo;
    for (int i = 0; i < (int)dsDe.size(); i++) {
        if (bando.debibat(dsDe[i].getvitri(), nguoiBat.getvitri())) {
            dsChiSo.push_back(i);
        }
    }
    return dsChiSo;
}

int TranDau::batngaunhien1de(const vector<int>& dsChiSo) const {
    if (dsChiSo.empty()) return -1;
    return dsChiSo[RandInt(0, (int)dsChiSo.size() - 1)];
}

vector<SuKienVaCham> TranDau::phathienvacapnhatvate(const vector<vitri>& vitriCu, const vector<vitri>& vitriMoi) {
    vector<SuKienVaCham> dsSuKienMoi;
    vector<int> dsDeBiStun;

    for (int i = 0; i < (int)dsDe.size(); i++) {
        for (int j = i + 1; j < (int)dsDe.size(); j++) {
            int kcCu = vitriCu[i].khoangcach(vitriCu[j]);
            int kcMoi = vitriMoi[i].khoangcach(vitriMoi[j]);
            if (kcCu > 1 && kcMoi <= 1) {
                SuKienVaCham suKien;
                suKien.vitriDe1 = vitriMoi[i];
                suKien.vitriDe2 = vitriMoi[j];
                suKien.soLuotConBiStun = soluotstun;
                dsSuKienMoi.push_back(suKien);
                dsDeBiStun.push_back(i);
                dsDeBiStun.push_back(j);
            }
        }
    }

    sort(dsDeBiStun.begin(), dsDeBiStun.end());
    dsDeBiStun.erase(unique(dsDeBiStun.begin(), dsDeBiStun.end()), dsDeBiStun.end());

    for (int chiSo : dsDeBiStun) {
        dsDe[chiSo].setstun(soluotstun);
    }

    return dsSuKienMoi;
}

void TranDau::capnhatsuKienDangBiet(vector<SuKienVaCham>& dsDangBiet, const vector<SuKienVaCham>& dsMoiDuocNghe) const {
    for (const SuKienVaCham& sk : dsMoiDuocNghe) {
        dsDangBiet.push_back(sk);
    }
}

void TranDau::giamsoluotstuncuacacsukien(vector<SuKienVaCham>& dsDangBiet) const {
    vector<SuKienVaCham> dsConLai;
    for (SuKienVaCham sk : dsDangBiet) {
        if (sk.soLuotConBiStun > 0) sk.soLuotConBiStun--;
        if (sk.soLuotConBiStun > 0) dsConLai.push_back(sk);
    }
    dsDangBiet = dsConLai;
}

void TranDau::khoitaongaunhien() {
    vector<vitri> dsVitriDaDung;
    vitri viTriNguoiBat;

    while (true) {
        dsVitriDaDung.clear();
        viTriNguoiBat = { RandInt(0, sohang - 1), RandInt(0, socot - 1) };
        dsVitriDaDung.push_back(viTriNguoiBat);

        bool hopLe = true;
        for (int i = 0; i < sode; i++) {
            bool datDuoc = false;
            for (int thu = 0; thu < 10000; thu++) {
                vitri viTriDe = { RandInt(0, sohang - 1), RandInt(0, socot - 1) };
                if (trungvitri(viTriDe, dsVitriDaDung)) continue;
                if (viTriDe.khoangcach(viTriNguoiBat) <= 3) continue;
                dsVitriDaDung.push_back(viTriDe);
                dsDe[i].setvitri(viTriDe);
                datDuoc = true;
                break;
            }
            if (!datDuoc) {
                hopLe = false;
                break;
            }
        }

        if (hopLe) break;
    }

    nguoiBat.setvitri(viTriNguoiBat);
    ganhuongnhinbandau();

    for (int i = 0; i < sode; i++) {
        dsDe[i].resetTrangThaiChienThuat(sode, chienThuatDeCuaTran->layChuKyKhaoSat());
        dsDe[i].capNhatBoNhoDayDu(dsDe, nguoiBat);
    }

    if (chon_de_ban_than_ngau_nhien) {
        chiSoDeBanThan = RandInt(0, sode - 1);
    }
    else {
        chiSoDeBanThan = max(0, min(sode - 1, chi_so_de_ban_than_co_dinh));
    }
}

KetQuaTran TranDau::choi1tran() {
    vector<SuKienVaCham> dsSuKienNguoiBatDangBiet;
    vector<SuKienVaCham> dsSuKienSeDuocNgheOLuotSau;

    for (int luot = 1; luot <= soluottoida; luot++) {
        capnhatsuKienDangBiet(dsSuKienNguoiBatDangBiet, dsSuKienSeDuocNgheOLuotSau);
        dsSuKienSeDuocNgheOLuotSau.clear();

        for (De& de : dsDe) {
            de.capNhatBoNhoTuTamNhin(bando, dsDe, nguoiBat);
        }

        vector<vitri> vitriDeTheoAmThanh = layvitricacde();
        vector<vitri> vitriDeCu = vitriDeTheoAmThanh;

        vector<QuyetDinhDe> dsQuyetDinh(dsDe.size());
        for (int i = 0; i < (int)dsDe.size(); i++) {
            if (dsDe[i].dangbistun()) {
                dsQuyetDinh[i].viTriMoi = dsDe[i].getvitri();
                dsQuyetDinh[i].huongMoi = dsDe[i].gethuongnhin();
                continue;
            }
            dsQuyetDinh[i] = dsDe[i].layhanhdong(bando, dsDe, nguoiBat);
        }

        for (int i = 0; i < (int)dsDe.size(); i++) {
            if (dsDe[i].dangbistun()) {
                dsDe[i].giamstunsau1luot();
            }
            else {
                if (dsQuyetDinh[i].coDoiHuong) {
                    dsDe[i].sethuongnhin(dsQuyetDinh[i].huongMoi);
                }
                dsDe[i].setvitri(dsQuyetDinh[i].viTriMoi);
            }

            if (!dsDe[i].getdangKhaoSat() && dsDe[i].getdemLuotConLaiDenLanKhaoSat() > 0) {
                dsDe[i].giam1luotChoBoDemKhaoSat();
            }
        }

        vector<vitri> vitriDeMoi = layvitricacde();
        dsSuKienSeDuocNgheOLuotSau = phathienvacapnhatvate(vitriDeCu, vitriDeMoi);

        vector<int> dsChiSoBiBat = laydanhsachdebiBat();
        if (!dsChiSoBiBat.empty()) {
            int deBiBat = batngaunhien1de(dsChiSoBiBat);
            KetQuaTran ketQua;
            ketQua.nguoiBatThang = true;
            ketQua.chiSoDeBiBat = deBiBat;
            ketQua.chiSoDeBanThan = chiSoDeBanThan;
            ketQua.deBanThanThang = (deBiBat != chiSoDeBanThan);
            ketQua.soLuotDaChoi = luot;
            return ketQua;
        }

        vitri viTriNguoiBatMoi = nguoiBat.layvitritoiuu(bando, vitriDeTheoAmThanh, dsSuKienNguoiBatDangBiet);
        nguoiBat.setvitri(viTriNguoiBatMoi);

        dsChiSoBiBat = laydanhsachdebiBat();
        if (!dsChiSoBiBat.empty()) {
            int deBiBat = batngaunhien1de(dsChiSoBiBat);
            KetQuaTran ketQua;
            ketQua.nguoiBatThang = true;
            ketQua.chiSoDeBiBat = deBiBat;
            ketQua.chiSoDeBanThan = chiSoDeBanThan;
            ketQua.deBanThanThang = (deBiBat != chiSoDeBanThan);
            ketQua.soLuotDaChoi = luot;
            return ketQua;
        }

        giamsoluotstuncuacacsukien(dsSuKienNguoiBatDangBiet);
    }

    KetQuaTran ketQua;
    ketQua.nguoiBatThang = false;
    ketQua.chiSoDeBiBat = -1;
    ketQua.chiSoDeBanThan = chiSoDeBanThan;
    ketQua.deBanThanThang = true;
    ketQua.soLuotDaChoi = soluottoida;
    return ketQua;
}
