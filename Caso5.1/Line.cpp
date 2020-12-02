#include "Line.h"
#include <vector>

Line::Line(std::string pText, std::vector<int> pfingerPrint)
{
    text = pText;
    fingerPrint = pfingerPrint;
}

double Line::getWeight()
{
    return weight;
}

std::string Line::getText()
{
    return text;
}

std::vector<int> Line::getFingerPrint()
{
    return fingerPrint;
}