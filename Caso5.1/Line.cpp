#include "Line.h"

Line::Line(std::string pText, int pWeigth)
{
    text = pText;
    weight = pWeigth;
}

int Line::getWeight()
{
    return weight;
}

std::string Line::getText()
{
    return text;
}
