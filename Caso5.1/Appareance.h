#pragma once
#include <vector>
#include <tuple>

class Appareance {

    int pos;
    std::vector<int> fingerPrint;
public:
    Appareance(int pPos, std::vector<int> pFingerPrint);
    std::vector<int>  getFingerPrint();
    int getPos();
};