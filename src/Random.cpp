#include "Random.h"

#include <ctime>
#include <random>
using namespace std;

int RandInt(int a, int b) {
    static mt19937 boSinhNgauNhien((unsigned)time(nullptr));
    uniform_int_distribution<int> randomSoNguyen(a, b);
    return randomSoNguyen(boSinhNgauNhien);
}

double RandDouble01() {
    static mt19937 boSinhNgauNhien((unsigned)time(nullptr) + 99991);
    uniform_real_distribution<double> randomSoThuc(0.0, 1.0);
    return randomSoThuc(boSinhNgauNhien);
}
