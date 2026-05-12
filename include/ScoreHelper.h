#pragma once

#include "BanDo.h"
#include "De.h"
#include "KieuDuLieu.h"
#include "NguoiBat.h"

#include <vector>
using namespace std;

vector<int> TinhRankTangDan(const vector<int>& dsGiaTri);
vector<vitri> LayCacDeKhacDangNhinThay(const BanDo& bando, const De& banThan, const vector<De>& dsDe);
vector<vitri> LayCacDeKhacTheoBoNhoChoCach3(const BanDo& bando, const De& banThan, const vector<De>& dsDe);

QuyetDinhDe RaQuyetDinhTheoHamScore(
    const BanDo& bando,
    const De& banThan,
    const vitri& viTriMucTieuChinh,
    bool batBuocMucTieuPhaiNamTrongTamNhin,
    const vitri* viTriNguyHiemBiBat,
    const vector<vitri>& dsDeKhacDeTinhKhoangCach
);
