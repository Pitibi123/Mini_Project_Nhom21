#include "BanDo.h"

#include "Config.h"

#include <algorithm>
#include <cmath>
using namespace std;

bool BanDo::namtrongbando(const vitri& a) const {
    return a.hang >= 0 && a.hang < sohang && a.cot >= 0 && a.cot < socot;
}

vector<vitri> BanDo::cacocothedi(const vitri& a) const {
    vector<vitri> v;
    v.push_back(a);

    vitri tren = { a.hang - 1, a.cot };
    vitri duoi = { a.hang + 1, a.cot };
    vitri trai = { a.hang, a.cot - 1 };
    vitri phai = { a.hang, a.cot + 1 };

    if (namtrongbando(tren)) v.push_back(tren);
    if (namtrongbando(duoi)) v.push_back(duoi);
    if (namtrongbando(trai)) v.push_back(trai);
    if (namtrongbando(phai)) v.push_back(phai);

    return v;
}

vector<HuongNhin> BanDo::cachuongdihople(const vitri& a) const {
    vector<HuongNhin> v;
    if (namtrongbando({ a.hang - 1, a.cot })) v.push_back(TREN);
    if (namtrongbando({ a.hang + 1, a.cot })) v.push_back(DUOI);
    if (namtrongbando({ a.hang, a.cot - 1 })) v.push_back(TRAI);
    if (namtrongbando({ a.hang, a.cot + 1 })) v.push_back(PHAI);
    return v;
}

vitri BanDo::dichuyentheohuong(const vitri& a, HuongNhin huong) const {
    vitri b = a;
    if (huong == TREN) b.hang--;
    else if (huong == DUOI) b.hang++;
    else if (huong == TRAI) b.cot--;
    else if (huong == PHAI) b.cot++;

    if (namtrongbando(b)) return b;
    return a;
}

int BanDo::khoangcachtoibien(const vitri& a) const {
    return min(min(a.hang, sohang - 1 - a.hang), min(a.cot, socot - 1 - a.cot));
}

bool BanDo::debibat(const vitri& vitriDe, const vitri& vitriNguoiBat) const {
    return vitriDe.khoangcach(vitriNguoiBat) <= 1;
}

bool BanDo::nhinthay(const vitri& nguon, HuongNhin huong, const vitri& mucTieu) const {
    if (huong == TRAI) return mucTieu.cot < nguon.cot;
    if (huong == PHAI) return mucTieu.cot > nguon.cot;
    if (huong == TREN) return mucTieu.hang < nguon.hang;
    return mucTieu.hang > nguon.hang;
}

vector<HuongNhin> BanDo::cachuongcohenhinthay(const vitri& nguon, const vitri& mucTieu) const {
    vector<HuongNhin> huongs;
    if (mucTieu.cot < nguon.cot) huongs.push_back(TRAI);
    if (mucTieu.cot > nguon.cot) huongs.push_back(PHAI);
    if (mucTieu.hang < nguon.hang) huongs.push_back(TREN);
    if (mucTieu.hang > nguon.hang) huongs.push_back(DUOI);
    return huongs;
}

HuongNhin BanDo::chonhuongnhintoimuctieu(const vitri& nguon, const vitri& mucTieu, HuongNhin huongHienTai) const {
    vector<HuongNhin> huongs = cachuongcohenhinthay(nguon, mucTieu);
    if (huongs.empty()) return huongHienTai;
    if ((int)huongs.size() == 1) return huongs[0];

    HuongNhin huongDoiDien = HuongDoiDien(huongHienTai);
    for (HuongNhin h : huongs) {
        if (h == huongDoiDien) return h;
    }

    int doLechHang = abs(mucTieu.hang - nguon.hang);
    int doLechCot = abs(mucTieu.cot - nguon.cot);

    if (doLechCot >= doLechHang) {
        for (HuongNhin h : huongs) {
            if (h == TRAI || h == PHAI) return h;
        }
    }
    for (HuongNhin h : huongs) {
        if (h == TREN || h == DUOI) return h;
    }
    return huongs[0];
}
