#pragma once

#include "HuongNhin.h"
#include "ViTri.h"

#include <vector>
using namespace std;

class BanDo {
public:
    bool namtrongbando(const vitri& a) const;
    vector<vitri> cacocothedi(const vitri& a) const;
    vector<HuongNhin> cachuongdihople(const vitri& a) const;
    vitri dichuyentheohuong(const vitri& a, HuongNhin huong) const;
    int khoangcachtoibien(const vitri& a) const;
    bool debibat(const vitri& vitriDe, const vitri& vitriNguoiBat) const;
    bool nhinthay(const vitri& nguon, HuongNhin huong, const vitri& mucTieu) const;
    vector<HuongNhin> cachuongcohenhinthay(const vitri& nguon, const vitri& mucTieu) const;
    HuongNhin chonhuongnhintoimuctieu(const vitri& nguon, const vitri& mucTieu, HuongNhin huongHienTai) const;
};
