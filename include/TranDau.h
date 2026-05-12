#pragma once

#include "BanDo.h"
#include "ChienThuat.h"
#include "De.h"
#include "KieuDuLieu.h"
#include "NguoiBat.h"

#include <vector>
using namespace std;

class TranDau {
private:
    BanDo bando;
    vector<De> dsDe;
    NguoiBat nguoiBat;
    int chiSoDeBanThan = 0;
    const ChienThuatDe* chienThuatDeCuaTran = nullptr;

    vector<vitri> layvitricacde() const;
    bool trungvitri(const vitri& a, const vector<vitri>& ds) const;
    void ganhuongnhinbandau();
    vector<int> laydanhsachdebiBat() const;
    int batngaunhien1de(const vector<int>& dsChiSo) const;
    vector<SuKienVaCham> phathienvacapnhatvate(const vector<vitri>& vitriCu, const vector<vitri>& vitriMoi);
    void capnhatsuKienDangBiet(vector<SuKienVaCham>& dsDangBiet, const vector<SuKienVaCham>& dsMoiDuocNghe) const;
    void giamsoluotstuncuacacsukien(vector<SuKienVaCham>& dsDangBiet) const;

public:
    TranDau(const ChienThuatDe* chienThuatDe, const ChienThuatNguoiBat* chienThuatNguoiBat);

    void khoitaongaunhien();
    KetQuaTran choi1tran();
};
