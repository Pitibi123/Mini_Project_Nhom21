#include "NguoiBat.h"
using namespace std;

NguoiBat::NguoiBat(int ma, const ChienThuatNguoiBat* chienThuatNguoiBat) : NhanVat(ma, "NguoiBat") {
    chienThuat = chienThuatNguoiBat;
}

void NguoiBat::ganChienThuat(const ChienThuatNguoiBat* chienThuatNguoiBat) {
    chienThuat = chienThuatNguoiBat;
}

vitri NguoiBat::layvitritoiuu(
    const BanDo& bando,
    const vector<vitri>& dsVitriDeTheoAmThanh,
    const vector<SuKienVaCham>& dsSuKienVaChamDangBiet
) const {
    if (chienThuat == nullptr) return viTriHienTai;
    return chienThuat->chonodedi(bando, *this, dsVitriDeTheoAmThanh, dsSuKienVaChamDangBiet);
}
