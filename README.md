# Mô phỏng trò chơi Bịt mắt bắt dê

Mini project C++ mô phỏng trò chơi có nhiều dê và một người bịt mắt trên bản đồ 2D. Dự án được tách file theo hướng OOP cơ bản để sinh viên năm nhất dễ đọc, dễ sửa và dễ đẩy lên GitHub.

## Ý tưởng chính

- Bản đồ là lưới 2 chiều.
- Dê và người bắt mỗi lượt có thể đi sang 4 ô chung cạnh hoặc đứng yên.
- Người bắt thắng nếu bắt được bất kỳ dê nào.
- Người chơi đóng vai một dê cụ thể. Dê bản thân thắng nếu không bị bắt, kể cả khi người bắt bắt được dê khác.
- Dê có hướng nhìn. Khi muốn dùng vị trí của người bắt hoặc dê khác, bắt buộc mục tiêu đó phải nằm trong tầm nhìn, trừ chiến thuật 3 có dùng bộ nhớ vị trí.
- Nếu hai dê va chạm với khoảng cách Manhattan <= 1 thì cả hai bị stun 3 lượt và tạo âm thanh cho người bắt.
- Người bắt nghe âm thanh trễ 1 lượt và di chuyển theo xác suất đúng hướng.

## Cấu trúc thư mục

```text
.
├── CMakeLists.txt
├── Makefile
├── README.md
├── include/
│   ├── BanDo.h
│   ├── ChienThuat.h
│   ├── ChienThuatDeCuThe.h
│   ├── ChienThuatNguoiBatAmThanh.h
│   ├── Config.h
│   ├── De.h
│   ├── HuongNhin.h
│   ├── KieuDuLieu.h
│   ├── MoPhong.h
│   ├── NguoiBat.h
│   ├── NhanVat.h
│   ├── Random.h
│   ├── ScoreHelper.h
│   ├── TranDau.h
│   └── ViTri.h
└── src/
    ├── BanDo.cpp
    ├── ChienThuatDeCuThe.cpp
    ├── ChienThuatNguoiBatAmThanh.cpp
    ├── Config.cpp
    ├── De.cpp
    ├── HuongNhin.cpp
    ├── MoPhong.cpp
    ├── NguoiBat.cpp
    ├── NhanVat.cpp
    ├── Random.cpp
    ├── ScoreHelper.cpp
    ├── TranDau.cpp
    └── main.cpp
```

## Vai trò từng nhóm file

| Nhóm file | Vai trò |
|---|---|
| `Config.h/.cpp` | Chứa thông số mô phỏng: kích thước bản đồ, số dê, số lượt, hệ số score, xác suất nghe đúng. |
| `ViTri.h`, `HuongNhin.h/.cpp` | Kiểu dữ liệu vị trí và hướng nhìn. |
| `KieuDuLieu.h` | Các struct kết quả, va chạm, quyết định di chuyển. |
| `BanDo.h/.cpp` | Luật bản đồ: ô hợp lệ, khoảng cách biên, tầm nhìn, bắt dê. |
| `NhanVat.h/.cpp` | Lớp cha cho dê và người bắt. |
| `De.h/.cpp` | Trạng thái của dê: vị trí, hướng nhìn, stun, bộ nhớ, khảo sát. |
| `NguoiBat.h/.cpp` | Trạng thái và hành động của người bắt. |
| `ChienThuat.h` | Interface chiến thuật cho dê và người bắt. |
| `ChienThuatDeCuThe.h/.cpp` | 3 cách chơi của dê. |
| `ChienThuatNguoiBatAmThanh.h/.cpp` | Thuật toán người bắt dựa vào âm thanh. |
| `ScoreHelper.h/.cpp` | Hàm rank, hàm score và các hàm lấy dê nhìn thấy / theo bộ nhớ. |
| `TranDau.h/.cpp` | Mô phỏng một trận đấu. |
| `MoPhong.h/.cpp` | Chạy nhiều trận và thống kê. |
| `main.cpp` | Điểm bắt đầu chương trình. |

## Cách build bằng Makefile

```bash
make
make run
```

## Cách build bằng CMake

```bash
cmake -S . -B build
cmake --build build
./build/bit_mat_bat_de
```

Trên Windows, file chạy có thể là:

```bash
./build/Debug/bit_mat_bat_de.exe
```

## Chỉnh thông số mô phỏng

Mở file `src/Config.cpp` và sửa các biến sau:

```cpp
int HS_khoangcachtoibien = 2;
int HS_khoangcachtoidegannhat = 3;
int HS_khoangcachtoinguoibat = 4;
int HS_sootieptheocothedi = 1;
```

Các hệ số này ảnh hưởng trực tiếp đến hàm score của dê.

## Gợi ý mở rộng tiếp theo

- Thêm module tự động thử nhiều bộ hệ số để tìm tỉ lệ thắng cao nhất.
- In log từng lượt để debug hành vi của dê và người bắt.
- Xuất kết quả ra CSV để vẽ biểu đồ.
- Thêm bản đồ có vật cản.
- Thêm chế độ một dê dùng chiến thuật A, các dê còn lại dùng chiến thuật B.
