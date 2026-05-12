#include "NhanVat.h"
using namespace std;

NhanVat::NhanVat(int ma, const string& loai) {
    maSo = ma;
    tenLoai = loai;
}

NhanVat::~NhanVat() {}

int NhanVat::getmaSo() const {
    return maSo;
}

string NhanVat::gettenLoai() const {
    return tenLoai;
}

vitri NhanVat::getvitri() const {
    return viTriHienTai;
}

void NhanVat::setvitri(const vitri& a) {
    viTriHienTai = a;
}
