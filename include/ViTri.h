#pragma once

#include <cmath>
using namespace std;

struct vitri {
    int hang = 0;
    int cot = 0;

    int khoangcach(const vitri& a) const {
        return abs(hang - a.hang) + abs(cot - a.cot);
    }

    bool operator==(const vitri& a) const {
        return hang == a.hang && cot == a.cot;
    }

    bool operator<(const vitri& a) const {
        if (hang != a.hang) return hang < a.hang;
        return cot < a.cot;
    }
};
