#pragma once

#include "HuongNhin.h"
#include "ViTri.h"
using namespace std;

struct QuyetDinhDe {
    bool coDoiHuong = false;
    HuongNhin huongMoi = TRAI;
    vitri viTriMoi;
};

struct SuKienVaCham {
    vitri vitriDe1;
    vitri vitriDe2;
    int soLuotConBiStun = 0;
};

struct KetQuaTran {
    bool nguoiBatThang = false;
    int chiSoDeBiBat = -1;
    int chiSoDeBanThan = 0;
    bool deBanThanThang = false;
    int soLuotDaChoi = 0;
};

struct ThongKeMoPhong {
    int soTranDeBanThanThang = 0;
    int soTranNguoiBatThang = 0;
    int soTranKhongAiBiBat = 0;
    int soTranDeBanThanBiBat = 0;
};
