#include "Line.h"

Line::Line(std::string pText, double pWeigth)
{
    text = pText;
    weight = pWeigth;
}

double Line::getWeight()
{
    return weight;
}

std::string Line::getText()
{
    return text;
}
