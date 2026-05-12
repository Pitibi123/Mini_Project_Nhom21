#include "ChienThuatDeCuThe.h"
#include "ChienThuatNguoiBatAmThanh.h"
#include "Config.h"
#include "MoPhong.h"

#include <iostream>
using namespace std;

int main() {
    ChienThuatDe_Cach1 chienThuatDeCach1;
    ChienThuatDe_Cach2 chienThuatDeCach2;
    ChienThuatDe_Cach3 chienThuatDeCach3;
    ChienThuatNguoiBat_AmThanh chienThuatNguoiBat;

    MoPhong moPhong;

    cout << "===== THONG SO =====\n";
    cout << "Ban do: " << sohang << "x" << socot << "\n";
    cout << "So de: " << sode << "\n";
    cout << "So luot toi da: " << soluottoida << "\n";
    cout << "So tran mo phong: " << sotranmophong << "\n";
    cout << "HS_khoangcachtoibien = " << HS_khoangcachtoibien << "\n";
    cout << "HS_khoangcachtoidegannhat = " << HS_khoangcachtoidegannhat << "\n";
    cout << "HS_khoangcachtoinguoibat = " << HS_khoangcachtoinguoibat << "\n";
    cout << "HS_sootieptheocothedi = " << HS_sootieptheocothedi << "\n\n";

    ThongKeMoPhong ketQuaCach1 = moPhong.run(&chienThuatDeCach1, &chienThuatNguoiBat);
    ThongKeMoPhong ketQuaCach2 = moPhong.run(&chienThuatDeCach2, &chienThuatNguoiBat);
    ThongKeMoPhong ketQuaCach3 = moPhong.run(&chienThuatDeCach3, &chienThuatNguoiBat);

    InKetQua("Cach 1 - Luon de y nguoi bat", ketQuaCach1);
    InKetQua("Cach 2 - Danh lac huong", ketQuaCach2);
    InKetQua("Cach 3 - Nguoi choi he bao quat", ketQuaCach3);

    return 0;
}
