#include "ScoreHelper.h"

#include "Config.h"
#include "Random.h"

#include <algorithm>
#include <map>
using namespace std;

vector<int> TinhRankTangDan(const vector<int>& dsGiaTri) {
    vector<int> giaTriPhanBiet = dsGiaTri;
    sort(giaTriPhanBiet.begin(), giaTriPhanBiet.end());
    giaTriPhanBiet.erase(unique(giaTriPhanBiet.begin(), giaTriPhanBiet.end()), giaTriPhanBiet.end());

    map<int, int> bangRank;
    for (int i = 0; i < (int)giaTriPhanBiet.size(); i++) {
        bangRank[giaTriPhanBiet[i]] = i + 1;
    }

    vector<int> dsRank(dsGiaTri.size(), 1);
    for (int i = 0; i < (int)dsGiaTri.size(); i++) {
        dsRank[i] = bangRank[dsGiaTri[i]];
    }
    return dsRank;
}

vector<vitri> LayCacDeKhacDangNhinThay(const BanDo& bando, const De& banThan, const vector<De>& dsDe) {
    vector<vitri> ds;
    for (const De& deKhac : dsDe) {
        if (deKhac.getmaSo() == banThan.getmaSo()) continue;
        if (bando.nhinthay(banThan.getvitri(), banThan.gethuongnhin(), deKhac.getvitri())) {
            ds.push_back(deKhac.getvitri());
        }
    }
    return ds;
}

vector<vitri> LayCacDeKhacTheoBoNhoChoCach3(const BanDo& bando, const De& banThan, const vector<De>& dsDe) {
    vector<vitri> ds;
    for (const De& deKhac : dsDe) {
        if (deKhac.getmaSo() == banThan.getmaSo()) continue;

        if (bando.nhinthay(banThan.getvitri(), banThan.gethuongnhin(), deKhac.getvitri())) {
            ds.push_back(deKhac.getvitri());
        }
        else if (banThan.cobonhode(deKhac.getmaSo())) {
            ds.push_back(banThan.laybonhode(deKhac.getmaSo()));
        }
    }
    return ds;
}

QuyetDinhDe RaQuyetDinhTheoHamScore(
    const BanDo& bando,
    const De& banThan,
    const vitri& viTriMucTieuChinh,
    bool batBuocMucTieuPhaiNamTrongTamNhin,
    const vitri* viTriNguyHiemBiBat,
    const vector<vitri>& dsDeKhacDeTinhKhoangCach
) {
    QuyetDinhDe qd;
    qd.viTriMoi = banThan.getvitri();
    qd.huongMoi = banThan.gethuongnhin();

    vitri viTriDe = banThan.getvitri();
    HuongNhin huongNhin = banThan.gethuongnhin();

    if (batBuocMucTieuPhaiNamTrongTamNhin && !bando.nhinthay(viTriDe, huongNhin, viTriMucTieuChinh)) {
        qd.coDoiHuong = true;
        qd.huongMoi = bando.chonhuongnhintoimuctieu(viTriDe, viTriMucTieuChinh, huongNhin);
        qd.viTriMoi = viTriDe;
        return qd;
    }

    vector<vitri> dsOCoTheDi = bando.cacocothedi(viTriDe);
    const int tmp = -1000000000;

    vector<int> rawKcMucTieu;
    vector<int> rawKcBien;
    vector<int> rawSoOCoTheDi;
    vector<int> rawKcDeGanNhat;
    vector<bool> hopLe(dsOCoTheDi.size(), true);

    for (int i = 0; i < (int)dsOCoTheDi.size(); i++) {
        const vitri& oMoi = dsOCoTheDi[i];
        bool viPham = false;

        if (viTriNguyHiemBiBat != nullptr && oMoi.khoangcach(*viTriNguyHiemBiBat) <= 1) {
            viPham = true;
        }

        if (batBuocMucTieuPhaiNamTrongTamNhin && !bando.nhinthay(oMoi, huongNhin, viTriMucTieuChinh)) {
            viPham = true;
        }

        if (viPham) {
            hopLe[i] = false;
            rawKcMucTieu.push_back(tmp);
            rawKcBien.push_back(tmp);
            rawSoOCoTheDi.push_back(tmp);
            rawKcDeGanNhat.push_back(tmp);
            continue;
        }

        rawKcMucTieu.push_back(oMoi.khoangcach(viTriMucTieuChinh));
        rawKcBien.push_back(bando.khoangcachtoibien(oMoi));
        rawSoOCoTheDi.push_back((int)bando.cacocothedi(oMoi).size());

        if (dsDeKhacDeTinhKhoangCach.empty()) {
            rawKcDeGanNhat.push_back(0);
        }
        else {
            int kcMin = 1000000000;
            for (const vitri& v : dsDeKhacDeTinhKhoangCach) {
                kcMin = min(kcMin, oMoi.khoangcach(v));
            }
            rawKcDeGanNhat.push_back(kcMin);
        }
    }

    vector<int> rankKcMucTieu = TinhRankTangDan(rawKcMucTieu);
    vector<int> rankKcBien = TinhRankTangDan(rawKcBien);
    vector<int> rankSoOCoTheDi = TinhRankTangDan(rawSoOCoTheDi);
    vector<int> rankKcDeGanNhat = TinhRankTangDan(rawKcDeGanNhat);

    long long diemMax = -1000000000LL;
    vector<int> dsChiSoMax;

    for (int i = 0; i < (int)dsOCoTheDi.size(); i++) {
        long long diem = -1000000000LL;

        if (hopLe[i]) {
            diem = 0;
            diem += 1LL * HS_khoangcachtoinguoibat * rankKcMucTieu[i];
            diem += 1LL * HS_khoangcachtoibien * rankKcBien[i];
            diem += 1LL * HS_sootieptheocothedi * rankSoOCoTheDi[i];
            diem += 1LL * HS_khoangcachtoidegannhat * rankKcDeGanNhat[i];
        }

        if (diem > diemMax) {
            diemMax = diem;
            dsChiSoMax.clear();
            dsChiSoMax.push_back(i);
        }
        else if (diem == diemMax) {
            dsChiSoMax.push_back(i);
        }
    }

    int chiSoChon = dsChiSoMax[RandInt(0, (int)dsChiSoMax.size() - 1)];
    qd.viTriMoi = dsOCoTheDi[chiSoChon];
    return qd;
}
