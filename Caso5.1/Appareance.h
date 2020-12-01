#pragma once

class Appareance {

    int pos;
    int weightByNearest;
public:
    Appareance(int pPos,int pWeight);

    bool operator<(Appareance const& p) const
    {
        return pos < p.pos;
    }

    int getWeight();
    int getPos();
};