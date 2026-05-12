#pragma once

#include "ViTri.h"

#include <string>
using namespace std;

class NhanVat {
protected:
    int maSo = -1;
    vitri viTriHienTai;
    string tenLoai;

public:
    NhanVat(int ma, const string& loai);
    virtual ~NhanVat();

    int getmaSo() const;
    string gettenLoai() const;
    vitri getvitri() const;
    void setvitri(const vitri& a);
};
