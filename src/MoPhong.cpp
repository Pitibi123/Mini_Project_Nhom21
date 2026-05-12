#include "MoPhong.h"

#include "Config.h"
#include "TranDau.h"

#include <iostream>
using namespace std;

ThongKeMoPhong MoPhong::run(const ChienThuatDe* chienThuatDe, const ChienThuatNguoiBat* chienThuatNguoiBat) {
    ThongKeMoPhong thongKe;

    for (int i = 1; i <= sotranmophong; i++) {
        TranDau tran(chienThuatDe, chienThuatNguoiBat);
        tran.khoitaongaunhien();
        KetQuaTran ketQua = tran.choi1tran();

        if (ketQua.deBanThanThang) thongKe.soTranDeBanThanThang++;
        if (ketQua.nguoiBatThang) thongKe.soTranNguoiBatThang++;
        if (!ketQua.nguoiBatThang) thongKe.soTranKhongAiBiBat++;
        if (ketQua.chiSoDeBiBat == ketQua.chiSoDeBanThan) thongKe.soTranDeBanThanBiBat++;
    }

    return thongKe;
}

void InKetQua(const string& tenChienThuat, const ThongKeMoPhong& ketQua) {
    cout << "===== " << tenChienThuat << " =====\n";
    cout << "So tran de ban than thang: " << ketQua.soTranDeBanThanThang << "\n";
    cout << "So tran de ban than bi bat: " << ketQua.soTranDeBanThanBiBat << "\n";
    cout << "So tran nguoi bat thang: " << ketQua.soTranNguoiBatThang << "\n";
    cout << "So tran het gio ma chua bat duoc de nao: " << ketQua.soTranKhongAiBiBat << "\n";
    cout << "Ti le de ban than thang: " << 100.0 * ketQua.soTranDeBanThanThang / sotranmophong << "%\n\n";
}
